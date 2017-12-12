#include "Account.h"
/*
This class represents a bank account
*/

class Account
{
private:
	int accountId_;
	char password_[4];
	double balance_;
	bool isVIP_;

	//Mutexes
	pthread_mutex_t readersMutex_;
	pthread_mutex_t writersMutex_;

	//Counter for readers-writer
	int readers_count_;

public:
	//*************************************************************************
	//* Function name: Account
	//* Description  : Account constructor
	//* Parameters   : accountId, password, initialBalance
	//* Return value : None
	//*************************************************************************
	Account(int account_id, char password[4], double initialBalance)
	{
		accountId_ = account_id;
		strcpy(password_, password);
		balance_ = initialBalance;
		isVIP_ = false;
		int createReadersMutex = pthread_mutex_init(&readersMutex_, NULL);
		int createWritersMutex = pthread_mutex_init(&writerssMutex_, NULL);

		//Check mutex initialization
		if (createReadersMutex != 0 || createWritersMutex != 0)
		{
			cerr << "Initializing mutex failed!" << endl;
			exit(-1);
		}

		readers_count_ = 0;
	}

	//*************************************************************************
	//* Function name: Account
	//* Description  : Account d'tor
	//* Parameters   : None
	//* Return value : None
	//*************************************************************************
	~Account() 
	{
		int destoryReaderMutex = pthread_mutex_init(&readersMutex_);
		int destoryReaderMutex = pthread_mutex_init(&writersMutex_);
		if (destoryReaderMutex != 0 || destoryReaderMutex != 0)
		{
			cerr << "Destroying mutex failed!" << endl;
			exit(-1);
		}
	}

	//*************************************************************************
	//* Function name: 	 makeVIP()
	//* Description  : Turns this account to a VIP account
	//* Parameters   : None
	//* Return value : None
	//*************************************************************************
	void makeVIP()
	{
		isVIP_ = true;
	}


	//*************************************************************************
	//* Function name: IsPasswordCorrect
	//* Description  : the function verifies whether the enetered password is correct
	//* Parameters   : userPassword - the password entered
	//* Return value : bool - true if the password correct and false otherwise
	//*************************************************************************
	bool checkPassword(char userPassword[4])
	{
		if (strcmp(password_, userPassword) == 0)
		{
			return true;
		}

		else
		{
			return false;
		}
	}

	//*************************************************************************
	//* Function name: deposit
	//* Description  : Deposit the given ammount to the account
	//* Parameters   : depositAmount - the ammount to deposit
	//* Return value : None
	//*************************************************************************
	void deposit(double depositAmount)
	{
		balance_ += depositAmount;
	}

	//*************************************************************************
	//* Function name: withdraw
	//* Description  : Withdraws the given ammount from the account
	//* Parameters   : withdrawAmount - the ammount to withdraw
	//* Return value : true if the withdrawing amount is legal (i.e. <= this.balance), false otherwise
	//*************************************************************************
	bool withdraw(double withdrawAmount)
	{
		if (balance_ < withdrawAmount)	
			{
			return false;
			}

		balance_ = balance_ - withdrawAmount;
		return true;
	}

	//*************************************************************************
	//* Function name: getBalance
	//* Description  : Returns the current balance
	//* Parameters   : None
	//* Return value : This account's balanace
	//*************************************************************************
	double getBalance()
	{
		return balance_;
	}

	//*************************************************************************
	//* Function name: lockWritersMutex
	//* Description  : locks the writers mutex
	//* Parameters   : None
	//* Return value : None
	//*************************************************************************
	void lockWritersMutex()
	{
		int writersLockCheck = pthread_mutex_lock(&writersMutex_);
		if (writersLockCheck != 0)
		{
			cerr << "locking writers mutex failed!" << endl;
			exit(-1);
		}
	}

	//*************************************************************************
	//* Function name: unlockWritersMutex
	//* Description  : unlocks the writers mutex
	//* Parameters   : None
	//* Return value : None
	//*************************************************************************
	void unlockWritersMutex()
	{
		int writersunlockCheck = pthread_mutex_unlock(&writersMutex_);
		if (writersunlockCheck != 0)
		{
			cerr << "unlocking writers mutex failed!" << endl;
			exit(-1);
		}
	}

	//*************************************************************************
	//* Function name: lockReadersMutex
	//* Description  : locks the readers mutex
	//* Parameters   : None
	//* Return value : None
	//*************************************************************************
	void lockReadersMutex()
	{
		int readersLockCheck = pthread_mutex_lock(&readersMutex_);
		if (readersLockCheck != 0)
		{
			cerr << "locking readers mutex failed!" << endl;
			exit(-1);
		}
	}

	//*************************************************************************
	//* Function name: unlockReadersMutex
	//* Description  : unlocks the readers mutex
	//* Parameters   : None
	//* Return value : None
	//*************************************************************************
	void unlockReadersMutex()
	{
		int readersunlockCheck = pthread_mutex_unlock(&readersMutex_);
		if (readersunlockCheck != 0)
		{
			cerr << "unlocking readers mutex failed!" << endl;
			exit(-1);
		}
	}

	//*************************************************************************
	//* Function name: increaseReadersNum
	//* Description  : increases the readers-counter by 1
	//* Parameters   : None
	//* Return value : None
	//*************************************************************************
	void increaseReadersNum()
	{
		readers_count_++;
		
	}

	//*************************************************************************
	//* Function name: decreaseReadersNum
	//* Description  : decreases the readers-counter by 1
	//* Parameters   : None
	//* Return value : None
	//*************************************************************************
	void decreaseReadersNum()
	{
		readers_count_--;
	}

	//*************************************************************************
	//* Function name: getReadersCount
	//* Description  : returns the number of current readers
	//* Parameters   : Number of current readers
	//* Return value : the number of current readers
	//*************************************************************************
	int getReadersCount()
	{
		return readers_count_;

	}
};
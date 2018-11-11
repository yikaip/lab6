// Edit: Yikai Peng @ 11/05/18
// SortedDriver.cpp

// tom bailey   1445  25 mar 2014
// Construct sorted sequences and call functions that
//   process the sorted sequences.


#include "RandomUtilities.h"
#include "ContainerPrinting.h"
#include "winTimer.h"//CHANGE: this to unixTimer.h if on mac/linux
#include <list>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// post: a sorted vector of listSize random doubles from
//         the range minNum to maxNum has been returned.
vector<double>
getNums(size_t listSize, double minNum, double maxNum)
{
	vector<double> theList;
	for (size_t i = 0; i < listSize; ++i)
	{
		theList.push_back(randReal(minNum, maxNum));
	}

	sort(begin(theList), end(theList));

	return theList;
}


// post: a sorted list of numWords words of length
//         wordLength with characters chosen randomly from
//         alphabet has been returned.
list<string>
getWords(size_t numWords, size_t wordLength, string alphabet)
{
	list<string> theWords;
	for (size_t i = 0; i < numWords; ++i)
	{
		string word;
		for (size_t j = 0; j < wordLength; ++j)
		{
			word += alphabet.at(randInt(0, alphabet.size()));
		}
		theWords.push_back(word);
	}

	theWords.sort();

	return theWords;
}


// pre:  number is not empty;
//       number is sorted from smallest to largest
// post: The most isolated entry in number has been returned
double
mostIsolated(vector<double> & number)
{
	// STUB  -YP

	//double n = number.size(); the  size of the number vector; it'll be better not characterized the size as double
	double IsoDiff = (number.at(number.size() - 2)) - (number.at(number.size() - 1)); //to return the difference between the next number and number
	double Num(0); //initialize Num, this is the number on position "i"
	double tempNum(0); //tempNum to store number temperarly
	double NumRight(0); //number at right
	double NumLeft(0); //number at left
	double oldNumber = number.at(number.size() - 1); //initialize an old number at position (size-1)
	int location = number.size() - 1; //locaion "i", to access number at some point, it is size-1

	for (int i = (number.size() - 2); i >= 0; i--)  //for integer location i starting at size-2, bigger or equals to 0, derease 1 each time
	{

		Num = number.at(i); //num is the number at location i
		NumRight = abs(Num - oldNumber); //number at the right is equals to the absolute value of the difference between number and old number
		if (i == 0) //when the first number
		{
			tempNum = abs(((number.at(i)) - (number.at(i + 1)))); //temp value is the number at right - the difference between number at position i and i+1
			if (tempNum > IsoDiff) //if temp number is bigger than the difference
			{
				IsoDiff = tempNum; //assign difference to tempNum
				location = i; //location is i
			}
			break;  //stop the if statement
		}
		NumLeft = abs(Num - number.at(i - 1)); //number at the left is equals to the absolute value of the difference between number at position i and i-1

		if (NumLeft < NumRight) //if number at left is less than number at right
		{ 
			tempNum = NumLeft; //tempNum is number at left
		}
		else 
		{
			tempNum = NumRight; //else tempNume is the number at right
		}

		tempNum = abs(tempNum); //set tempNum to a positive number
		Num = abs(Num); //set Num to a positive number

		if (tempNum > IsoDiff) //if temNum is bigger than the isolate difference
		{
			IsoDiff = tempNum; //assign tempnum to isodiff
			location = i; //location is i
		}

		oldNumber = Num;

	}
	
	/*for (int i = 0; i <= number.size(); i++) //for integer type i  starting with 0, goes until the end of the vector, increase by 1 every time
	{
		Num = number.at(i); //number at position i
		NumRight = abs(Num - number.at(i + 1)); //number at the right is equals to the absolute value of the difference between number at position i and i+1

		if (i == 0) //when the first number
		{
			tempNum = NumRight; //temp value is the number at right
			if (tempNum > NumRight) //if temp number is bigger then the number at right
			{
				IsoDiff = tempNum; //assign that to isodiff
				Location = i; //location at i
			}
			break; //stop the if statement
		}

		NumLeft = abs(Num - number.at(i - 1)); //number at the left is equals to the absolute value of the difference between number at position i and i-1

		if (i == number.size()) //when it's the last number
		{
			tempNum = NumLeft; //temp value is the number at left
			if (tempNum > NumLeft) //if temp number is bigger then the number at left
			{
				IsoDiff = tempNum; //assign that to isodiff
				Location = i; //location at i
			}
			break; //stop the if statement
		}
		/*
		if (tempNum > IsoDiff)
		{
			IsoDiff = tempNum;
			Location = i;
		}
		Num = tempNum;
	} */
	

	return number.at(location); //return  the number at that position
}


// pre:  A and B are sorted.
// post: The number of strings in A that do not occur in B
//         has been returned.
int
unmatched(list<string> & A, list<string> & B)
{
	// STUB  -YP

	list<string>::iterator iterA = A.begin(); //initialize an iterator A as the beginning number of A list
	list<string>::iterator iterB = B.begin(); //initialize an iterator B as the beginning number of B list
	int count(0);
	while (iterA != end(A)) //when iterA is not the end of A list
	{
		if (*iterA < *iterB) //if pointer to iterA is less then pointer to iterB; this pointer points to the address of iterA and B
		{
			count++; //count the number of count by increment it
			iterA++; //increment iterA to count the size of iterA
		}
		else if (*iterA == *iterB) //else if they are equal
		{
			iterA++; //increment iterA to count the size of iterA
		}
		else
		{
			if (iterB != end(B)) //if iterB is not the end of B list
			{
				iterB++; //increment B to count the size of iterB
			}
		}
	}

	return count;

}


int
main()
{
	cout << "Find the most isolated number" << endl
		<< "-----------------------------" << endl << endl;
	while (true)
	{
		cout << "Enter size for numbers: ";
		int n = 0;
		cin >> n;
		if (n <= 0)
			break;
		cout << "Enter seed for rand: ";
		unsigned int seed;
		cin >> seed;
		srand(seed);

		// Construct a sorted list of numbers
		Timer get;
		get.start();
		vector<double> numbers = getNums(n, -n, n);
		get.stop();
		cout << "Constructed in " << get() << " seconds"
			<< endl;

		if (n < 10)
			cout << numbers << endl << endl;

		// Report a most isolated isolated number
		Timer time;
		time.start();
		double isolated = mostIsolated(numbers);
		time.stop();
		cout << "The most isolated number is "
			<< isolated << endl
			<< "calculated in " << time() << " seconds"
			<< endl << endl;
	} 
	

	cout << endl << endl;
	cout << "Count the unmatched words" << endl
		<< "-------------------------" << endl << endl;
	while (true)
	{
		cout << "Enter size for words lists: ";
		int n = 0;
		cin >> n;
		if (n <= 0)
			break;
		cout << "Enter word length: ";
		int wordSize;
		cin >> wordSize;
		cout << "Enter alphabet: ";
		string alphabet;
		cin >> alphabet;

		cout << "Enter seed for rand: ";
		unsigned int seed;
		cin >> seed;
		srand(seed);

		// Construct two sorted vectors of words
		Timer get;
		get.start();
		list<string> A = getWords(n, wordSize, alphabet);
		list<string> B = getWords(n, wordSize, alphabet);
		get.stop();
		cout << "Constructed in " << get() << " seconds"
			<< endl;

		if (wordSize * n < 60)
		{
			cout << "A is: " << A << endl
				<< "B is: " << B << endl;
		}

		// Report the number of words in the first sorted list
		//   that are not in the second sorted list
		Timer time;
		time.start();
		int count = unmatched(A, B);
		time.stop();
		cout << count
			<< " words in A were not in B" << endl
			<< "calculated in " << time() << " seconds"
			<< endl << endl;
	}

	return 0;
}

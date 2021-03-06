#include "stdafx.h"
#include <iostream>
#include <ostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <time.h>
#include <string>

// Name: Sean Mathews
// Date Modified: 1/10/18
// Class: CS-340
// Instructor: Ercal
// Description: This is the cpp file that has main. Main will call each sorting algorithm. 
// Before and after each call will be a timer that will output the time it took for the sort to complete.
// This will be done for insertion sort, merge sort, and heap sort. Within heap sort, there is a process called 
// the max-heap. This will also be timed seperately as well while the heap sort is running. 


using namespace std;


char getSortingAlg();
char getFileSize();
char getPermSorted();

void loadFileIntoArray(string list[]);

void insertionSort(string arr[], int n);

void mergeSort(string arr[], int left, int right);
void merge(string arr[], int left, int middle, int right);

void heapSort(string arr[], int n);

void maxHeapify(string arr[], int n, int i);


int main()
{
	//these three references will store the returned values from user input
	char sortingAlgChoice, fileSizeChoice, permSortedChoice;

	//this is the reference for file being read in
	ifstream listFile;

	//this is the reference when creating the output file
	ofstream outputFile;

	//string objects that hold parts of the file name that will be opened
	
	string stringFileSize;
	string fileType;


	//these are the returned values from all the user input to get started
	sortingAlgChoice = getSortingAlg();

	fileSizeChoice = getFileSize();

	permSortedChoice = getPermSorted();

	string emptyString = "";

	//this will be a nested switch statement. This will go through options to determine which file to open, load it into an array, and what alg to use with it

	//first take care of the fileSizeChoice, then figure out which file to get. then load the file, then figure out which sort to use, then sort. 

	if ( fileSizeChoice == '1' ) {

		//represents the amount of words in the txt file in thousands
		stringFileSize = "30";

		//makes the array with the correct amount of space
		
	}

	else if (fileSizeChoice == '2') {

		 stringFileSize = "60";

	}
	else if (fileSizeChoice == '3') {

		  stringFileSize = "90";
		
	}
	else if (fileSizeChoice == '4') {

		 stringFileSize = "120";
	
	}
	else if (fileSizeChoice == '5') {

		 stringFileSize = "150";
	}

	if (permSortedChoice == '1') {

		 fileType = "sorted";
	}
	else if (permSortedChoice == '2') {

		 fileType = "perm";

	}

	if (sortingAlgChoice == '1') {

		//this string is what holds what file to open
		 emptyString += fileType + stringFileSize + "k" + ".txt";

		 //open the file
		listFile.open(emptyString);

		//add 3 0s to put it into the correct value place, in one case its 30k instead of just 30
		stringFileSize += "000";

		//this converts the fileSize string into an int to be used as the size for the initialization of the array
		int fileSize = stoi(stringFileSize);

		//initialize the new array using its dereference
		static string *stringArray = new string[fileSize];

		//loadFileIntoArray(stringArray);

		if (listFile.fail()) {
			cout << "Oops! file couldn't open." << endl;
		}

		//initial size of how many words are in the array currently, which is 0
		int arrayFilledSize = 0;

		while (!listFile.eof()) {

			//loads the each list item into an array
			listFile >> stringArray[arrayFilledSize];

			arrayFilledSize++;
		}
		
		//starts timer
		clock_t beginInsertion = clock();
	
		insertionSort(stringArray, fileSize);

		//ends timer
		clock_t endInsertion = clock();

		double elapsed_secs = double(endInsertion - beginInsertion) / CLOCKS_PER_SEC;
		cout << "It took " << elapsed_secs << " seconds to complete insertion sort." << endl;

		cout << "The outputFile is located in the solution folder alongside all the other files." << endl;

		//this is where the outstream file will be made for the graph
		outputFile.open("outputFile.txt");

		outputFile << "InsertionSort Time: " << endl;
		outputFile << elapsed_secs << endl;

		outputFile << "SortedList Using InsertionSort: " << endl;

		for (int i = 0; i < (fileSize - 1); i++)
		{
			outputFile << stringArray[i] << endl;
		}
	}

	//mergesort
	else if (sortingAlgChoice == '2') {

		//this string is what holds what file to open
		emptyString += fileType + stringFileSize + "k" + ".txt";

		//open the file
		listFile.open(emptyString);

		//add 3 0s to put it into the correct value place, in one case its 30k instead of just 30
		stringFileSize += "000";

		//this converts the fileSize string into an int to be used as the size for the initialization of the array
		int fileSize = stoi(stringFileSize);

		//initialize the new array using its dereference
		static string *stringArray = new string[fileSize];

		//loadFileIntoArray(stringArray);

		if (listFile.fail()) {
			cout << "Oops! file couldn't open." << endl;
		}

		//initial size of how many words are in the array currently, which is 0
		int arrayFilledSize = 0;

		while (!listFile.eof()) {

			//loads the each list item into an array
			listFile >> stringArray[arrayFilledSize];

			arrayFilledSize++;
		}

		//this puts the middle index value into a reference called middle 
		int middle = ((fileSize - 1) - arrayFilledSize) / 2;

		//this puts the very last index value to a reference called right
		int right = fileSize - 1;

		int left = 0;

		//starts timer
		clock_t beginMerge = clock();

		//takes in array name, start of list(left), middle of list( (right - left) / 2), then end of list (right)
		mergeSort(stringArray, 0, (fileSize - 1) );

		//ends timer
		clock_t endMerge = clock();

		/*for  (int i = 0; i < (fileSize - 1) ; i++)
		{
			cout << stringArray[i] << endl;
		}*/

		double elapsed_secs = double(endMerge - beginMerge) / CLOCKS_PER_SEC;
		cout << "It took " << elapsed_secs << " seconds to complete merge sort." << endl;

		cout << "The outputFile is located in the solution folder alongside all the other files." << endl;

		//this is where the outstream file will be made
		outputFile.open("outputFile.txt");

		outputFile << "MergeSort Time: " << endl;
		outputFile << elapsed_secs << endl;

		outputFile << "SortedList Using MergeSort: " << endl;

		for (int i = 0; i < (fileSize - 1); i++)
		{
			outputFile << stringArray[i] << endl;
		}
	}

	//heapsort
	else if (sortingAlgChoice == '3') {
		//this string is what holds what file to open
		emptyString += fileType + stringFileSize + "k" + ".txt";

		//open the file
		listFile.open(emptyString);

		//add 3 0s to put it into the correct value place, in one case its 30k instead of just 30
		stringFileSize += "000";

		//this converts the fileSize string into an int to be used as the size for the initialization of the array
		int fileSize = stoi(stringFileSize);

		//initialize the new array using its dereference
		static string *stringArray = new string[fileSize];

		//loadFileIntoArray(stringArray);

		if (listFile.fail()) {
			cout << "Oops! file couldn't open." << endl;
		}

		//initial size of how many words are in the array currently, which is 0
		int arrayFilledSize = 0;

		while (!listFile.eof()) {

			//loads the each list item into an array
			listFile >> stringArray[arrayFilledSize];

			arrayFilledSize++;
		}

		//starts timer
		clock_t beginHeap = clock();

		heapSort(stringArray, fileSize);

		//ends timer
		clock_t endHeap = clock();

		double elapsed_secs = double(endHeap - beginHeap) / CLOCKS_PER_SEC;
		cout << "It took " << elapsed_secs << " seconds to complete heap sort." << endl;

		cout << "The outputFile is located in the solution folder alongside all the other files." << endl;

		//this is where the outstream file will be made
		outputFile.open("outputFile.txt");

		outputFile << "HeapSort Time: " << endl;
		outputFile << elapsed_secs << endl;

		outputFile << "SortedList Using HeapSort: " << endl;

		for (int i = 0; i < (fileSize - 1); i++)
		{
			outputFile << stringArray[i] << endl;
		}

	}

	
	
}


char getSortingAlg() {

	char sortingAlgChoice;
	cout << "Which sorting Algorithim would you like to use?" << endl;

	cout << "1) Insertion Sort" << endl;
	cout << "2) Merge Sort" << endl;
	cout << "3) Heap Sort" << endl;

	cin >> sortingAlgChoice;
	return sortingAlgChoice;
}

char getFileSize() {
	char fileSizeChoice;

	cout << "Which file size would you like?" << endl << endl;

	cout << "1) 30k" << endl;
	cout << "2) 60k" << endl;
	cout << "3) 90k" << endl;
	cout << "4) 120k" << endl;
	cout << "5) 150k" << endl;

	cin >> fileSizeChoice;

	return fileSizeChoice;
}

char getPermSorted() {
	char permSortedChoice;

	cout << "Do you wish for a permuted list or a sorted list?" << endl << endl;

	cout << "1) SortedList" << endl;
	cout << "2) PermutedList" << endl;

	cin >> permSortedChoice;

	return permSortedChoice;
}



void insertionSort(string arr[], int arraySize) {
	
	{
		int i, j;

		string key;
		for (i = 1; i < arraySize; i++)
		{
			key = arr[i];
			j = i - 1;

			/* Move elements of arr[0..i-1], that are
			greater than key, to one position ahead
			of their current position */
			while (j >= 0 && arr[j] > key)
			{
				arr[j + 1] = arr[j];
				j = j - 1;
			}
			arr[j + 1] = key;
		}
	}
	

	

}

void mergeSort(string arr[], int left, int right) {

	if (left < right)
	{
		// Same as (l+r)/2, but avoids overflow for
		// large l and h
		int middle = floor((right + left) / 2);

		// Sort first half
		mergeSort(arr, left, middle);

		// Sort second half
		mergeSort(arr, middle + 1, right);

		//merge the two arrays
		merge(arr, left, middle, right);
	}

}

void merge(string arr[], int left, int middle, int right) {

	
	
	//lefthalf = 1
	//righthalf = 0
	// n1 = leftHalfSize
	// n1 = q - p + 1
	// n2 = r - q

	int leftHalfSize = middle - left + 1;
	int rightHalfSize = right - middle;

	// create temp arrays that are of their respective sizes, and then add one more index for the sentinel value. The purpose of the sentinel value 
	// is to be able to assign the rest of the values to the merging array once the first temp array has been merged. for example leftArray = [A,B] and rightArray = [C,D] let mergedArray = [ , , , ,] where they are no values in it yet
	// then merge A,B into the mergeArray[A,B, , ]. now once the first array has been merged then the rest of those values should be compared to a really big value to guarantee that the order of those values wont be changed
	// when C, D are merged. The ordering of C, D wont change since they are compared to a really big value.


	string *leftArray = new string[leftHalfSize + 1];
	string *rightArray = new string[rightHalfSize + 1];

	

	// copy data to temp arrays leftArray and rightArray

	// leftArray
	for (int i = 0; i <= leftHalfSize; i++) {

		leftArray[i] = arr[left + i];

	}

	// rightArray
	for (int j = 0; j <= rightHalfSize; j++) {

		rightArray[j] = arr[middle + 1 + j];

	}

	//these are the sentinel values used to force the other subarray to merge if one subarray is finished
	leftArray[leftHalfSize] = "ZZZZ";
	rightArray[rightHalfSize] = "ZZZZ";

	//merge the temp arrays back into the parameter given array called arr
	//first initialize the indexes with 0 to begin at the first element in both sub arrays

	int indexLeftArray = 0; // initialized index of first subarray, i
	int indexRightArray = 0; // initialized index of second subarray, j
	int k = left;
	//p = left, r = right

	for ( int k = left; k <= right; k++)
	{
		if (leftArray[indexLeftArray] <= rightArray[indexRightArray])
		{
			//this assigns the left value to the new array, arr
			arr[k] = leftArray[indexLeftArray];
			indexLeftArray++;
		}
		else
		{
			//this assigns the right value to the new array, arr
			arr[k] = rightArray[indexRightArray];
			indexRightArray++;
		}
	}
}






void heapSort(string arr[], int heapSize) {

	
	clock_t beginHeapify = clock();





	//builds max heap
	for (int i = heapSize / 2 - 1; i >= 0; i--) {

		//this keeps recurssively calling itself until maxheap is made
		maxHeapify(arr, heapSize, i);

	}
	

	clock_t endHeapify = clock();

	double elapsed_secs = double(endHeapify - beginHeapify) / CLOCKS_PER_SEC;
	cout << "It took " << elapsed_secs << " seconds to complete heapfy" << endl;

	// One by one extract an element from heap
	for (int i = heapSize - 1; i >= 0; i--)
	{
		// Move current root to end
		swap(arr[0], arr[i]);

		//call max heapify on the reduced heap
		maxHeapify(arr, i, 0); //heapify(arr, i, 0); heapify(arr, n, largest);
	}


}

void maxHeapify(string arr[], int heapSize, int i) {

	int largest = i;
	int left = 2 * i + 1;  // This gets you the left child of the current index left = 2*i + 1
	int right = 2 * i + 2;  //this gets you the right child of the current index right = 2*i + 2

	// If left child is larger than root
	if (left <= heapSize && arr[left] > arr[largest]) {
		int largest = left;
	}

	// If right child is larger than largest so far
	if (right <= heapSize && arr[right] > arr[largest]) {
		int largest = right;
	}

	// If largest is not root
	if (largest != i)
	{
		//to swap the top of the heap with the current index that we are at. 
		swap(arr[i], arr[largest]);

		// Recursively heapify the affected sub-tree
		maxHeapify(arr, heapSize, largest);

	}
}




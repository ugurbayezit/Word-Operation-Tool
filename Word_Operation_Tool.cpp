#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <algorithm>
using namespace std;

class WordOperation{
	public:
		
		string star_check="*";
		//string kelime="u*i*a";
		//string kelime="a*e*o";
		
		string Begin_Word;//Word based on the position of the star
		string Middle_Word;//Word based on the position of the star
		string Last_Word;//Word based on the position of the star
		string Readed_Document;//Readed text string
		string Filled_Document;//Fillled text string
	
		int star_checkerr=0;// The number of star
		int *star_checker_arr{new int[50]};// The star Position in Word
		
		int *result{new int[50]};//Result
		int result_counter=0;
		
		int replace_counter=0;
		int *replace_arr{new int[50]};
		
		int replace_counter1=0;
		int *replace_arr1{new int[50]};//ending index of words obtained after the position of the star
		
		int control_mid=0;
		
		void OpenText(string path);
		void FindWordP(string Searched_Word,string Searched_Place,int *arr, int &arr_counter,int index);//Word search function with star action
		void StarCheckProcess(string Searched_Word,string Searched_Place);//Control and store the star
		void FindStarPosition(string Searched_Word,string Searched_Place);//Finding position of star and divide part of word
		void FindWordWithStar(string Searched_Word,string Searched_Place);//Find word in readed document
		void EraseWordWithStar(string Word);//Erase word in readed document
		void UserCommands();
		
		int index_position_arr_counter1=0; // The Number of Words Found
		int *index_position_arr1{new int[50]}; // The Position of the Found Word
		int indexx;
		
		int line_checker=0;// The number of line
		int *line_checker_arr{new int[50]}; // The Line Position in Word
		
		string line_check="-"; // Line Check 
		
		void LineCheckProcess(string Searched_Word,string Searched_Place); // Check Line Status Process
		void FindWord(string Searched_Word,string Searched_Place); // Find General Word Process
		void FindWordLine(string Searched_Word,string Searched_Place); // Find Line or No-line Word Process
		void ReplaceWord(string Original,string Desired); // Replace Word Process
		void EraseWord(string word); //Erase Word Process
};

void WordOperation::OpenText(string path) 
{
	
ifstream MyReadFile(path);
if(MyReadFile.is_open())
{
// Use a while loop together with the getline() function to read the file line by line
while (getline (MyReadFile, Filled_Document)) {
// Output the text from the file
Readed_Document.append(Filled_Document);
}
// Close the file
MyReadFile.close();
}
else
{
cout<<"Can't open file"<<endl;
}

}

void WordOperation::FindWordP(string Searched_Word,string Searched_Place,int *arr, int &arr_counter,int index)
{
	//Local Variables
	arr_counter=0;	
	int word_positionn=0;
	word_positionn=0;
	index=0;

	while((index = Searched_Place.find(Searched_Word, word_positionn)) != string::npos) // Search for the position of the word in the file being read
	{
		//kelime arama
		//cout << "Match found at position: " << index << endl; //New position is from next element of index
		word_positionn = index + 1; //new position is from next element of index
		arr[arr_counter]=index; // Assign given array's position in array position counter to word position in the document
		arr_counter++;
	}
	//cout<<endl;
}

void WordOperation::StarCheckProcess(string Searched_Word,string Searched_Place)
{
	//Local Variables
	int index;
	int word_position = 0;
	
	while((index = Searched_Place.find(Searched_Word, word_position)) != string::npos) // Search for the position of the word in the file being read
	{
	//kelime arama
	//cout << "Match found at position: " << index << endl;
	word_position = index + 1; //new position is from next element of index
	star_checker_arr[star_checkerr]=index;// Assign star's position in star position counter to word position in the document
	star_checkerr++;
	}	
}

void WordOperation::FindStarPosition(string Searched_Word,string Searched_Place)
{
	//Local Variables
	string star_index_variable;
	string star_index_variable1;
	string star_index_variable2;
	string star_index_variable3;
	
	int index_star;
	int index_star1;
	string star_check="*";
	//StarCheckProcess(star_check,Searched_Word); //Find Star Position
	
	index_star=star_checker_arr[0]; //Insert star index
	index_star1=star_checker_arr[1];//Insert star index
	
	star_index_variable=Searched_Word[index_star+1];//The value of the word after the star is assigned.
	star_index_variable1=Searched_Word[index_star-1];//the value of the word before the star is assigned.
	
	star_index_variable2=Searched_Word[index_star1+1];//The value of the word after the star is assigned.
	star_index_variable3=Searched_Word[index_star1-1];//the value of the word before the star is assigned.
	control_mid=0;
	if (star_checkerr==1)// If the 1 star
	{
		if ( (star_index_variable!="" && index_star==0) ||(star_index_variable1!="" && index_star==(Searched_Word.length()-1))) //Whether the star is at the beginning or at the end of the word is checked.
		{
		Searched_Word.erase(index_star,1);//Star is deleted from the word
		Begin_Word=Searched_Word;// Store the global variable
		}
		else if (star_index_variable!="" && star_index_variable1!="") // If the star is the middle
		{
			for(int a=0; a<index_star; a++)
			{
				Begin_Word.push_back(Searched_Word[a]);//The word to the left of the star is stored global variable.
			}
			for(int b=index_star+1; b<Searched_Word.length();b++)
			{
				Last_Word.push_back(Searched_Word[b]);//The word to the right of the star is stored global variable.
			}
		}	
	}

	if (star_checkerr==2)// If the 2 star
	{
		if (index_star==0 && index_star1==(Searched_Word.length()-1)) //If it is at the beginning and end
		{
			Searched_Word.erase(index_star,1);//Star is deleted from the word
			Searched_Word.erase(index_star1-1,1);//Star is deleted from the word
			Middle_Word=Searched_Word;//The word stored to global variable
			control_mid++;
		}
		else if(star_index_variable!="" && star_index_variable1!="" && star_index_variable2!="" && star_index_variable3!="")// If the stars is the middle
		{
			for(int x=0; x<index_star; x++)
			{
				Begin_Word.push_back(Searched_Word[x]);//Store the begin word in global variable
			}
			for (int y=index_star+1; y<index_star1; y++)
			{
				Middle_Word.push_back(Searched_Word[y]);//Store the middle word in global variable
			}
			for(int z=index_star1+1; z<Searched_Word.length();z++)
			{
				Last_Word.push_back(Searched_Word[z]);//Store the last word in global variable
			}
		}
	}
}

void WordOperation::FindWordWithStar(string Searched_Word,string Searched_Place)
{
	
	//Local Variables
	string Space_Position=" ";
	
	int star_checker=0;
	int *star_checker_arr{new int[50]};
	int index_star;
	
	int star_checker1=0;
	int *star_checker_arr1{new int[50]};
	int index_star1;
	
	int star_checker2=0;
	int *star_checker_arr2{new int[50]};
	int index_star2;
	
	int star_checker3=0;
	int *star_checker_arr3{new int[50]};
	int index_star3;
	

	int position_control=0;
	int position_control1=0;

	int begin_controller=0;
	int begin_controller1=0;
	int middle_controller=0;
	int middle_controller1=0;
	int last_controller=0;
	int last_controller1=0;
	
	int *begin_to_middle{new int[50]};
	int begin_to_middle_counter=0;
	
	int *middle_to_last{new int[50]};
	int middle_to_last_counter=0;
	int controller=0;
	
	FindStarPosition(Searched_Word,Readed_Document);// Search star position
	
	if (!Begin_Word.empty()){ //if there is a character in the begin string
		FindWordP(Begin_Word,Readed_Document,star_checker_arr,star_checker,index_star);//Find begin word in readed document
		//cout<<star_checker;
	}
	
	if (!Middle_Word.empty()){//if there is a character in the middle string
		FindWordP(Middle_Word,Readed_Document,star_checker_arr1,star_checker1,index_star1);//Find middle word in readed document
		//cout<<star_checker1;
	}
	
	if (!Last_Word.empty()){//if there is a character in the last string
		FindWordP(Last_Word,Readed_Document,star_checker_arr2,star_checker2,index_star2);//Find last_word word in readed document
	}
	
	FindWordP(Space_Position,Readed_Document,star_checker_arr3,star_checker3,index_star3);//Find space word in readed document
	
	cout<<Begin_Word<<" ";
	cout<<Middle_Word<<" ";
	cout<<Last_Word<<" ";
	
	if (!Begin_Word.empty() && !Last_Word.empty() && Middle_Word.empty()) //if there is a character in the beginning and the last string and the character in the middle is empty
	{
		for(int i=0; i<star_checker; i++) //Create array for length begin word
		{
			for(int a=0; a<star_checker2; a++)//Create array for length last word
			{
				//Controller
				begin_controller=0;
				begin_controller1=0;
				//All possibilities are scanned between begin and last indices.
				for (int b=star_checker_arr[i]; b<star_checker_arr2[a]; b++)
				{
					if(star_checker_arr[i]<star_checker_arr2[a])//If the starting index is less then the last index
					{
						begin_controller=1;//controller checked
					}
					for(int c=0; c<star_checker3; c++)//Space checker
					{
						if (b==star_checker_arr3[c])//Checking the space character between two indexes.
						{
						begin_controller1=1;//controller checked
					}
					}
				}
				//cout<<endl;
				if (begin_controller==1&&begin_controller1==0)//if both spaces and index values are provided
				{
				cout<<star_checker_arr[i]<<" ";
				result[result_counter]=star_checker_arr[i];//insert word position
				result_counter++;
				}
			}
		}
	}
	else
	{
		controller++;
		
	}
	cout<<endl;
	
	if (!Begin_Word.empty() && !Middle_Word.empty() && !Last_Word.empty()) //if there is a character in the beginning, middle and the last string
	{
		for(int i=0; i<star_checker; i++) //Create array for length begin word
		{
			for(int a=0; a<star_checker1; a++)//Create array for length middle word
			{
				begin_controller=0;
				begin_controller1=0;
				//All possibilities are scanned between begin and middle indices.
				for (int b=star_checker_arr[i]; b<star_checker_arr1[a]; b++) 
				{
					if(star_checker_arr[i]<star_checker_arr1[a])//If the begin index is less then the middle index
					{
						begin_controller=1;//controller checked
					}
					for(int c=0; c<star_checker3; c++)//Space checker
					{
						if (b==star_checker_arr3[c])//Checking the space character between two indexes.
						{
							begin_controller1=1;//controller checked
						}
					}
				}
				//cout<<endl;
				if (begin_controller==1&&begin_controller1==0)//if both spaces and index values are provided
				{
				cout<<star_checker_arr[i]<<" ";
				begin_to_middle[begin_to_middle_counter]=star_checker_arr[i];//insert word position to begin_to_middle
				begin_to_middle_counter++;
				}
			}
		}
		cout<<endl;
		
		for(int i=0; i<star_checker1; i++) //Create array for length middle word
		{
			for(int a=0; a<star_checker2; a++)//Create array for length last word
			{
				middle_controller=0;
				middle_controller1=0;
				//All possibilities are scanned between middle and last indices.
				for (int b=star_checker_arr1[i]; b<star_checker_arr2[a]; b++)
				{
					if(star_checker_arr1[i]<star_checker_arr2[a])//If the middle index is less then the last index
					{
						middle_controller=1;//controller checked
					}
					for(int c=0; c<star_checker3; c++)//Checking the space character between two indexes.
					{
						if (b==star_checker_arr3[c])
						{
						middle_controller1=1;//controller checked
						}
					}
				}
				//cout<<endl;
				if (middle_controller==1&&middle_controller1==0)//if both spaces and index values are provided
				{
				middle_to_last[middle_to_last_counter]=star_checker_arr1[i];//insert word position to middle_to_last
				middle_to_last_counter++;
				replace_arr[replace_counter]=star_checker_arr2[a];//the end index of the character is stored
				replace_counter++;
				}
			}
		}
		cout<<endl;
		for(int i=0; i<begin_to_middle_counter; i++) //Create array for length begin_to_middle 
		{
			for(int a=0; a<middle_to_last_counter; a++)//Create array for length middle_to_last 
			{
				last_controller=0;
				last_controller1=0;
				//All possibilities are scanned between middle and last indices.
				for (int b=begin_to_middle[i]; b<middle_to_last[a]; b++)
				{
					if(begin_to_middle[i]<middle_to_last[a])//If the begin_to_middle index is less then the middle_to_last
					{
						last_controller=1;//Controller Checked
					}
					for(int c=0; c<star_checker3; c++)//Checking the space character between two indexes.
					{
						if (b==star_checker_arr3[c])
						{
						last_controller1=1;//controller checked
						}
					}
				}
				//cout<<endl;
				if (last_controller==1&&last_controller1==0)//if both spaces and index values are provided
				{
				//cout<<result1[i]<<" ";
				result[result_counter]=begin_to_middle[i];//insert word position to result
				result_counter++;
				}
			}
		}
		//The procedure for finding the indexes of the last letters of the word indexes found
		
		for(int i=0; i<result_counter; i++) //Create array for length result_counter 
		{
			for(int a=0; a<replace_counter; a++)//Create array for length replace_counter 
			{
				//Controller
				position_control=0;
				position_control1=0;
				//All possibilities are scanned between result_counter and replace_counter indices.
				for (int b=result[i]; b<replace_arr[a]; b++)
				{
					if(result[i]<replace_arr[a])//If the result index is less then the replace_arr
					{
						position_control=1;//Controller Checked
					}
					for(int c=0; c<star_checker3; c++)//Space Checker
					{
						if (b==star_checker_arr3[c])//Checking the space character between two indexes.
						{
						position_control1=1;//controller checked
						}
					}
			}
			//cout<<endl;
			if (position_control==1&&position_control1==0)//if both spaces and index values are provided
			{
			//cout<<replace_arr[a]<<" ";
			replace_arr1[replace_counter1]=replace_arr[a];//insert word finished position to replace_arr
			replace_counter1++;
			//result[result_counter]=result1[i];
			//result_counter++;
			}
		}
	}
	cout<<endl;	
	}
	
	for (int a=0; a<result_counter; a++){
		cout<<result[a]<<" ";
	}
	cout<<endl;
	for (int a=0; a<replace_counter1; a++){
	cout<<replace_arr1[a]<<" ";
	}
	cout<<endl;
	
	cout<<"One Star Process Result Number of found: "<<star_checker<<endl;//One Star Result
	cout<<"Two Star Begin to End Process Number of found:"<<star_checker1<<endl;//Two Star Result
	cout<<"In the Middle Process Number of found: "<<result_counter<<endl;//Two Star Star position between words
	
	
}

void WordOperation::EraseWordWithStar(string Word)
{
	//Local Variable
	cout<<endl;
	int erase_count=0;
	int erase_control_bit=0;
	int controller=0;
	int counter=0;

	FindWordWithStar(Word,Readed_Document); //Search word in the document
	cout<<endl;
	cout<<Readed_Document<<endl;
	
	for (int b=0; b<result_counter; b++)//Create loop size of result counter
	{
		erase_count=replace_arr1[b]-result[b]+1;//Remove the starting index from the last index of the word and add 1 to delete the last index.
		if(erase_control_bit==0)//If deletion not happened
		{
			Readed_Document.erase(result[b],erase_count);//Delete starting from the index word found in the document
			erase_control_bit++;//increment erase_control_bit
			controller=erase_count;
		}
		else
		{
			cout<<controller<<endl;
			Readed_Document.erase(result[b]-controller,erase_count);
			cout<<b;
			controller=erase_count+controller;
		}
	}
	cout<<Readed_Document<<endl;
	//tut=0;
}


void WordOperation::UserCommands()
{
	//Local Variables	
	string Operation ;
	string path;
	string Searched_Word;
	string Replaced_Word;
	string Deleted_Word;
	
	cout << "Enter the path to the file you want to process: "; 
	getline (cin, path);// Getting the path of the file to be processed.
	
	cout << "Choose your operation type; F(Find),R(Replace),D(Delete):";
	getline (cin, Operation); //The transaction information to be performed is received.
	
	if (Operation=="F")
	{
	cout << "Searched Words: ";
	getline (cin, Searched_Word);//The word information to be searched is obtained.
	OpenText(path);
	StarCheckProcess(star_check,Searched_Word);
	LineCheckProcess(line_check,Searched_Word);
	//cout<<Readed_Document<<endl;
	if (star_checkerr!=0 && line_checker==0)
	{

		FindWordWithStar(Searched_Word,Readed_Document);//Calling Word Search Function
	}
	else if (star_checkerr==0 && line_checker!=0)
	{
		FindWordLine(Searched_Word,Readed_Document);//Calling Word Search Function
	}
	else if (star_checkerr==0 && line_checker==0)
	{
		FindWordLine(Searched_Word,Readed_Document);//Calling Word Search Function
	}
	else
	{
		cout<<"You can only use line or star";
	}
	
	}
	else if (Operation=="R")
	{
	cout << "Searched Words: ";
	getline (cin, Searched_Word);//Getting the word information contained in the text.
	cout << "Replace Words: ";
	getline (cin, Replaced_Word);//The word information to be changed is received.
	OpenText(path);
	cout<<Readed_Document<<endl;
	
	StarCheckProcess(star_check,Searched_Word);
	LineCheckProcess(line_check,Searched_Word);
	//cout<<Readed_Document<<endl;
	cout<<star_checkerr;
	if (star_checkerr!=0 && line_checker==0)
	{
		//FindWordWithStar(Searched_Word,Readed_Document);//Calling Word Search Function
	}
	else if (star_checkerr==0 && line_checker!=0)
	{
		ReplaceWord(Searched_Word,Replaced_Word);//The word exchange function is called.
	}
	else if (star_checkerr==0 && line_checker==0)
	{
		ReplaceWord(Searched_Word,Replaced_Word);//Calling Word Search Function
	}
	else
	{
		cout<<"You can only use line or star";
	}
	
	}
	else if (Operation=="D")
	{
	cout << "Deleted Word: ";
	getline (cin,Deleted_Word);//The word information to be changed is deleted.
	OpenText(path);
	cout<<Readed_Document<<endl;
	StarCheckProcess(star_check,Deleted_Word);
	LineCheckProcess(line_check,Deleted_Word);
	if (star_checkerr!=0 && line_checker==0)
	{
		EraseWordWithStar(Deleted_Word);// The word deleted function is called.
	}
	else if (star_checkerr==0 && line_checker!=0)
	{
		EraseWord(Deleted_Word);//The word exchange function is called.
	}
	else if (star_checkerr==0 && line_checker==0)
	{
		EraseWord(Deleted_Word);//Calling Word Search Function
	}
	else
	{
		cout<<"You can only use line or star";
	}
	
	}
	else
	{
	cout<<"Invalid Operation";// Error Status Information
	}

}


void WordOperation::LineCheckProcess(string Searched_Word,string Searched_Place)
{
	//Local Variables	
	int index;
	int word_position = 0;

	while((index = Searched_Place.find(Searched_Word, word_position)) != string::npos) // Search for the position of the word in the file being read
	{ 
		//kelime arama
		//cout << "Match found at position: " << index << endl;
		word_position = index + 1; //New position is from next element of index
		line_checker_arr[line_checker]=index;// Assign line_checker_arr's position in line_checker to line position in the word
		line_checker++;//increment line values
	}
}

void WordOperation::FindWord(string Searched_Word,string Searched_Place)
{
		
	//Local Variables
	int word_positionn=0;
	word_positionn=0;
	indexx=0;

	while((indexx = Searched_Place.find(Searched_Word, word_positionn)) != string::npos) // Search for the position of the word in the file being read
	{
		cout << "Match found at position: " << indexx << endl;
		word_positionn = indexx + 1; //New position is from next element of index
		index_position_arr1[index_position_arr_counter1]=indexx;// Assign index_position_arr1's position in index_position_arr_counter1 to word position in the document
		index_position_arr_counter1++; // increment word values
	}
	sort(index_position_arr1, index_position_arr1 + index_position_arr_counter1);// Sorting the value smallest to bigger

}

void WordOperation::FindWordLine(string Searched_Word,string Searched_Place)
{

	string alphabet="abcdefghijklmnopqrstuvwxyz"; // Alphabet letter declaration
	//LineCheckProcess(line_check,Searched_Word); // Check line values and line position

	if (line_checker==0) //If there is no line
	{
		FindWord(Searched_Word,Searched_Place);// Directly search the word
		cout<<"Result of find process: "<<index_position_arr_counter1<<endl;
	}
		
	else if (line_checker==1)// If there is one line
	{
		for (int b = 0; b < alphabet.length(); b++)
		{
			Searched_Word[line_checker_arr[0]]=alphabet[b];//Each element of the alphabet sequence is followed by the line in the word searched, and a new sentence is formed.
			FindWord(Searched_Word,Searched_Place);// Search new word
		}
		cout<<"Result of find process: "<<index_position_arr_counter1<<endl;
	}
	else if (line_checker==2)// If there is one line
	{
		for (int c = 0; c < alphabet.length(); c++)
		{
			Searched_Word[line_checker_arr[0]]=alphabet[c];//An element of the alphabet sequence is left fixed to the first line in the search word.
			for(int d=0; d<alphabet.length(); d++)
			{
				Searched_Word[line_checker_arr[1]]=alphabet[d];//On the right line, all the elements of the alphabet sequence are given in order. Thus, all possibilities that may occur are tested.
				FindWord(Searched_Word,Searched_Place);//Search new word
			}
		}
		cout<<"Result of find process: "<<index_position_arr_counter1<<endl;
	}
	else
	{
		cout<<"You can use up to 2 -."; // Warning 
	}
}

void WordOperation::ReplaceWord(string Original,string Desired)
{
	//Local Variables
	int replace_length=0;
	int replace_array_control_values=0;
	
	FindWordLine(Original,Readed_Document);// FindWordLine function is called and the entered word is searched in the document.
	//kelime deðiþtirme
	if ((Desired.length()-Original.length())>0 && indexx!=0)// If not in the starting position and replacing word length greater than 0 
	{
		replace_length=Desired.length()-Original.length(); // replace length changed in the desired_length-original_length
														   //In this way, the problem of shifting due to the length of the word to be changed is prevented.
	}
	else 
	{
		replace_length=0;
	}
	for (int b=0; b<index_position_arr_counter1; b++) //index_position_arr_counter1 the number of found words
	{
		replace_array_control_values = b*replace_length;//The location is updated by multiplying replace length with the location index in the text.
		Readed_Document.replace(index_position_arr1[b]+replace_array_control_values,Desired.length()-replace_length,Desired);// With the updated control value, index position is called with the value in arr and replaced with the size of the desired word.
	}
	
	cout<<Readed_Document<<endl;// Print result of Replace Operation
} 

void WordOperation::EraseWord(string word)
{
	//Local Variables
	int erase_count=0;
	int erase_control_bit=0;
	FindWordLine(word,Readed_Document);// FindWordLine function is called and the entered word is searched in the document.
	erase_count=word.length();//the length of word which has wanted to be deleted is assigned.
	
	for (int b=0; b<index_position_arr_counter1; b++) //index_position_arr_counter1 the number of found words
	{	
		if(erase_control_bit==0)// If the first deletion
		{
		Readed_Document.erase(index_position_arr1[b],erase_count);//Length of the word is deleted from the word position in the document read.
		erase_control_bit++;	
		}
		else
		{
		Readed_Document.erase(index_position_arr1[b]-(b*erase_count),erase_count);//Length of the word is deleted from the word position in the document read.
																				  //It can prevent the slipping problem caused by the words deleted from the document.
																				  //The position of the newly created text is taken under control by multiplying the number of deleted words by the length of the deleted word.
		}
	}
	cout<<Readed_Document<<endl;
}


int main(){
	
	WordOperation Exp;
	Exp.UserCommands();

}

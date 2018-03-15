#include <dirent.h>
#include <sys/stat.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>

using namespace std;

//adding comment 

//adding second comment

void explore(char *dir_name){
   DIR *dir; //pointer to an open directory
   struct dirent *entry; //stuff in the directory
   struct stat info; //information about each entry

   //1 open
   dir = opendir(dir_name);
   if(!dir){
      cout << "Directory was not found\n" << endl;
      return;
   }
   int file_count = 0;
   int folder_count = 0;
   int total_file_size = 0;
   //2 read
   while( (entry = readdir(dir)) != NULL){
      if( entry->d_name[0]  != '.'){
         string path = string(dir_name) + "/" + string(entry->d_name);
         cout << "Entry = " << path << endl;
         stat(path.c_str(),&info); //
         if(S_ISDIR(info.st_mode)){
            folder_count++;
            explore((char*)path.c_str());
         }
         else{
            file_count++;
	    stat(dir_name, &info);
   	    total_file_size += info.st_size;
         }
      }
   }
   cout << "Directory " << dir_name << " has " << file_count << " files" << endl;
	cout << "Directory: " << dir_name << " has " << folder_count << " directories" << endl;

 cout << "total file size is " << total_file_size << " bytes" << endl; 
 //3 close
   closedir(dir);

}

static int version = 10;

void displayVersion(){
	cout << "Version: " << version << ".\n " << endl;
}

int main(int argc, char ** argv)
{

	displayVersion();
   //should this be the argument we accept?
	if(argc == 2)
    explore((char*)argv[1]);
	else
	{
		explore((char*)".");
	}
    return 0;
}

#include <iostream>

#include "Data.h"

using namespace std;


int main() {
	//create the Image Object
    Data myImage("/home/pd-laptop/myDocuments/GitRepo/Image_processing_counting_stars/counting_stars.raw");

    unsigned char* buff = myImage.getBuffer();
	int height = 3456;
	int width = 5184;
	int size = (height*width);
	myImage.setSize(size);
    int star_count = 0;

	//load the buffer into a datamap so we can semi-visualize
	vector< vector <unsigned int> > dataMap(height, vector <unsigned int> (width));
	int bufferCounter = 0;
	for(int a = 0; a < height; ++a){
		for(int b = 0; b < width; ++b){
			dataMap[a][b] = (unsigned int)buff[bufferCounter];
			bufferCounter++;
		}
	}

	//check surrounding for peaks, do not include
	for(int x = 1; x < height-1; ++x){
		for(int y = 1; y < width-1; ++y){

			if(dataMap[x][y] > dataMap[x-1][y-1]
					&& dataMap[x][y] >= dataMap[x-1][y]
						&& dataMap[x][y] > dataMap[x-1][y+1]
						   && dataMap[x][y] >= dataMap[x][y-1]
							  && dataMap[x][y] >= dataMap[x][y+1]
							  	&& dataMap[x][y] > dataMap[x+1][y-1]
							  		&& dataMap[x][y] >= dataMap[x+1][y]
			   							&& dataMap[x][y] > dataMap[x+1][y+1]
					) {
				++star_count;
			}
		}
	}

    cout<<"The number of stars is: "<<star_count<<endl;

    myImage.writeData("/home/pd-laptop/myDocuments/GitRepo/Image_processing_counting_stars/output.raw");
    cout<<"finished writing..."<<endl;

	delete [] buff;

	cin.get();
	return 0;
}
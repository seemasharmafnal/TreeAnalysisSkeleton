#define AnalyzeLightBSM_cxx
#include "AnalyzeLightBSM.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <fstream>
#include"TGraphErrors.h"
#include"TGraphAsymmErrors.h"
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"
#pragma link C++ class std::vector< std::vector >+; 
#pragma link C++ class std::vector< TLorentzVector >+;
#ifdef __CINT__
#pragma link C++ class std::vector<TLorentzVector>+;
#endif
using namespace TMVA;
int main(int argc, char* argv[])
{

  if (argc < 3) {
    cerr << "Please give 3 arguments " << "inputFileList " << " " << "outputFileName" << " " << "DetectorType" <<endl;
    return -1;
  }
  const char *inputFileList = argv[1];
  const char *outFileName   = argv[2];
  const char *detType          = argv[3];

  AnalyzeLightBSM ana(inputFileList, outFileName,detType);
  cout << "Detector type " << detType << endl;
  cout<<inputFileList <<"\t"<<outFileName<<"\t"<<detType<<endl;
  ana.EventLoop(detType,inputFileList,outFileName);
  Tools::Instance();
  return 0;
}

void AnalyzeLightBSM::EventLoop(const char *detType,const char *inputFileList, const char *outFileName) {
  cout<<"inside event loop"<<endl;
  if (fChain == 0) return;
  Long64_t nentries = fChain->GetEntriesFast();
  cout << "nentries " << nentries << endl;
  cout << "Analyzing data from " << detType << " " << endl;

   Long64_t nbytes = 0, nb = 0;
   int decade = 0;
   bool Debug=false;
  
    for (Long64_t jentry=0; jentry<nentries;jentry++)
      {
	double progress = 10.0 * jentry / (1.0 * nentries);
	int k = int (progress);
	if (k > decade)
	  cout << 10 * k << " %" << endl;
	decade = k;
	
	// ===============read this entry == == == == == == == == == == ==                                                                        
	Long64_t ientry = LoadTree(jentry);
	if(Debug)
	  cout<<"===load tree entry ==="<<jentry<<endl;
	if (ientry < 0) break;
	nb = fChain->GetEntry(jentry);   nbytes += nb;
	if(Debug)
	  cout<<"===load tree entry ==="<<jentry<<endl;

	  // do something with tree branches here

      }
}

//
//  ofxTSPS::OpenCvProcessor.h
//  openTSPS
//
//  Created by Brett Renfer on 7/12/12.
//  Copyright (c) 2012 Rockwell Group. All rights reserved.
//

#pragma once

#include "ofxTSPS/Processor.h"
#include "ofxTSPS/opencv/OpenCvPerson.h"

#include "ofxOpenCv.h"
#include "ofxCvHaarTracker.h"
#include "ofxCvOpticalFlowLK.h"
#include "ofxCvBlobTracker.h"

namespace ofxTSPS {
    class OpenCvProcessor : public Processor, public ofxCvBlobListener {
    public:
        
        OpenCvProcessor();
        
        void draw();
        
        // step 0: camera
        void setCameraImage( ofBaseImage & image );
        
        // step 1: background
        void captureBackground( ofBaseImage & image );
        ofPixelsRef progressiveBackground( ofBaseImage & image, float amount );
        
        void blankBackground();
        
        // step 2: difference
        ofPixelsRef difference( ofBaseImage & image, TrackingType trackingType );
        
        // step 3: process
        ofPixelsRef process ( ofBaseImage & image );
        void processOpticalFlow( ofBaseImage & image );
        void processHaar( ofBaseImage & image );
        
        // methods: utils
        void resize( int camWidth, int camHeight );
        
        // settings
        void setOpticalflowMinMax( float min = 0.0, float max = 10.0 );
        void setHaarXMLFile( string xmlFile );
        
        // ofxCvBlobListener functions
        void blobOn( int x, int y, int id, int order );
        void blobMoved( int x, int y, int id, int order );
        void blobOff( int x, int y, int id, int order );
        
    protected:
        void setupProcessor();
        
    private:
        ofxCvGrayscaleImage dummyImage;
        
        // haar tracking
        ofxLABCvHaarFinder  haarFinder;
        ofxCvHaarTracker    haarTracker;
        ofxCvGrayscaleImage haarImage;
        
        // contour tracking 
        ofxCvContourFinder 	contourFinder;
        ofxCvBlobTracker    persistentTracker;
        
        // optical flow
        ofxCvOpticalFlowLK	opticalFlow;
        ofxCvGrayscaleImage opticalFlowImage, opticalFlowLastImage;
        
        // cv images
        ofxCvGrayscaleImage grayImg;            // stores camera image
        ofxCvGrayscaleImage grayBg;             // bg to subtract
        ofxCvShortImage		floatBgImg;         // progressive background image
        
        ofxCvGrayscaleImage	grayDiff;
    };
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int sampleSize; int rate; int totalBytes; int format; int channels; int bits; } ;
struct TYPE_4__ {int framePeriod; int maxRecordSize; int frameRate; int numVideoFrames; int width; int height; scalar_t__ moviOffset; TYPE_1__ a; scalar_t__ audio; scalar_t__ motionJpeg; scalar_t__ chunkStackTop; } ;

/* Variables and functions */
 int /*<<< orphan*/  END_CHUNK () ; 
 int /*<<< orphan*/  START_CHUNK (char*) ; 
 int /*<<< orphan*/  WRITE_2BYTES (int) ; 
 int /*<<< orphan*/  WRITE_4BYTES (int) ; 
 int /*<<< orphan*/  WRITE_STRING (char*) ; 
 TYPE_2__ afd ; 
 scalar_t__ bufIndex ; 

void CL_WriteAVIHeader( void )
{
  bufIndex = 0;
  afd.chunkStackTop = 0;

  START_CHUNK( "RIFF" );
  {
    WRITE_STRING( "AVI " );
    {
      START_CHUNK( "LIST" );
      {
        WRITE_STRING( "hdrl" );
        WRITE_STRING( "avih" );
        WRITE_4BYTES( 56 );                     //"avih" "chunk" size
        WRITE_4BYTES( afd.framePeriod );        //dwMicroSecPerFrame
        WRITE_4BYTES( afd.maxRecordSize *
            afd.frameRate );                    //dwMaxBytesPerSec
        WRITE_4BYTES( 0 );                      //dwReserved1
        WRITE_4BYTES( 0x110 );                  //dwFlags bits HAS_INDEX and IS_INTERLEAVED
        WRITE_4BYTES( afd.numVideoFrames );     //dwTotalFrames
        WRITE_4BYTES( 0 );                      //dwInitialFrame

        if( afd.audio )                         //dwStreams
          WRITE_4BYTES( 2 );
        else
          WRITE_4BYTES( 1 );

        WRITE_4BYTES( afd.maxRecordSize );      //dwSuggestedBufferSize
        WRITE_4BYTES( afd.width );              //dwWidth
        WRITE_4BYTES( afd.height );             //dwHeight
        WRITE_4BYTES( 0 );                      //dwReserved[ 0 ]
        WRITE_4BYTES( 0 );                      //dwReserved[ 1 ]
        WRITE_4BYTES( 0 );                      //dwReserved[ 2 ]
        WRITE_4BYTES( 0 );                      //dwReserved[ 3 ]

        START_CHUNK( "LIST" );
        {
          WRITE_STRING( "strl" );
          WRITE_STRING( "strh" );
          WRITE_4BYTES( 56 );                   //"strh" "chunk" size
          WRITE_STRING( "vids" );

          if( afd.motionJpeg )
            WRITE_STRING( "MJPG" );
          else
            WRITE_4BYTES( 0 );                  // BI_RGB

          WRITE_4BYTES( 0 );                    //dwFlags
          WRITE_4BYTES( 0 );                    //dwPriority
          WRITE_4BYTES( 0 );                    //dwInitialFrame

          WRITE_4BYTES( 1 );                    //dwTimescale
          WRITE_4BYTES( afd.frameRate );        //dwDataRate
          WRITE_4BYTES( 0 );                    //dwStartTime
          WRITE_4BYTES( afd.numVideoFrames );   //dwDataLength

          WRITE_4BYTES( afd.maxRecordSize );    //dwSuggestedBufferSize
          WRITE_4BYTES( -1 );                   //dwQuality
          WRITE_4BYTES( 0 );                    //dwSampleSize
          WRITE_2BYTES( 0 );                    //rcFrame
          WRITE_2BYTES( 0 );                    //rcFrame
          WRITE_2BYTES( afd.width );            //rcFrame
          WRITE_2BYTES( afd.height );           //rcFrame

          WRITE_STRING( "strf" );
          WRITE_4BYTES( 40 );                   //"strf" "chunk" size
          WRITE_4BYTES( 40 );                   //biSize
          WRITE_4BYTES( afd.width );            //biWidth
          WRITE_4BYTES( afd.height );           //biHeight
          WRITE_2BYTES( 1 );                    //biPlanes
          WRITE_2BYTES( 24 );                   //biBitCount

          if( afd.motionJpeg )                  //biCompression
          {
            WRITE_STRING( "MJPG" );
            WRITE_4BYTES( afd.width *
                afd.height );                   //biSizeImage
          }
          else
          {
            WRITE_4BYTES( 0 );                  // BI_RGB
            WRITE_4BYTES( afd.width *
                afd.height * 3 );               //biSizeImage
          }

          WRITE_4BYTES( 0 );                    //biXPelsPetMeter
          WRITE_4BYTES( 0 );                    //biYPelsPetMeter
          WRITE_4BYTES( 0 );                    //biClrUsed
          WRITE_4BYTES( 0 );                    //biClrImportant
        }
        END_CHUNK( );

        if( afd.audio )
        {
          START_CHUNK( "LIST" );
          {
            WRITE_STRING( "strl" );
            WRITE_STRING( "strh" );
            WRITE_4BYTES( 56 );                 //"strh" "chunk" size
            WRITE_STRING( "auds" );
            WRITE_4BYTES( 0 );                  //FCC
            WRITE_4BYTES( 0 );                  //dwFlags
            WRITE_4BYTES( 0 );                  //dwPriority
            WRITE_4BYTES( 0 );                  //dwInitialFrame

            WRITE_4BYTES( afd.a.sampleSize );   //dwTimescale
            WRITE_4BYTES( afd.a.sampleSize *
                afd.a.rate );                   //dwDataRate
            WRITE_4BYTES( 0 );                  //dwStartTime
            WRITE_4BYTES( afd.a.totalBytes /
                afd.a.sampleSize );             //dwDataLength

            WRITE_4BYTES( 0 );                  //dwSuggestedBufferSize
            WRITE_4BYTES( -1 );                 //dwQuality
            WRITE_4BYTES( afd.a.sampleSize );   //dwSampleSize
            WRITE_2BYTES( 0 );                  //rcFrame
            WRITE_2BYTES( 0 );                  //rcFrame
            WRITE_2BYTES( 0 );                  //rcFrame
            WRITE_2BYTES( 0 );                  //rcFrame

            WRITE_STRING( "strf" );
            WRITE_4BYTES( 18 );                 //"strf" "chunk" size
            WRITE_2BYTES( afd.a.format );       //wFormatTag
            WRITE_2BYTES( afd.a.channels );     //nChannels
            WRITE_4BYTES( afd.a.rate );         //nSamplesPerSec
            WRITE_4BYTES( afd.a.sampleSize *
                afd.a.rate );                   //nAvgBytesPerSec
            WRITE_2BYTES( afd.a.sampleSize );   //nBlockAlign
            WRITE_2BYTES( afd.a.bits );         //wBitsPerSample
            WRITE_2BYTES( 0 );                  //cbSize
          }
          END_CHUNK( );
        }
      }
      END_CHUNK( );

      afd.moviOffset = bufIndex;

      START_CHUNK( "LIST" );
      {
        WRITE_STRING( "movi" );
      }
    }
  }
}
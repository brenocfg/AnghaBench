#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  raw ;
typedef  int /*<<< orphan*/  byte ;
struct TYPE_9__ {int speed; } ;
struct TYPE_6__ {int rate; int width; int channels; } ;
struct TYPE_8__ {TYPE_1__ info; } ;
struct TYPE_7__ {scalar_t__ value; } ;

/* Variables and functions */
 scalar_t__ MAX_RAW_SAMPLES ; 
 int /*<<< orphan*/  S_Base_RawSamples (int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  S_Base_StopBackgroundTrack () ; 
 int S_CodecReadStream (TYPE_3__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OpenBackgroundStream (scalar_t__*) ; 
 TYPE_4__ dma ; 
 scalar_t__* s_backgroundLoop ; 
 TYPE_3__* s_backgroundStream ; 
 TYPE_2__* s_musicVolume ; 
 scalar_t__* s_rawend ; 
 scalar_t__ s_soundtime ; 

void S_UpdateBackgroundTrack( void ) {
	int		bufferSamples;
	int		fileSamples;
	byte	raw[30000];		// just enough to fit in a mac stack frame
	int		fileBytes;
	int		r;

	if(!s_backgroundStream) {
		return;
	}

	// don't bother playing anything if musicvolume is 0
	if ( s_musicVolume->value <= 0 ) {
		return;
	}

	// see how many samples should be copied into the raw buffer
	if ( s_rawend[0] < s_soundtime ) {
		s_rawend[0] = s_soundtime;
	}

	while ( s_rawend[0] < s_soundtime + MAX_RAW_SAMPLES ) {
		bufferSamples = MAX_RAW_SAMPLES - (s_rawend[0] - s_soundtime);

		// decide how much data needs to be read from the file
		fileSamples = bufferSamples * s_backgroundStream->info.rate / dma.speed;

		if (!fileSamples)
			return;

		// our max buffer size
		fileBytes = fileSamples * (s_backgroundStream->info.width * s_backgroundStream->info.channels);
		if ( fileBytes > sizeof(raw) ) {
			fileBytes = sizeof(raw);
			fileSamples = fileBytes / (s_backgroundStream->info.width * s_backgroundStream->info.channels);
		}

		// Read
		r = S_CodecReadStream(s_backgroundStream, fileBytes, raw);
		if(r < fileBytes)
		{
			fileSamples = r / (s_backgroundStream->info.width * s_backgroundStream->info.channels);
		}

		if(r > 0)
		{
			// add to raw buffer
			S_Base_RawSamples(0, fileSamples, s_backgroundStream->info.rate,
				s_backgroundStream->info.width, s_backgroundStream->info.channels, raw, s_musicVolume->value, -1);
		}
		else
		{
			// loop
			if(s_backgroundLoop[0])
			{
				S_OpenBackgroundStream( s_backgroundLoop );
				if(!s_backgroundStream)
					return;
			}
			else
			{
				S_Base_StopBackgroundTrack();
				return;
			}
		}

	}
}
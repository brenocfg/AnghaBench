#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {short left; short right; } ;
typedef  TYPE_1__ portable_samplepair_t ;
typedef  int byte ;
struct TYPE_11__ {float speed; } ;
struct TYPE_10__ {int /*<<< orphan*/  origin; } ;
struct TYPE_9__ {scalar_t__ integer; } ;
struct TYPE_8__ {int value; } ;

/* Variables and functions */
 int /*<<< orphan*/  Com_DPrintf (char*,int,int) ; 
 int MAX_GENTITIES ; 
 int MAX_RAW_SAMPLES ; 
 int MAX_RAW_STREAMS ; 
 int /*<<< orphan*/  S_SpatializeOrigin (int /*<<< orphan*/ ,int,int*,int*) ; 
 TYPE_6__ dma ; 
 TYPE_5__* loopSounds ; 
 TYPE_4__* s_muted ; 
 int* s_rawend ; 
 TYPE_1__** s_rawsamples ; 
 scalar_t__ s_soundMuted ; 
 int /*<<< orphan*/  s_soundStarted ; 
 int s_soundtime ; 
 TYPE_2__* s_volume ; 

void S_Base_RawSamples( int stream, int samples, int rate, int width, int s_channels, const byte *data, float volume, int entityNum)
{
	int		i;
	int		src, dst;
	float	scale;
	int		intVolumeLeft, intVolumeRight;
	portable_samplepair_t *rawsamples;

	if ( !s_soundStarted || s_soundMuted ) {
		return;
	}

	if ( (stream < 0) || (stream >= MAX_RAW_STREAMS) ) {
		return;
	}

	rawsamples = s_rawsamples[stream];

	if ( s_muted->integer ) {
		intVolumeLeft = intVolumeRight = 0;
	} else {
		int leftvol, rightvol;

		if ( entityNum >= 0 && entityNum < MAX_GENTITIES ) {
			// support spatialized raw streams, e.g. for VoIP
			S_SpatializeOrigin( loopSounds[ entityNum ].origin, 256, &leftvol, &rightvol );
		} else {
			leftvol = rightvol = 256;
		}

		intVolumeLeft = leftvol * volume * s_volume->value;
		intVolumeRight = rightvol * volume * s_volume->value;
	}

	if ( s_rawend[stream] < s_soundtime ) {
		Com_DPrintf( "S_Base_RawSamples: resetting minimum: %i < %i\n", s_rawend[stream], s_soundtime );
		s_rawend[stream] = s_soundtime;
	}

	scale = (float)rate / dma.speed;

//Com_Printf ("%i < %i < %i\n", s_soundtime, s_paintedtime, s_rawend[stream]);
	if (s_channels == 2 && width == 2)
	{
		if (scale == 1.0)
		{	// optimized case
			for (i=0 ; i<samples ; i++)
			{
				dst = s_rawend[stream]&(MAX_RAW_SAMPLES-1);
				s_rawend[stream]++;
				rawsamples[dst].left = ((short *)data)[i*2] * intVolumeLeft;
				rawsamples[dst].right = ((short *)data)[i*2+1] * intVolumeRight;
			}
		}
		else
		{
			for (i=0 ; ; i++)
			{
				src = i*scale;
				if (src >= samples)
					break;
				dst = s_rawend[stream]&(MAX_RAW_SAMPLES-1);
				s_rawend[stream]++;
				rawsamples[dst].left = ((short *)data)[src*2] * intVolumeLeft;
				rawsamples[dst].right = ((short *)data)[src*2+1] * intVolumeRight;
			}
		}
	}
	else if (s_channels == 1 && width == 2)
	{
		for (i=0 ; ; i++)
		{
			src = i*scale;
			if (src >= samples)
				break;
			dst = s_rawend[stream]&(MAX_RAW_SAMPLES-1);
			s_rawend[stream]++;
			rawsamples[dst].left = ((short *)data)[src] * intVolumeLeft;
			rawsamples[dst].right = ((short *)data)[src] * intVolumeRight;
		}
	}
	else if (s_channels == 2 && width == 1)
	{
		intVolumeLeft *= 256;
		intVolumeRight *= 256;

		for (i=0 ; ; i++)
		{
			src = i*scale;
			if (src >= samples)
				break;
			dst = s_rawend[stream]&(MAX_RAW_SAMPLES-1);
			s_rawend[stream]++;
			rawsamples[dst].left = ((char *)data)[src*2] * intVolumeLeft;
			rawsamples[dst].right = ((char *)data)[src*2+1] * intVolumeRight;
		}
	}
	else if (s_channels == 1 && width == 1)
	{
		intVolumeLeft *= 256;
		intVolumeRight *= 256;

		for (i=0 ; ; i++)
		{
			src = i*scale;
			if (src >= samples)
				break;
			dst = s_rawend[stream]&(MAX_RAW_SAMPLES-1);
			s_rawend[stream]++;
			rawsamples[dst].left = (((byte *)data)[src]-128) * intVolumeLeft;
			rawsamples[dst].right = (((byte *)data)[src]-128) * intVolumeRight;
		}
	}

	if ( s_rawend[stream] > s_soundtime + MAX_RAW_SAMPLES ) {
		Com_DPrintf( "S_Base_RawSamples: overflowed %i > %i\n", s_rawend[stream], s_soundtime );
	}
}
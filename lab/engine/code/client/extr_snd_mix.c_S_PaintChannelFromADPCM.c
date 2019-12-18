#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {struct TYPE_10__* next; } ;
typedef  TYPE_1__ sndBuffer ;
struct TYPE_11__ {TYPE_1__* soundData; } ;
typedef  TYPE_2__ sfx_t ;
struct TYPE_12__ {int left; int right; } ;
typedef  TYPE_3__ portable_samplepair_t ;
struct TYPE_13__ {int leftvol; int rightvol; int oldDopplerScale; scalar_t__ doppler; } ;
typedef  TYPE_4__ channel_t ;

/* Variables and functions */
 int SND_CHUNK_SIZE ; 
 int /*<<< orphan*/  S_AdpcmGetSamples (TYPE_1__*,short*) ; 
 TYPE_3__* paintbuffer ; 
 short* sfxScratchBuffer ; 
 int sfxScratchIndex ; 
 TYPE_2__* sfxScratchPointer ; 
 int snd_vol ; 

void S_PaintChannelFromADPCM( channel_t *ch, sfx_t *sc, int count, int sampleOffset, int bufferOffset ) {
	int						data;
	int						leftvol, rightvol;
	int						i;
	portable_samplepair_t	*samp;
	sndBuffer				*chunk;
	short					*samples;

	leftvol = ch->leftvol*snd_vol;
	rightvol = ch->rightvol*snd_vol;

	i = 0;
	samp = &paintbuffer[ bufferOffset ];
	chunk = sc->soundData;

	if (ch->doppler) {
		sampleOffset = sampleOffset*ch->oldDopplerScale;
	}

	while (sampleOffset>=(SND_CHUNK_SIZE*4)) {
		chunk = chunk->next;
		sampleOffset -= (SND_CHUNK_SIZE*4);
		i++;
	}

	if (i!=sfxScratchIndex || sfxScratchPointer != sc) {
		S_AdpcmGetSamples( chunk, sfxScratchBuffer );
		sfxScratchIndex = i;
		sfxScratchPointer = sc;
	}

	samples = sfxScratchBuffer;

	for ( i=0 ; i<count ; i++ ) {
		data  = samples[sampleOffset++];
		samp[i].left += (data * leftvol)>>8;
		samp[i].right += (data * rightvol)>>8;

		if (sampleOffset == SND_CHUNK_SIZE*4) {
			chunk = chunk->next;
			S_AdpcmGetSamples( chunk, sfxScratchBuffer);
			sampleOffset = 0;
			sfxScratchIndex++;
		}
	}
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {short* sndChunk; struct TYPE_8__* next; } ;
typedef  TYPE_1__ sndBuffer ;
struct TYPE_9__ {int soundChannels; TYPE_1__* soundData; } ;
typedef  TYPE_2__ sfx_t ;
struct TYPE_10__ {int left; int right; } ;
typedef  TYPE_3__ portable_samplepair_t ;
struct TYPE_11__ {int oldDopplerScale; float dopplerScale; int leftvol; int rightvol; scalar_t__ doppler; } ;
typedef  TYPE_4__ channel_t ;

/* Variables and functions */
 int SND_CHUNK_SIZE ; 
 TYPE_3__* paintbuffer ; 
 int snd_vol ; 

__attribute__((used)) static void S_PaintChannelFrom16_scalar( channel_t *ch, const sfx_t *sc, int count, int sampleOffset, int bufferOffset ) {
	int						data, aoff, boff;
	int						leftvol, rightvol;
	int						i, j;
	portable_samplepair_t	*samp;
	sndBuffer				*chunk;
	short					*samples;
	float					ooff, fdata[2], fdiv, fleftvol, frightvol;

	if (sc->soundChannels <= 0) {
		return;
	}

	samp = &paintbuffer[ bufferOffset ];

	if (ch->doppler) {
		sampleOffset = sampleOffset*ch->oldDopplerScale;
	}

	if ( sc->soundChannels == 2 ) {
		sampleOffset *= sc->soundChannels;

		if ( sampleOffset & 1 ) {
			sampleOffset &= ~1;
		}
	}

	chunk = sc->soundData;
	while (sampleOffset>=SND_CHUNK_SIZE) {
		chunk = chunk->next;
		sampleOffset -= SND_CHUNK_SIZE;
		if (!chunk) {
			chunk = sc->soundData;
		}
	}

	if (!ch->doppler || ch->dopplerScale==1.0f) {
		leftvol = ch->leftvol*snd_vol;
		rightvol = ch->rightvol*snd_vol;
		samples = chunk->sndChunk;
		for ( i=0 ; i<count ; i++ ) {
			data  = samples[sampleOffset++];
			samp[i].left += (data * leftvol)>>8;

			if ( sc->soundChannels == 2 ) {
				data = samples[sampleOffset++];
			}
			samp[i].right += (data * rightvol)>>8;

			if (sampleOffset == SND_CHUNK_SIZE) {
				chunk = chunk->next;
				samples = chunk->sndChunk;
				sampleOffset = 0;
			}
		}
	} else {
		fleftvol = ch->leftvol*snd_vol;
		frightvol = ch->rightvol*snd_vol;

		ooff = sampleOffset;
		samples = chunk->sndChunk;
		



		for ( i=0 ; i<count ; i++ ) {

			aoff = ooff;
			ooff = ooff + ch->dopplerScale * sc->soundChannels;
			boff = ooff;
			fdata[0] = fdata[1] = 0;
			for (j=aoff; j<boff; j += sc->soundChannels) {
				if (j == SND_CHUNK_SIZE) {
					chunk = chunk->next;
					if (!chunk) {
						chunk = sc->soundData;
					}
					samples = chunk->sndChunk;
					ooff -= SND_CHUNK_SIZE;
				}
				if ( sc->soundChannels == 2 ) {
					fdata[0] += samples[j&(SND_CHUNK_SIZE-1)];
					fdata[1] += samples[(j+1)&(SND_CHUNK_SIZE-1)];
				} else {
					fdata[0] += samples[j&(SND_CHUNK_SIZE-1)];
					fdata[1] += samples[j&(SND_CHUNK_SIZE-1)];
				}
			}
			fdiv = 256 * (boff-aoff) / sc->soundChannels;
			samp[i].left += (fdata[0] * fleftvol)/fdiv;
			samp[i].right += (fdata[1] * frightvol)/fdiv;
		}
	}
}
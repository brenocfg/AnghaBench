#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  sample; int /*<<< orphan*/  index; } ;
struct TYPE_7__ {scalar_t__ sndChunk; TYPE_1__ adpcm; } ;
typedef  TYPE_2__ sndBuffer ;
typedef  int /*<<< orphan*/  byte ;
struct TYPE_8__ {int /*<<< orphan*/  sample; int /*<<< orphan*/  index; } ;
typedef  TYPE_3__ adpcm_state_t ;

/* Variables and functions */
 int SND_CHUNK_SIZE_BYTE ; 
 int /*<<< orphan*/  S_AdpcmDecode (char*,short*,int,TYPE_3__*) ; 

void S_AdpcmGetSamples(sndBuffer *chunk, short *to) {
	adpcm_state_t	state;
	byte			*out;

	// get the starting state from the block header
	state.index = chunk->adpcm.index;
	state.sample = chunk->adpcm.sample;

	out = (byte *)chunk->sndChunk;
	// get samples
	S_AdpcmDecode((char *) out, to, SND_CHUNK_SIZE_BYTE*2, &state );
}
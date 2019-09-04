#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct adpcm_state {int sample; int index; } ;

/* Variables and functions */
 scalar_t__* indexTable ; 
 int* stepsizeTable ; 

void S_AdpcmEncode( short indata[], char outdata[], int len, struct adpcm_state *state ) {
    short *inp;			/* Input buffer pointer */
    signed char *outp;		/* output buffer pointer */
    int val;			/* Current input sample value */
    int sign;			/* Current adpcm sign bit */
    int delta;			/* Current adpcm output value */
    int diff;			/* Difference between val and sample */
    int step;			/* Stepsize */
    int valpred;		/* Predicted output value */
    int vpdiff;			/* Current change to valpred */
    int index;			/* Current step change index */
    int outputbuffer;		/* place to keep previous 4-bit value */
    int bufferstep;		/* toggle between outputbuffer/output */

    outp = (signed char *)outdata;
    inp = indata;

    valpred = state->sample;
    index = state->index;
    step = stepsizeTable[index];
    
	outputbuffer = 0;	// quiet a compiler warning
    bufferstep = 1;

    for ( ; len > 0 ; len-- ) {
		val = *inp++;

		/* Step 1 - compute difference with previous value */
		diff = val - valpred;
		sign = (diff < 0) ? 8 : 0;
		if ( sign ) diff = (-diff);

		/* Step 2 - Divide and clamp */
		/* Note:
		** This code *approximately* computes:
		**    delta = diff*4/step;
		**    vpdiff = (delta+0.5)*step/4;
		** but in shift step bits are dropped. The net result of this is
		** that even if you have fast mul/div hardware you cannot put it to
		** good use since the fixup would be too expensive.
		*/
		delta = 0;
		vpdiff = (step >> 3);
		
		if ( diff >= step ) {
			delta = 4;
			diff -= step;
			vpdiff += step;
		}
		step >>= 1;
		if ( diff >= step  ) {
			delta |= 2;
			diff -= step;
			vpdiff += step;
		}
		step >>= 1;
		if ( diff >= step ) {
			delta |= 1;
			vpdiff += step;
		}

		/* Step 3 - Update previous value */
		if ( sign )
		  valpred -= vpdiff;
		else
		  valpred += vpdiff;

		/* Step 4 - Clamp previous value to 16 bits */
		if ( valpred > 32767 )
		  valpred = 32767;
		else if ( valpred < -32768 )
		  valpred = -32768;

		/* Step 5 - Assemble value, update index and step values */
		delta |= sign;
		
		index += indexTable[delta];
		if ( index < 0 ) index = 0;
		if ( index > 88 ) index = 88;
		step = stepsizeTable[index];

		/* Step 6 - Output value */
		if ( bufferstep ) {
			outputbuffer = (delta << 4) & 0xf0;
		} else {
			*outp++ = (delta & 0x0f) | outputbuffer;
		}
		bufferstep = !bufferstep;
    }

    /* Output last step, if needed */
    if ( !bufferstep )
      *outp++ = outputbuffer;
    
    state->sample = valpred;
    state->index = index;
}
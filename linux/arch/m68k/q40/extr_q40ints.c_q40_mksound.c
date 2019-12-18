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

/* Variables and functions */
 int* DAC_LEFT ; 
 int* DAC_RIGHT ; 
 int sound_ticks ; 

void q40_mksound(unsigned int hz, unsigned int ticks)
{
	/* for now ignore hz, except that hz==0 switches off sound */
	/* simply alternate the ampl (128-SVOL)-(128+SVOL)-..-.. at 200Hz */
	if (hz == 0) {
		if (sound_ticks)
			sound_ticks = 1;

		*DAC_LEFT = 128;
		*DAC_RIGHT = 128;

		return;
	}
	/* sound itself is done in q40_timer_int */
	if (sound_ticks == 0)
		sound_ticks = 1000; /* pretty long beep */
	sound_ticks = ticks << 1;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int tv_usec; } ;

/* Variables and functions */
 int FINEUSEC ; 
 int SHIFT_SCALE ; 
 int tick ; 
 scalar_t__ time_adj ; 
 int time_phase ; 
 TYPE_1__ timex ; 

void
hardclock(void)
{
	int ltemp, time_update;

	time_update = tick;	/* computed by adjtime() */
	time_phase += time_adj;
	if (time_phase < -FINEUSEC) {
		ltemp = -time_phase >> SHIFT_SCALE;
		time_phase += ltemp << SHIFT_SCALE;
		time_update -= ltemp;
	}
	else if (time_phase > FINEUSEC) {
		ltemp = time_phase >> SHIFT_SCALE;
		time_phase -= ltemp << SHIFT_SCALE;
		time_update += ltemp;
	}
	timex.tv_usec += time_update;
}
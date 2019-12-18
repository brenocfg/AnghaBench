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
typedef  scalar_t__ uint32_t ;
typedef  int int32_t ;
struct TYPE_4__ {TYPE_1__* config; } ;
struct TYPE_3__ {int clock_src; } ;

/* Variables and functions */
 scalar_t__ INITIAL_TIMECOUNTER ; 
 scalar_t__ mv_get_timer (int) ; 
 TYPE_2__* timer_softc ; 

__attribute__((used)) static void
mv_delay(int usec, void* arg)
{
	uint32_t	val, val_temp;
	int32_t		nticks;

	val = mv_get_timer(1);
	nticks = ((timer_softc->config->clock_src / 1000000 + 1) * usec);

	while (nticks > 0) {
		val_temp = mv_get_timer(1);
		if (val > val_temp)
			nticks -= (val - val_temp);
		else
			nticks -= (val + (INITIAL_TIMECOUNTER - val_temp));

		val = val_temp;
	}
}
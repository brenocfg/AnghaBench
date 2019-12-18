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
 int /*<<< orphan*/  ET_LOCK () ; 
 int /*<<< orphan*/  ET_UNLOCK () ; 
 int /*<<< orphan*/  configtimer (int) ; 
 scalar_t__ periodic ; 
 int profiling ; 

void
cpu_stopprofclock(void)
{

	ET_LOCK();
	if (profiling == 1) {
		if (periodic) {
			configtimer(0);
			profiling = 0;
			configtimer(1);
		} else
		profiling = 0;
	} else
		profiling--;
	ET_UNLOCK();
}
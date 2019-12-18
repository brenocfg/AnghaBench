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
typedef  scalar_t__ u_int ;
struct timeval {int tv_sec; } ;

/* Variables and functions */
 scalar_t__ hz ; 
 int ticks ; 

int
ppsratecheck(struct timeval *lasttime, int *curpps, int maxpps)
{
	int now;

	/*
	 * Reset the last time and counter if this is the first call
	 * or more than a second has passed since the last update of
	 * lasttime.
	 */
	now = ticks;
	if (lasttime->tv_sec == 0 || (u_int)(now - lasttime->tv_sec) >= hz) {
		lasttime->tv_sec = now;
		*curpps = 1;
		return (maxpps != 0);
	} else {
		(*curpps)++;		/* NB: ignore potential overflow */
		return (maxpps < 0 || *curpps <= maxpps);
	}
}
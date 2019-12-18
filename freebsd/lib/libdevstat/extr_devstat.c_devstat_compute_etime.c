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
struct bintime {long double sec; long double frac; } ;

/* Variables and functions */
 long double BINTIME_SCALE ; 

long double
devstat_compute_etime(struct bintime *cur_time, struct bintime *prev_time)
{
	long double etime;

	etime = cur_time->sec;
	etime += cur_time->frac * BINTIME_SCALE;
	if (prev_time != NULL) {
		etime -= prev_time->sec;
		etime -= prev_time->frac * BINTIME_SCALE;
	}
	return(etime);
}
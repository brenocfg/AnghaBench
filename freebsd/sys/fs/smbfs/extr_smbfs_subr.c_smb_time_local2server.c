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
typedef  scalar_t__ u_long ;
struct timespec {scalar_t__ tv_sec; } ;

/* Variables and functions */

void
smb_time_local2server(struct timespec *tsp, int tzoff, u_long *seconds)
{
	*seconds = tsp->tv_sec - tzoff * 60 /*- tz_minuteswest * 60 -
	    (wall_cmos_clock ? adjkerntz : 0)*/;
}
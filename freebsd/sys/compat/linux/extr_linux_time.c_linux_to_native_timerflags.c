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
 int EINVAL ; 
 int LINUX_TIMER_ABSTIME ; 
 int TIMER_ABSTIME ; 

int
linux_to_native_timerflags(int *nflags, int flags)
{

	if (flags & ~LINUX_TIMER_ABSTIME)
		return (EINVAL);
	*nflags = 0;
	if (flags & LINUX_TIMER_ABSTIME)
		*nflags |= TIMER_ABSTIME;
	return (0);
}
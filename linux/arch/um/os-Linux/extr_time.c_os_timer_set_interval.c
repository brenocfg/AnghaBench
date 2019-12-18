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
struct TYPE_4__ {unsigned long long tv_sec; unsigned long long tv_nsec; } ;
struct TYPE_3__ {unsigned long long tv_sec; unsigned long long tv_nsec; } ;
struct itimerspec {TYPE_2__ it_interval; TYPE_1__ it_value; } ;

/* Variables and functions */
 unsigned long long UM_NSEC_PER_SEC ; 
 int errno ; 
 int /*<<< orphan*/  event_high_res_timer ; 
 int timer_settime (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct itimerspec*,int /*<<< orphan*/ *) ; 

int os_timer_set_interval(unsigned long long nsecs)
{
	struct itimerspec its;

	its.it_value.tv_sec = nsecs / UM_NSEC_PER_SEC;
	its.it_value.tv_nsec = nsecs % UM_NSEC_PER_SEC;

	its.it_interval.tv_sec = nsecs / UM_NSEC_PER_SEC;
	its.it_interval.tv_nsec = nsecs % UM_NSEC_PER_SEC;

	if (timer_settime(event_high_res_timer, 0, &its, NULL) == -1)
		return -errno;

	return 0;
}
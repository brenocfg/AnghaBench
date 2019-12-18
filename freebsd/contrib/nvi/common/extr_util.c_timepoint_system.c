#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct timespec {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_3__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
typedef  TYPE_1__ mach_timespec_t ;
typedef  scalar_t__ kern_return_t ;
typedef  int /*<<< orphan*/  clock_serv_t ;

/* Variables and functions */
 int /*<<< orphan*/  CALENDAR_CLOCK ; 
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 int /*<<< orphan*/  CLOCK_REALTIME_FAST ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  clock_get_time (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 scalar_t__ host_get_clock_service (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mach_host_self () ; 
 int /*<<< orphan*/  mach_port_deallocate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mach_task_self () ; 

void
timepoint_system(
	struct timespec *ts)
{
#ifdef __APPLE__
	clock_serv_t clk;
	mach_timespec_t mts;
	kern_return_t kr;

	kr = host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &clk);
	if (kr != KERN_SUCCESS)
		return;
	(void)clock_get_time(clk, &mts);
	(void)mach_port_deallocate(mach_task_self(), clk);
	ts->tv_sec = mts.tv_sec;
	ts->tv_nsec = mts.tv_nsec;
#else
#ifdef CLOCK_REALTIME_FAST
	(void)clock_gettime(CLOCK_REALTIME_FAST, ts);
#else
	(void)clock_gettime(CLOCK_REALTIME, ts);
#endif
#endif
}
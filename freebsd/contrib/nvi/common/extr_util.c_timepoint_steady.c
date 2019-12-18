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
typedef  int uint64_t ;
struct timespec {int tv_sec; int tv_nsec; } ;
struct TYPE_3__ {int denom; int numer; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ mach_timebase_info_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  CLOCK_MONOTONIC_FAST ; 
 int /*<<< orphan*/  clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 int mach_absolute_time () ; 
 int /*<<< orphan*/  mach_timebase_info (TYPE_1__*) ; 

void
timepoint_steady(
	struct timespec *ts)
{
#ifdef __APPLE__
	static mach_timebase_info_data_t base = { 0 };
	uint64_t val;
	uint64_t ns;

	if (base.denom == 0)
		(void)mach_timebase_info(&base);

	val = mach_absolute_time();
	ns = val * base.numer / base.denom;
	ts->tv_sec = ns / 1000000000;
	ts->tv_nsec = ns % 1000000000;
#else
#ifdef CLOCK_MONOTONIC_FAST
	(void)clock_gettime(CLOCK_MONOTONIC_FAST, ts);
#else
	(void)clock_gettime(CLOCK_MONOTONIC, ts);
#endif
#endif
}
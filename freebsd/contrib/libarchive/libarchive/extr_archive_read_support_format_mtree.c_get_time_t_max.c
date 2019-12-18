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
typedef  scalar_t__ time_t ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 scalar_t__ INT32_MAX ; 
 scalar_t__ INT64_MAX ; 
 scalar_t__ TIME_T_MAX ; 

__attribute__((used)) static int64_t
get_time_t_max(void)
{
#if defined(TIME_T_MAX)
	return TIME_T_MAX;
#else
	/* ISO C allows time_t to be a floating-point type,
	   but POSIX requires an integer type.  The following
	   should work on any system that follows the POSIX
	   conventions. */
	if (((time_t)0) < ((time_t)-1)) {
		/* Time_t is unsigned */
		return (~(time_t)0);
	} else {
		/* Time_t is signed. */
		/* Assume it's the same as int64_t or int32_t */
		if (sizeof(time_t) == sizeof(int64_t)) {
			return (time_t)INT64_MAX;
		} else {
			return (time_t)INT32_MAX;
		}
	}
#endif
}
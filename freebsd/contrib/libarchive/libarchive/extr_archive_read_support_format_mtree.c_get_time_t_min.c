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
 scalar_t__ INT32_MIN ; 
 scalar_t__ INT64_MIN ; 
 scalar_t__ TIME_T_MIN ; 

__attribute__((used)) static int64_t
get_time_t_min(void)
{
#if defined(TIME_T_MIN)
	return TIME_T_MIN;
#else
	if (((time_t)0) < ((time_t)-1)) {
		/* Time_t is unsigned */
		return (time_t)0;
	} else {
		/* Time_t is signed. */
		if (sizeof(time_t) == sizeof(int64_t)) {
			return (time_t)INT64_MIN;
		} else {
			return (time_t)INT32_MIN;
		}
	}
#endif
}
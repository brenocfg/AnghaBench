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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 scalar_t__ TSTMP_GEQ (scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline uint32_t
bbr_calc_time(uint32_t cts, uint32_t earlier_time) {
	/*
	 * Given two timestamps, the current time stamp cts, and some other
	 * time-stamp taken in theory earlier return the difference. The
	 * trick is here sometimes locking will get the other timestamp
	 * after the cts. If this occurs we need to return 0.
	 */
	if (TSTMP_GEQ(cts, earlier_time))
		return (cts - earlier_time);
	/*
	 * cts is behind earlier_time if its less than 10ms consider it 0.
	 * If its more than 10ms difference then we had a time wrap. Else
	 * its just the normal locking foo. I wonder if we should not go to
	 * 64bit TS and get rid of this issue.
	 */
	if (TSTMP_GEQ((cts + 10000), earlier_time))
		return (0);
	/*
	 * Ok the time must have wrapped. So we need to answer a large
	 * amount of time, which the normal subtraction should do.
	 */
	return (cts - earlier_time);
}
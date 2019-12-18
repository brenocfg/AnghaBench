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

__attribute__((used)) static bool pmc_overflow_power7(unsigned long val)
{
	/*
	 * Events on POWER7 can roll back if a speculative event doesn't
	 * eventually complete. Unfortunately in some rare cases they will
	 * raise a performance monitor exception. We need to catch this to
	 * ensure we reset the PMC. In all cases the PMC will be 256 or less
	 * cycles from overflow.
	 *
	 * We only do this if the first pass fails to find any overflowing
	 * PMCs because a user might set a period of less than 256 and we
	 * don't want to mistakenly reset them.
	 */
	if ((0x80000000 - val) <= 256)
		return true;

	return false;
}
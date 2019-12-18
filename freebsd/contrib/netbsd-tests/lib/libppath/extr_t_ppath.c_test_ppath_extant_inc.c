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
 int /*<<< orphan*/  atf_tc_fail (char*) ; 
 scalar_t__ nppath ; 

void
test_ppath_extant_inc(void)
{
	if (++nppath == 0)
		atf_tc_fail("count of extant paths overflowed");
}
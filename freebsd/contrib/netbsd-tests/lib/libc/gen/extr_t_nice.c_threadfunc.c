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
 int /*<<< orphan*/  ATF_REQUIRE (int) ; 
 int /*<<< orphan*/  PRIO_PROCESS ; 
 int /*<<< orphan*/  atf_tc_fail (char*) ; 
 scalar_t__ errno ; 
 int getpriority (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *
threadfunc(void *arg)
{
	int pri, val;

	val = *(int *)arg;

	errno = 0;
	pri = getpriority(PRIO_PROCESS, 0);
	ATF_REQUIRE(errno == 0);

	if (pri != val)
		atf_tc_fail("nice(3) value was not propagated to threads");

	return NULL;
}
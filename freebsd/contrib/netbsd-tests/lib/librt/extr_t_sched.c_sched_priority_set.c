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
struct sched_param {int sched_priority; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_CHECK_EQ (int,int) ; 
 int /*<<< orphan*/  ATF_REQUIRE (int) ; 
 scalar_t__ sched_getparam (int /*<<< orphan*/ ,struct sched_param*) ; 
 int sched_getscheduler (int /*<<< orphan*/ ) ; 
 scalar_t__ sched_setscheduler (int /*<<< orphan*/ ,int,struct sched_param*) ; 

__attribute__((used)) static void
sched_priority_set(int pri, int pol)
{
	struct sched_param sched;

	sched.sched_priority = pri;

	ATF_REQUIRE(pri >= 0);
	ATF_REQUIRE(sched_setscheduler(0, pol, &sched) == 0);

	/*
	 * Test that the policy was changed.
	 */
	ATF_CHECK_EQ(sched_getscheduler(0), pol);

	/*
	 * And that sched_getparam(3) returns the new priority.
	 */
	sched.sched_priority = -1;

	ATF_REQUIRE(sched_getparam(0, &sched) == 0);
	ATF_CHECK_EQ(sched.sched_priority, pri);
}
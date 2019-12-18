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
typedef  size_t u_int ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE_MSG (int,char*,int) ; 
 size_t __arraycount (int*) ; 
 int sched_getscheduler (int /*<<< orphan*/ ) ; 
 int* schedulers ; 

__attribute__((used)) static int
get_different_scheduler(void)
{
	u_int i;
	int scheduler;

	/* get current schedule policy */
	scheduler = sched_getscheduler(0);
	for (i = 0; i < __arraycount(schedulers); i++) {
		if (schedulers[i] == scheduler)
			break;
	}
	ATF_REQUIRE_MSG(i < __arraycount(schedulers),
	    "Unknown current scheduler %d", scheduler);

	/* new scheduler */
	i++;
	if (i >= __arraycount(schedulers))
		i = 0;
	return schedulers[i];
}
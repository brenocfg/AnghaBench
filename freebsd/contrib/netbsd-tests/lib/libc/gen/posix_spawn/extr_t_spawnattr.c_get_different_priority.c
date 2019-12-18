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
 int sched_get_priority_max (int) ; 
 int sched_get_priority_min (int) ; 
 int /*<<< orphan*/  sched_getparam (int /*<<< orphan*/ ,struct sched_param*) ; 

__attribute__((used)) static int
get_different_priority(int scheduler)
{
	int max, min, new, priority;
	struct sched_param param;

	max = sched_get_priority_max(scheduler);
	min = sched_get_priority_min(scheduler);

	sched_getparam(0, &param);
	priority = param.sched_priority;

	/*
	 * Change numerical value of the priority, to ensure that it
	 * was set for the spawned child.
	 */
	new = priority + 1;
	if (new > max)
		new = min;
	return new;
}
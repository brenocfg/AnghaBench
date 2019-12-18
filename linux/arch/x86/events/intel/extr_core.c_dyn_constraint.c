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
struct event_constraint {int flags; } ;
struct cpu_hw_events {struct event_constraint* constraint_list; } ;

/* Variables and functions */
 int PERF_X86_EVENT_DYNAMIC ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 

__attribute__((used)) static struct event_constraint *
dyn_constraint(struct cpu_hw_events *cpuc, struct event_constraint *c, int idx)
{
	WARN_ON_ONCE(!cpuc->constraint_list);

	if (!(c->flags & PERF_X86_EVENT_DYNAMIC)) {
		struct event_constraint *cx;

		/*
		 * grab pre-allocated constraint entry
		 */
		cx = &cpuc->constraint_list[idx];

		/*
		 * initialize dynamic constraint
		 * with static constraint
		 */
		*cx = *c;

		/*
		 * mark constraint as dynamic
		 */
		cx->flags |= PERF_X86_EVENT_DYNAMIC;
		c = cx;
	}

	return c;
}
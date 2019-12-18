#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  config; } ;
struct TYPE_3__ {int precise_ip; } ;
struct perf_event {TYPE_2__ hw; TYPE_1__ attr; } ;
struct event_constraint {int dummy; } ;
struct cpu_hw_events {int dummy; } ;

/* Variables and functions */
 scalar_t__ constraint_match (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct event_constraint counter0_constraint ; 
 int /*<<< orphan*/  fixed0_constraint ; 
 struct event_constraint fixed0_counter0_constraint ; 
 struct event_constraint* intel_get_event_constraints (struct cpu_hw_events*,int,struct perf_event*) ; 

__attribute__((used)) static struct event_constraint *
tnt_get_event_constraints(struct cpu_hw_events *cpuc, int idx,
			  struct perf_event *event)
{
	struct event_constraint *c;

	/*
	 * :ppp means to do reduced skid PEBS,
	 * which is available on PMC0 and fixed counter 0.
	 */
	if (event->attr.precise_ip == 3) {
		/* Force instruction:ppp on PMC0 and Fixed counter 0 */
		if (constraint_match(&fixed0_constraint, event->hw.config))
			return &fixed0_counter0_constraint;

		return &counter0_constraint;
	}

	c = intel_get_event_constraints(cpuc, idx, event);

	return c;
}
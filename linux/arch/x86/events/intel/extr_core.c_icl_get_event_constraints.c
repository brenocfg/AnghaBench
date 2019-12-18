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
 scalar_t__ constraint_match (struct event_constraint*,int /*<<< orphan*/ ) ; 
 struct event_constraint fixed0_constraint ; 
 struct event_constraint* hsw_get_event_constraints (struct cpu_hw_events*,int,struct perf_event*) ; 

__attribute__((used)) static struct event_constraint *
icl_get_event_constraints(struct cpu_hw_events *cpuc, int idx,
			  struct perf_event *event)
{
	/*
	 * Fixed counter 0 has less skid.
	 * Force instruction:ppp in Fixed counter 0
	 */
	if ((event->attr.precise_ip == 3) &&
	    constraint_match(&fixed0_constraint, event->hw.config))
		return &fixed0_constraint;

	return hsw_get_event_constraints(cpuc, idx, event);
}
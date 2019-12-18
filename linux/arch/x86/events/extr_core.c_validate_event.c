#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct perf_event {int dummy; } ;
struct event_constraint {int /*<<< orphan*/  weight; } ;
struct cpu_hw_events {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* put_event_constraints ) (struct cpu_hw_events*,struct perf_event*) ;struct event_constraint* (* get_event_constraints ) (struct cpu_hw_events*,int /*<<< orphan*/ ,struct perf_event*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct cpu_hw_events*) ; 
 int PTR_ERR (struct cpu_hw_events*) ; 
 struct cpu_hw_events* allocate_fake_cpuc () ; 
 int /*<<< orphan*/  free_fake_cpuc (struct cpu_hw_events*) ; 
 struct event_constraint* stub1 (struct cpu_hw_events*,int /*<<< orphan*/ ,struct perf_event*) ; 
 int /*<<< orphan*/  stub2 (struct cpu_hw_events*,struct perf_event*) ; 
 TYPE_1__ x86_pmu ; 

__attribute__((used)) static int validate_event(struct perf_event *event)
{
	struct cpu_hw_events *fake_cpuc;
	struct event_constraint *c;
	int ret = 0;

	fake_cpuc = allocate_fake_cpuc();
	if (IS_ERR(fake_cpuc))
		return PTR_ERR(fake_cpuc);

	c = x86_pmu.get_event_constraints(fake_cpuc, 0, event);

	if (!c || !c->weight)
		ret = -EINVAL;

	if (x86_pmu.put_event_constraints)
		x86_pmu.put_event_constraints(fake_cpuc, event);

	free_fake_cpuc(fake_cpuc);

	return ret;
}
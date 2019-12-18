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
struct perf_event {struct perf_event* group_leader; } ;
struct cpu_hw_events {int n_events; } ;
struct TYPE_2__ {int (* schedule_events ) (struct cpu_hw_events*,int,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct cpu_hw_events*) ; 
 int PTR_ERR (struct cpu_hw_events*) ; 
 struct cpu_hw_events* allocate_fake_cpuc () ; 
 int collect_events (struct cpu_hw_events*,struct perf_event*,int) ; 
 int /*<<< orphan*/  free_fake_cpuc (struct cpu_hw_events*) ; 
 int stub1 (struct cpu_hw_events*,int,int /*<<< orphan*/ *) ; 
 TYPE_1__ x86_pmu ; 

__attribute__((used)) static int validate_group(struct perf_event *event)
{
	struct perf_event *leader = event->group_leader;
	struct cpu_hw_events *fake_cpuc;
	int ret = -EINVAL, n;

	fake_cpuc = allocate_fake_cpuc();
	if (IS_ERR(fake_cpuc))
		return PTR_ERR(fake_cpuc);
	/*
	 * the event is not yet connected with its
	 * siblings therefore we must first collect
	 * existing siblings, then add the new event
	 * before we can simulate the scheduling
	 */
	n = collect_events(fake_cpuc, leader, true);
	if (n < 0)
		goto out;

	fake_cpuc->n_events = n;
	n = collect_events(fake_cpuc, event, false);
	if (n < 0)
		goto out;

	fake_cpuc->n_events = 0;
	ret = x86_pmu.schedule_events(fake_cpuc, n, NULL);

out:
	free_fake_cpuc(fake_cpuc);
	return ret;
}
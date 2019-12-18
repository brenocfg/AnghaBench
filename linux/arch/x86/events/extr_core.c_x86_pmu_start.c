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
struct TYPE_3__ {int idx; int state; } ;
struct perf_event {TYPE_1__ hw; } ;
struct cpu_hw_events {int /*<<< orphan*/  running; int /*<<< orphan*/  active_mask; struct perf_event** events; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* enable ) (struct perf_event*) ;} ;

/* Variables and functions */
 int PERF_EF_RELOAD ; 
 int PERF_HES_STOPPED ; 
 int PERF_HES_UPTODATE ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  __set_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_hw_events ; 
 int /*<<< orphan*/  perf_event_update_userpage (struct perf_event*) ; 
 int /*<<< orphan*/  stub1 (struct perf_event*) ; 
 struct cpu_hw_events* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  x86_perf_event_set_period (struct perf_event*) ; 
 TYPE_2__ x86_pmu ; 

__attribute__((used)) static void x86_pmu_start(struct perf_event *event, int flags)
{
	struct cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	int idx = event->hw.idx;

	if (WARN_ON_ONCE(!(event->hw.state & PERF_HES_STOPPED)))
		return;

	if (WARN_ON_ONCE(idx == -1))
		return;

	if (flags & PERF_EF_RELOAD) {
		WARN_ON_ONCE(!(event->hw.state & PERF_HES_UPTODATE));
		x86_perf_event_set_period(event);
	}

	event->hw.state = 0;

	cpuc->events[idx] = event;
	__set_bit(idx, cpuc->active_mask);
	__set_bit(idx, cpuc->running);
	x86_pmu.enable(event);
	perf_event_update_userpage(event);
}
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
struct TYPE_3__ {int state; int /*<<< orphan*/  event_base; } ;
struct perf_event {TYPE_1__ hw; } ;
struct cpu_hw_events {int n_events; int txn_flags; int /*<<< orphan*/  n_added; int /*<<< orphan*/ * events; struct perf_event** event; int /*<<< orphan*/ * current_idx; } ;
struct TYPE_4__ {int max_hw_events; } ;

/* Variables and functions */
 int EAGAIN ; 
 int PERF_EF_START ; 
 int PERF_HES_ARCH ; 
 int PERF_HES_STOPPED ; 
 int PERF_HES_UPTODATE ; 
 int PERF_PMU_TXN_ADD ; 
 int /*<<< orphan*/  PIC_NO_INDEX ; 
 scalar_t__ check_excludes (struct perf_event**,int,int) ; 
 int /*<<< orphan*/  cpu_hw_events ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 scalar_t__ sparc_check_constraints (struct perf_event**,int /*<<< orphan*/ *,int) ; 
 TYPE_2__* sparc_pmu ; 
 struct cpu_hw_events* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sparc_pmu_add(struct perf_event *event, int ef_flags)
{
	struct cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	int n0, ret = -EAGAIN;
	unsigned long flags;

	local_irq_save(flags);

	n0 = cpuc->n_events;
	if (n0 >= sparc_pmu->max_hw_events)
		goto out;

	cpuc->event[n0] = event;
	cpuc->events[n0] = event->hw.event_base;
	cpuc->current_idx[n0] = PIC_NO_INDEX;

	event->hw.state = PERF_HES_UPTODATE | PERF_HES_STOPPED;
	if (!(ef_flags & PERF_EF_START))
		event->hw.state |= PERF_HES_ARCH;

	/*
	 * If group events scheduling transaction was started,
	 * skip the schedulability test here, it will be performed
	 * at commit time(->commit_txn) as a whole
	 */
	if (cpuc->txn_flags & PERF_PMU_TXN_ADD)
		goto nocheck;

	if (check_excludes(cpuc->event, n0, 1))
		goto out;
	if (sparc_check_constraints(cpuc->event, cpuc->events, n0 + 1))
		goto out;

nocheck:
	cpuc->n_events++;
	cpuc->n_added++;

	ret = 0;
out:
	local_irq_restore(flags);
	return ret;
}
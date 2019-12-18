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
struct hw_perf_event {int state; } ;
struct perf_event {struct hw_perf_event hw; } ;
struct cpu_hw_events {int n_events; int txn_flags; int n_added; int n_txn; int /*<<< orphan*/  assign; } ;
struct TYPE_2__ {int (* schedule_events ) (struct cpu_hw_events*,int,int*) ;int /*<<< orphan*/  (* add ) (struct perf_event*) ;} ;

/* Variables and functions */
 int PERF_EF_START ; 
 int PERF_HES_ARCH ; 
 int PERF_HES_STOPPED ; 
 int PERF_HES_UPTODATE ; 
 int PERF_PMU_TXN_ADD ; 
 int X86_PMC_IDX_MAX ; 
 int collect_events (struct cpu_hw_events*,struct perf_event*,int) ; 
 int /*<<< orphan*/  cpu_hw_events ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 int stub1 (struct cpu_hw_events*,int,int*) ; 
 int /*<<< orphan*/  stub2 (struct perf_event*) ; 
 struct cpu_hw_events* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 TYPE_1__ x86_pmu ; 

__attribute__((used)) static int x86_pmu_add(struct perf_event *event, int flags)
{
	struct cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	struct hw_perf_event *hwc;
	int assign[X86_PMC_IDX_MAX];
	int n, n0, ret;

	hwc = &event->hw;

	n0 = cpuc->n_events;
	ret = n = collect_events(cpuc, event, false);
	if (ret < 0)
		goto out;

	hwc->state = PERF_HES_UPTODATE | PERF_HES_STOPPED;
	if (!(flags & PERF_EF_START))
		hwc->state |= PERF_HES_ARCH;

	/*
	 * If group events scheduling transaction was started,
	 * skip the schedulability test here, it will be performed
	 * at commit time (->commit_txn) as a whole.
	 *
	 * If commit fails, we'll call ->del() on all events
	 * for which ->add() was called.
	 */
	if (cpuc->txn_flags & PERF_PMU_TXN_ADD)
		goto done_collect;

	ret = x86_pmu.schedule_events(cpuc, n, assign);
	if (ret)
		goto out;
	/*
	 * copy new assignment, now we know it is possible
	 * will be used by hw_perf_enable()
	 */
	memcpy(cpuc->assign, assign, n*sizeof(int));

done_collect:
	/*
	 * Commit the collect_events() state. See x86_pmu_del() and
	 * x86_pmu_*_txn().
	 */
	cpuc->n_events = n;
	cpuc->n_added += n - n0;
	cpuc->n_txn += n - n0;

	if (x86_pmu.add) {
		/*
		 * This is before x86_pmu_enable() will call x86_pmu_start(),
		 * so we enable LBRs before an event needs them etc..
		 */
		x86_pmu.add(event);
	}

	ret = 0;
out:
	return ret;
}
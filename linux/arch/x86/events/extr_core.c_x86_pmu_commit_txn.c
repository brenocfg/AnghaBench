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
struct pmu {int dummy; } ;
struct cpu_hw_events {int txn_flags; int n_events; int /*<<< orphan*/  assign; } ;
struct TYPE_2__ {int (* schedule_events ) (struct cpu_hw_events*,int,int*) ;} ;

/* Variables and functions */
 int EAGAIN ; 
 int PERF_PMU_TXN_ADD ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int X86_PMC_IDX_MAX ; 
 int /*<<< orphan*/  cpu_hw_events ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  perf_pmu_enable (struct pmu*) ; 
 int stub1 (struct cpu_hw_events*,int,int*) ; 
 struct cpu_hw_events* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 TYPE_1__ x86_pmu ; 
 int /*<<< orphan*/  x86_pmu_initialized () ; 

__attribute__((used)) static int x86_pmu_commit_txn(struct pmu *pmu)
{
	struct cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	int assign[X86_PMC_IDX_MAX];
	int n, ret;

	WARN_ON_ONCE(!cpuc->txn_flags);	/* no txn in flight */

	if (cpuc->txn_flags & ~PERF_PMU_TXN_ADD) {
		cpuc->txn_flags = 0;
		return 0;
	}

	n = cpuc->n_events;

	if (!x86_pmu_initialized())
		return -EAGAIN;

	ret = x86_pmu.schedule_events(cpuc, n, assign);
	if (ret)
		return ret;

	/*
	 * copy new assignment, now we know it is possible
	 * will be used by hw_perf_enable()
	 */
	memcpy(cpuc->assign, assign, n*sizeof(int));

	cpuc->txn_flags = 0;
	perf_pmu_enable(pmu);
	return 0;
}
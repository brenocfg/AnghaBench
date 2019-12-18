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
typedef  int u64 ;
struct pmu {int dummy; } ;
struct TYPE_2__ {int auth_ctl; } ;
struct cpu_cf_events {int txn_flags; int state; TYPE_1__ info; } ;

/* Variables and functions */
 int CPUMF_LCCTL_ENABLE_SHIFT ; 
 int ENOENT ; 
 int PERF_PMU_TXN_ADD ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  cpu_cf_events ; 
 int /*<<< orphan*/  perf_pmu_enable (struct pmu*) ; 
 struct cpu_cf_events* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cpumf_pmu_commit_txn(struct pmu *pmu)
{
	struct cpu_cf_events *cpuhw = this_cpu_ptr(&cpu_cf_events);
	u64 state;

	WARN_ON_ONCE(!cpuhw->txn_flags);	/* no txn in flight */

	if (cpuhw->txn_flags & ~PERF_PMU_TXN_ADD) {
		cpuhw->txn_flags = 0;
		return 0;
	}

	/* check if the updated state can be scheduled */
	state = cpuhw->state & ~((1 << CPUMF_LCCTL_ENABLE_SHIFT) - 1);
	state >>= CPUMF_LCCTL_ENABLE_SHIFT;
	if ((state & cpuhw->info.auth_ctl) != state)
		return -ENOENT;

	cpuhw->txn_flags = 0;
	perf_pmu_enable(pmu);
	return 0;
}
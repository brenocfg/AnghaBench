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
struct pmu {int dummy; } ;
struct cpu_cf_events {unsigned int txn_flags; scalar_t__ tx_state; scalar_t__ state; } ;

/* Variables and functions */
 unsigned int PERF_PMU_TXN_ADD ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  cpu_cf_events ; 
 int /*<<< orphan*/  perf_pmu_enable (struct pmu*) ; 
 struct cpu_cf_events* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cpumf_pmu_cancel_txn(struct pmu *pmu)
{
	unsigned int txn_flags;
	struct cpu_cf_events *cpuhw = this_cpu_ptr(&cpu_cf_events);

	WARN_ON_ONCE(!cpuhw->txn_flags);	/* no txn in flight */

	txn_flags = cpuhw->txn_flags;
	cpuhw->txn_flags = 0;
	if (txn_flags & ~PERF_PMU_TXN_ADD)
		return;

	WARN_ON(cpuhw->tx_state != cpuhw->state);

	perf_pmu_enable(pmu);
}
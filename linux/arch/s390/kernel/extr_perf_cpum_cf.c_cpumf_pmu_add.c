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
struct TYPE_2__ {int state; int /*<<< orphan*/  config_base; } ;
struct perf_event {TYPE_1__ hw; } ;
struct cpu_cf_events {int txn_flags; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  PERF_EF_RELOAD ; 
 int PERF_EF_START ; 
 int PERF_HES_STOPPED ; 
 int PERF_HES_UPTODATE ; 
 int PERF_PMU_TXN_ADD ; 
 int /*<<< orphan*/  cpu_cf_events ; 
 int /*<<< orphan*/  cpumf_pmu_start (struct perf_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctr_set_enable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_event_update_userpage (struct perf_event*) ; 
 struct cpu_cf_events* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 scalar_t__ validate_ctr_auth (TYPE_1__*) ; 

__attribute__((used)) static int cpumf_pmu_add(struct perf_event *event, int flags)
{
	struct cpu_cf_events *cpuhw = this_cpu_ptr(&cpu_cf_events);

	/* Check authorization for the counter set to which this
	 * counter belongs.
	 * For group events transaction, the authorization check is
	 * done in cpumf_pmu_commit_txn().
	 */
	if (!(cpuhw->txn_flags & PERF_PMU_TXN_ADD))
		if (validate_ctr_auth(&event->hw))
			return -ENOENT;

	ctr_set_enable(&cpuhw->state, event->hw.config_base);
	event->hw.state = PERF_HES_UPTODATE | PERF_HES_STOPPED;

	if (flags & PERF_EF_START)
		cpumf_pmu_start(event, PERF_EF_RELOAD);

	perf_event_update_userpage(event);

	return 0;
}
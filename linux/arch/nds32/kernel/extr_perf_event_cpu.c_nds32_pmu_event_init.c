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
struct perf_event {int /*<<< orphan*/  pmu; } ;
struct nds32_pmu {int (* map_event ) (struct perf_event*) ;int /*<<< orphan*/  active_events; } ;
typedef  int /*<<< orphan*/  atomic_t ;

/* Variables and functions */
 int ENOENT ; 
 int EOPNOTSUPP ; 
 int __hw_perf_event_init (struct perf_event*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc_not_zero (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ has_branch_stack (struct perf_event*) ; 
 int nds32_pmu_reserve_hardware (struct nds32_pmu*) ; 
 int stub1 (struct perf_event*) ; 
 struct nds32_pmu* to_nds32_pmu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nds32_pmu_event_init(struct perf_event *event)
{
	struct nds32_pmu *nds32_pmu = to_nds32_pmu(event->pmu);
	int err = 0;
	atomic_t *active_events = &nds32_pmu->active_events;

	/* does not support taken branch sampling */
	if (has_branch_stack(event))
		return -EOPNOTSUPP;

	if (nds32_pmu->map_event(event) == -ENOENT)
		return -ENOENT;

	if (!atomic_inc_not_zero(active_events)) {
		if (atomic_read(active_events) == 0) {
			/* Register irq handler */
			err = nds32_pmu_reserve_hardware(nds32_pmu);
		}

		if (!err)
			atomic_inc(active_events);
	}

	if (err)
		return err;

	err = __hw_perf_event_init(event);

	return err;
}
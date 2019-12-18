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
struct hw_perf_event {int dummy; } ;
struct perf_event {int /*<<< orphan*/  pmu; struct hw_perf_event hw; } ;
struct cpu_hw_events {int n_events; int* current_idx; unsigned long idx_mask; int /*<<< orphan*/ * evtype; struct perf_event** event; } ;

/* Variables and functions */
 int /*<<< orphan*/  alpha_perf_event_update (struct perf_event*,struct hw_perf_event*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_hw_events ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  perf_event_update_userpage (struct perf_event*) ; 
 int /*<<< orphan*/  perf_pmu_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_pmu_enable (int /*<<< orphan*/ ) ; 
 struct cpu_hw_events* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void alpha_pmu_del(struct perf_event *event, int flags)
{
	struct cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	struct hw_perf_event *hwc = &event->hw;
	unsigned long irq_flags;
	int j;

	perf_pmu_disable(event->pmu);
	local_irq_save(irq_flags);

	for (j = 0; j < cpuc->n_events; j++) {
		if (event == cpuc->event[j]) {
			int idx = cpuc->current_idx[j];

			/* Shift remaining entries down into the existing
			 * slot.
			 */
			while (++j < cpuc->n_events) {
				cpuc->event[j - 1] = cpuc->event[j];
				cpuc->evtype[j - 1] = cpuc->evtype[j];
				cpuc->current_idx[j - 1] =
					cpuc->current_idx[j];
			}

			/* Absorb the final count and turn off the event. */
			alpha_perf_event_update(event, hwc, idx, 0);
			perf_event_update_userpage(event);

			cpuc->idx_mask &= ~(1UL<<idx);
			cpuc->n_events--;
			break;
		}
	}

	local_irq_restore(irq_flags);
	perf_pmu_enable(event->pmu);
}
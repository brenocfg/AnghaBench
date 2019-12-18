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
typedef  unsigned long long u64 ;
struct pt_regs {int dummy; } ;
struct perf_sample_data {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  last_period; } ;
struct perf_event {TYPE_1__ hw; } ;
struct cpu_hw_events {struct perf_event** events; int /*<<< orphan*/  active_mask; } ;
struct TYPE_4__ {int num_counters; int cntval_bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  APIC_DM_NMI ; 
 int /*<<< orphan*/  APIC_LVTPC ; 
 int /*<<< orphan*/  apic_perf_irqs ; 
 int /*<<< orphan*/  apic_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_hw_events ; 
 int /*<<< orphan*/  inc_irq_stat (int /*<<< orphan*/ ) ; 
 scalar_t__ perf_event_overflow (struct perf_event*,struct perf_sample_data*,struct pt_regs*) ; 
 int /*<<< orphan*/  perf_sample_data_init (struct perf_sample_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int,int /*<<< orphan*/ ) ; 
 struct cpu_hw_events* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  x86_perf_event_set_period (struct perf_event*) ; 
 unsigned long long x86_perf_event_update (struct perf_event*) ; 
 TYPE_2__ x86_pmu ; 
 int /*<<< orphan*/  x86_pmu_stop (struct perf_event*,int /*<<< orphan*/ ) ; 

int x86_pmu_handle_irq(struct pt_regs *regs)
{
	struct perf_sample_data data;
	struct cpu_hw_events *cpuc;
	struct perf_event *event;
	int idx, handled = 0;
	u64 val;

	cpuc = this_cpu_ptr(&cpu_hw_events);

	/*
	 * Some chipsets need to unmask the LVTPC in a particular spot
	 * inside the nmi handler.  As a result, the unmasking was pushed
	 * into all the nmi handlers.
	 *
	 * This generic handler doesn't seem to have any issues where the
	 * unmasking occurs so it was left at the top.
	 */
	apic_write(APIC_LVTPC, APIC_DM_NMI);

	for (idx = 0; idx < x86_pmu.num_counters; idx++) {
		if (!test_bit(idx, cpuc->active_mask))
			continue;

		event = cpuc->events[idx];

		val = x86_perf_event_update(event);
		if (val & (1ULL << (x86_pmu.cntval_bits - 1)))
			continue;

		/*
		 * event overflow
		 */
		handled++;
		perf_sample_data_init(&data, 0, event->hw.last_period);

		if (!x86_perf_event_set_period(event))
			continue;

		if (perf_event_overflow(event, &data, regs))
			x86_pmu_stop(event, 0);
	}

	if (handled)
		inc_irq_stat(apic_perf_irqs);

	return handled;
}
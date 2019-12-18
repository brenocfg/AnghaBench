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
typedef  unsigned long long u64 ;
struct pt_regs {int dummy; } ;
struct perf_sample_data {int dummy; } ;
struct hw_perf_event {int idx; int /*<<< orphan*/  last_period; } ;
struct perf_event {struct hw_perf_event hw; } ;
struct cpu_hw_events {struct perf_event** events; int /*<<< orphan*/  running; int /*<<< orphan*/  active_mask; } ;
struct TYPE_2__ {int num_counters; int cntval_bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  APIC_DM_NMI ; 
 int /*<<< orphan*/  APIC_LVTPC ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 scalar_t__ __test_and_clear_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apic_perf_irqs ; 
 int /*<<< orphan*/  apic_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_hw_events ; 
 int /*<<< orphan*/  inc_irq_stat (int /*<<< orphan*/ ) ; 
 int p4_pmu_clear_cccr_ovf (struct hw_perf_event*) ; 
 scalar_t__ perf_event_overflow (struct perf_event*,struct perf_sample_data*,struct pt_regs*) ; 
 int /*<<< orphan*/  perf_sample_data_init (struct perf_sample_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int,int /*<<< orphan*/ ) ; 
 struct cpu_hw_events* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  x86_perf_event_set_period (struct perf_event*) ; 
 unsigned long long x86_perf_event_update (struct perf_event*) ; 
 TYPE_1__ x86_pmu ; 
 int /*<<< orphan*/  x86_pmu_stop (struct perf_event*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int p4_pmu_handle_irq(struct pt_regs *regs)
{
	struct perf_sample_data data;
	struct cpu_hw_events *cpuc;
	struct perf_event *event;
	struct hw_perf_event *hwc;
	int idx, handled = 0;
	u64 val;

	cpuc = this_cpu_ptr(&cpu_hw_events);

	for (idx = 0; idx < x86_pmu.num_counters; idx++) {
		int overflow;

		if (!test_bit(idx, cpuc->active_mask)) {
			/* catch in-flight IRQs */
			if (__test_and_clear_bit(idx, cpuc->running))
				handled++;
			continue;
		}

		event = cpuc->events[idx];
		hwc = &event->hw;

		WARN_ON_ONCE(hwc->idx != idx);

		/* it might be unflagged overflow */
		overflow = p4_pmu_clear_cccr_ovf(hwc);

		val = x86_perf_event_update(event);
		if (!overflow && (val & (1ULL << (x86_pmu.cntval_bits - 1))))
			continue;

		handled += overflow;

		/* event overflow for sure */
		perf_sample_data_init(&data, 0, hwc->last_period);

		if (!x86_perf_event_set_period(event))
			continue;


		if (perf_event_overflow(event, &data, regs))
			x86_pmu_stop(event, 0);
	}

	if (handled)
		inc_irq_stat(apic_perf_irqs);

	/*
	 * When dealing with the unmasking of the LVTPC on P4 perf hw, it has
	 * been observed that the OVF bit flag has to be cleared first _before_
	 * the LVTPC can be unmasked.
	 *
	 * The reason is the NMI line will continue to be asserted while the OVF
	 * bit is set.  This causes a second NMI to generate if the LVTPC is
	 * unmasked before the OVF bit is cleared, leading to unknown NMI
	 * messages.
	 */
	apic_write(APIC_LVTPC, APIC_DM_NMI);

	return handled;
}
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
struct pt_regs {int dummy; } ;
struct pmu_hw_events {struct perf_event** events; } ;
struct perf_sample_data {int dummy; } ;
struct hw_perf_event {int /*<<< orphan*/  last_period; } ;
struct perf_event {struct hw_perf_event hw; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  pmu; int /*<<< orphan*/  hw_events; } ;

/* Variables and functions */
 int BIT (int) ; 
 int CSKY_PMU_MAX_EVENTS ; 
 int /*<<< orphan*/  HPOFSR ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int cprcr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csky_perf_event_update (struct perf_event*,struct hw_perf_event*) ; 
 TYPE_1__ csky_pmu ; 
 int /*<<< orphan*/  csky_pmu_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  csky_pmu_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  csky_pmu_event_set_period (struct perf_event*) ; 
 int /*<<< orphan*/  csky_pmu_stop_event (struct perf_event*) ; 
 struct pt_regs* get_irq_regs () ; 
 int /*<<< orphan*/  irq_work_run () ; 
 scalar_t__ perf_event_overflow (struct perf_event*,struct perf_sample_data*,struct pt_regs*) ; 
 int /*<<< orphan*/  perf_sample_data_init (struct perf_sample_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pmu_hw_events* this_cpu_ptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t csky_pmu_handle_irq(int irq_num, void *dev)
{
	struct perf_sample_data data;
	struct pmu_hw_events *cpuc = this_cpu_ptr(csky_pmu.hw_events);
	struct pt_regs *regs;
	int idx;

	/*
	 * Did an overflow occur?
	 */
	if (!cprcr(HPOFSR))
		return IRQ_NONE;

	/*
	 * Handle the counter(s) overflow(s)
	 */
	regs = get_irq_regs();

	csky_pmu_disable(&csky_pmu.pmu);

	for (idx = 0; idx < CSKY_PMU_MAX_EVENTS; ++idx) {
		struct perf_event *event = cpuc->events[idx];
		struct hw_perf_event *hwc;

		/* Ignore if we don't have an event. */
		if (!event)
			continue;
		/*
		 * We have a single interrupt for all counters. Check that
		 * each counter has overflowed before we process it.
		 */
		if (!(cprcr(HPOFSR) & BIT(idx)))
			continue;

		hwc = &event->hw;
		csky_perf_event_update(event, &event->hw);
		perf_sample_data_init(&data, 0, hwc->last_period);
		csky_pmu_event_set_period(event);

		if (perf_event_overflow(event, &data, regs))
			csky_pmu_stop_event(event);
	}

	csky_pmu_enable(&csky_pmu.pmu);

	/*
	 * Handle the pending perf events.
	 *
	 * Note: this call *must* be run with interrupts disabled. For
	 * platforms that can have the PMU interrupts raised as an NMI, this
	 * will not work.
	 */
	irq_work_run();

	return IRQ_HANDLED;
}
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
struct perf_sample_data {int dummy; } ;
struct hw_perf_event {int /*<<< orphan*/  last_period; } ;
struct perf_event {struct hw_perf_event hw; } ;
struct cpu_hw_events {int n_events; int* current_idx; int /*<<< orphan*/  idx_mask; struct perf_event** event; } ;
struct TYPE_2__ {unsigned long num_pmcs; scalar_t__* pmc_max_period; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERFMON_CMD_DISABLE ; 
 int /*<<< orphan*/  PERFMON_CMD_ENABLE ; 
 int /*<<< orphan*/  __this_cpu_inc (int /*<<< orphan*/ ) ; 
 scalar_t__ alpha_perf_event_set_period (struct perf_event*,struct hw_perf_event*,int) ; 
 int /*<<< orphan*/  alpha_perf_event_update (struct perf_event*,struct hw_perf_event*,int,scalar_t__) ; 
 TYPE_1__* alpha_pmu ; 
 int /*<<< orphan*/  alpha_pmu_stop (struct perf_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_hw_events ; 
 int /*<<< orphan*/  irq_err_count ; 
 int /*<<< orphan*/  irq_pmi_count ; 
 scalar_t__ perf_event_overflow (struct perf_event*,struct perf_sample_data*,struct pt_regs*) ; 
 int /*<<< orphan*/  perf_sample_data_init (struct perf_sample_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warning (char*,int) ; 
 struct cpu_hw_events* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wrperfmon (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void alpha_perf_event_irq_handler(unsigned long la_ptr,
					struct pt_regs *regs)
{
	struct cpu_hw_events *cpuc;
	struct perf_sample_data data;
	struct perf_event *event;
	struct hw_perf_event *hwc;
	int idx, j;

	__this_cpu_inc(irq_pmi_count);
	cpuc = this_cpu_ptr(&cpu_hw_events);

	/* Completely counting through the PMC's period to trigger a new PMC
	 * overflow interrupt while in this interrupt routine is utterly
	 * disastrous!  The EV6 and EV67 counters are sufficiently large to
	 * prevent this but to be really sure disable the PMCs.
	 */
	wrperfmon(PERFMON_CMD_DISABLE, cpuc->idx_mask);

	/* la_ptr is the counter that overflowed. */
	if (unlikely(la_ptr >= alpha_pmu->num_pmcs)) {
		/* This should never occur! */
		irq_err_count++;
		pr_warning("PMI: silly index %ld\n", la_ptr);
		wrperfmon(PERFMON_CMD_ENABLE, cpuc->idx_mask);
		return;
	}

	idx = la_ptr;

	for (j = 0; j < cpuc->n_events; j++) {
		if (cpuc->current_idx[j] == idx)
			break;
	}

	if (unlikely(j == cpuc->n_events)) {
		/* This can occur if the event is disabled right on a PMC overflow. */
		wrperfmon(PERFMON_CMD_ENABLE, cpuc->idx_mask);
		return;
	}

	event = cpuc->event[j];

	if (unlikely(!event)) {
		/* This should never occur! */
		irq_err_count++;
		pr_warning("PMI: No event at index %d!\n", idx);
		wrperfmon(PERFMON_CMD_ENABLE, cpuc->idx_mask);
		return;
	}

	hwc = &event->hw;
	alpha_perf_event_update(event, hwc, idx, alpha_pmu->pmc_max_period[idx]+1);
	perf_sample_data_init(&data, 0, hwc->last_period);

	if (alpha_perf_event_set_period(event, hwc, idx)) {
		if (perf_event_overflow(event, &data, regs)) {
			/* Interrupts coming too quickly; "throttle" the
			 * counter, i.e., disable it for a little while.
			 */
			alpha_pmu_stop(event, 0);
		}
	}
	wrperfmon(PERFMON_CMD_ENABLE, cpuc->idx_mask);

	return;
}
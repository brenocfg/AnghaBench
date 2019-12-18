#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct pt_regs {int dummy; } ;
struct perf_sample_data {int /*<<< orphan*/  weight; int /*<<< orphan*/  data_src; int /*<<< orphan*/ * br_stack; int /*<<< orphan*/  addr; } ;
struct TYPE_5__ {int sample_type; } ;
struct TYPE_4__ {scalar_t__ sample_period; int state; scalar_t__ last_period; int /*<<< orphan*/  period_left; int /*<<< orphan*/  prev_count; int /*<<< orphan*/  idx; } ;
struct perf_event {TYPE_2__ attr; TYPE_1__ hw; int /*<<< orphan*/  count; } ;
struct cpu_hw_events {int /*<<< orphan*/  bhrb_stack; } ;
typedef  scalar_t__ s64 ;
struct TYPE_6__ {int /*<<< orphan*/  (* get_mem_weight ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  flags; int /*<<< orphan*/  (* get_mem_data_src ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct pt_regs*) ;} ;

/* Variables and functions */
 int PERF_HES_STOPPED ; 
 int PERF_SAMPLE_ADDR ; 
 int PERF_SAMPLE_BRANCH_STACK ; 
 int PERF_SAMPLE_DATA_SRC ; 
 int PERF_SAMPLE_PHYS_ADDR ; 
 int PERF_SAMPLE_WEIGHT ; 
 scalar_t__ check_and_compute_delta (scalar_t__,unsigned long) ; 
 int /*<<< orphan*/  cpu_hw_events ; 
 int /*<<< orphan*/  local64_add (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ local64_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local64_set (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ perf_event_overflow (struct perf_event*,struct perf_sample_data*,struct pt_regs*) ; 
 int /*<<< orphan*/  perf_event_update_userpage (struct perf_event*) ; 
 int /*<<< orphan*/  perf_get_data_addr (struct pt_regs*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_sample_data_init (struct perf_sample_data*,unsigned long long,scalar_t__) ; 
 int /*<<< orphan*/  power_pmu_bhrb_read (struct cpu_hw_events*) ; 
 int /*<<< orphan*/  power_pmu_stop (struct perf_event*,int /*<<< orphan*/ ) ; 
 TYPE_3__* ppmu ; 
 int siar_valid (struct pt_regs*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct pt_regs*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *) ; 
 struct cpu_hw_events* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_pmc (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void record_and_restart(struct perf_event *event, unsigned long val,
			       struct pt_regs *regs)
{
	u64 period = event->hw.sample_period;
	s64 prev, delta, left;
	int record = 0;

	if (event->hw.state & PERF_HES_STOPPED) {
		write_pmc(event->hw.idx, 0);
		return;
	}

	/* we don't have to worry about interrupts here */
	prev = local64_read(&event->hw.prev_count);
	delta = check_and_compute_delta(prev, val);
	local64_add(delta, &event->count);

	/*
	 * See if the total period for this event has expired,
	 * and update for the next period.
	 */
	val = 0;
	left = local64_read(&event->hw.period_left) - delta;
	if (delta == 0)
		left++;
	if (period) {
		if (left <= 0) {
			left += period;
			if (left <= 0)
				left = period;
			record = siar_valid(regs);
			event->hw.last_period = event->hw.sample_period;
		}
		if (left < 0x80000000LL)
			val = 0x80000000LL - left;
	}

	write_pmc(event->hw.idx, val);
	local64_set(&event->hw.prev_count, val);
	local64_set(&event->hw.period_left, left);
	perf_event_update_userpage(event);

	/*
	 * Finally record data if requested.
	 */
	if (record) {
		struct perf_sample_data data;

		perf_sample_data_init(&data, ~0ULL, event->hw.last_period);

		if (event->attr.sample_type &
		    (PERF_SAMPLE_ADDR | PERF_SAMPLE_PHYS_ADDR))
			perf_get_data_addr(regs, &data.addr);

		if (event->attr.sample_type & PERF_SAMPLE_BRANCH_STACK) {
			struct cpu_hw_events *cpuhw;
			cpuhw = this_cpu_ptr(&cpu_hw_events);
			power_pmu_bhrb_read(cpuhw);
			data.br_stack = &cpuhw->bhrb_stack;
		}

		if (event->attr.sample_type & PERF_SAMPLE_DATA_SRC &&
						ppmu->get_mem_data_src)
			ppmu->get_mem_data_src(&data.data_src, ppmu->flags, regs);

		if (event->attr.sample_type & PERF_SAMPLE_WEIGHT &&
						ppmu->get_mem_weight)
			ppmu->get_mem_weight(&data.weight);

		if (perf_event_overflow(event, &data, regs))
			power_pmu_stop(event, 0);
	}
}
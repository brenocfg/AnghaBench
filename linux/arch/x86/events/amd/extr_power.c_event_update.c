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
typedef  scalar_t__ u64 ;
struct hw_perf_event {scalar_t__ pwr_acc; scalar_t__ ptsc; } ;
struct perf_event {int /*<<< orphan*/  count; struct hw_perf_event hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_F15H_CU_PWR_ACCUMULATOR ; 
 int /*<<< orphan*/  MSR_F15H_PTSC ; 
 int cpu_pwr_sample_ratio ; 
 int /*<<< orphan*/  do_div (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  local64_add (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ max_cu_acc_power ; 
 int /*<<< orphan*/  rdmsrl (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void event_update(struct perf_event *event)
{
	struct hw_perf_event *hwc = &event->hw;
	u64 prev_pwr_acc, new_pwr_acc, prev_ptsc, new_ptsc;
	u64 delta, tdelta;

	prev_pwr_acc = hwc->pwr_acc;
	prev_ptsc = hwc->ptsc;
	rdmsrl(MSR_F15H_CU_PWR_ACCUMULATOR, new_pwr_acc);
	rdmsrl(MSR_F15H_PTSC, new_ptsc);

	/*
	 * Calculate the CU power consumption over a time period, the unit of
	 * final value (delta) is micro-Watts. Then add it to the event count.
	 */
	if (new_pwr_acc < prev_pwr_acc) {
		delta = max_cu_acc_power + new_pwr_acc;
		delta -= prev_pwr_acc;
	} else
		delta = new_pwr_acc - prev_pwr_acc;

	delta *= cpu_pwr_sample_ratio * 1000;
	tdelta = new_ptsc - prev_ptsc;

	do_div(delta, tdelta);
	local64_add(delta, &event->count);
}
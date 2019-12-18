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
typedef  int u64 ;
struct hw_perf_event {int idx; } ;
struct perf_event {struct hw_perf_event hw; int /*<<< orphan*/  pmu; } ;
struct arm_pmu {int dummy; } ;

/* Variables and functions */
 int ARMV8_IDX_CYCLE_COUNTER ; 
 int /*<<< orphan*/  armv8pmu_counter_valid (struct arm_pmu*,int) ; 
 int /*<<< orphan*/  armv8pmu_event_is_64bit (struct perf_event*) ; 
 int /*<<< orphan*/  armv8pmu_write_hw_counter (struct perf_event*,int) ; 
 int /*<<< orphan*/  pmccntr_el0 ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 struct arm_pmu* to_arm_pmu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_sysreg (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void armv8pmu_write_counter(struct perf_event *event, u64 value)
{
	struct arm_pmu *cpu_pmu = to_arm_pmu(event->pmu);
	struct hw_perf_event *hwc = &event->hw;
	int idx = hwc->idx;

	if (!armv8pmu_counter_valid(cpu_pmu, idx))
		pr_err("CPU%u writing wrong counter %d\n",
			smp_processor_id(), idx);
	else if (idx == ARMV8_IDX_CYCLE_COUNTER) {
		/*
		 * The cycles counter is really a 64-bit counter.
		 * When treating it as a 32-bit counter, we only count
		 * the lower 32 bits, and set the upper 32-bits so that
		 * we get an interrupt upon 32-bit overflow.
		 */
		if (!armv8pmu_event_is_64bit(event))
			value |= 0xffffffff00000000ULL;
		write_sysreg(value, pmccntr_el0);
	} else
		armv8pmu_write_hw_counter(event, value);
}
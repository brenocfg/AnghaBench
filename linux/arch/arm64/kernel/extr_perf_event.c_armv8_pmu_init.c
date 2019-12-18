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
struct arm_pmu {int /*<<< orphan*/  filter_match; int /*<<< orphan*/  set_event_filter; int /*<<< orphan*/  reset; int /*<<< orphan*/  stop; int /*<<< orphan*/  start; int /*<<< orphan*/  clear_event_idx; int /*<<< orphan*/  get_event_idx; int /*<<< orphan*/  write_counter; int /*<<< orphan*/  read_counter; int /*<<< orphan*/  disable; int /*<<< orphan*/  enable; int /*<<< orphan*/  handle_irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  armv8pmu_clear_event_idx ; 
 int /*<<< orphan*/  armv8pmu_disable_event ; 
 int /*<<< orphan*/  armv8pmu_enable_event ; 
 int /*<<< orphan*/  armv8pmu_filter_match ; 
 int /*<<< orphan*/  armv8pmu_get_event_idx ; 
 int /*<<< orphan*/  armv8pmu_handle_irq ; 
 int armv8pmu_probe_pmu (struct arm_pmu*) ; 
 int /*<<< orphan*/  armv8pmu_read_counter ; 
 int /*<<< orphan*/  armv8pmu_reset ; 
 int /*<<< orphan*/  armv8pmu_set_event_filter ; 
 int /*<<< orphan*/  armv8pmu_start ; 
 int /*<<< orphan*/  armv8pmu_stop ; 
 int /*<<< orphan*/  armv8pmu_write_counter ; 

__attribute__((used)) static int armv8_pmu_init(struct arm_pmu *cpu_pmu)
{
	int ret = armv8pmu_probe_pmu(cpu_pmu);
	if (ret)
		return ret;

	cpu_pmu->handle_irq		= armv8pmu_handle_irq;
	cpu_pmu->enable			= armv8pmu_enable_event;
	cpu_pmu->disable		= armv8pmu_disable_event;
	cpu_pmu->read_counter		= armv8pmu_read_counter;
	cpu_pmu->write_counter		= armv8pmu_write_counter;
	cpu_pmu->get_event_idx		= armv8pmu_get_event_idx;
	cpu_pmu->clear_event_idx	= armv8pmu_clear_event_idx;
	cpu_pmu->start			= armv8pmu_start;
	cpu_pmu->stop			= armv8pmu_stop;
	cpu_pmu->reset			= armv8pmu_reset;
	cpu_pmu->set_event_filter	= armv8pmu_set_event_filter;
	cpu_pmu->filter_match		= armv8pmu_filter_match;

	return 0;
}
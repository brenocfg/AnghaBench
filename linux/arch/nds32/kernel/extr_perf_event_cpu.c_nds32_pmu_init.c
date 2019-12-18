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
struct nds32_pmu {int max_period; int /*<<< orphan*/  reset; int /*<<< orphan*/  stop; int /*<<< orphan*/  start; int /*<<< orphan*/  get_event_idx; int /*<<< orphan*/  write_counter; int /*<<< orphan*/  read_counter; int /*<<< orphan*/  disable; int /*<<< orphan*/  enable; int /*<<< orphan*/  handle_irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  nds32_pmu_disable_event ; 
 int /*<<< orphan*/  nds32_pmu_enable_event ; 
 int /*<<< orphan*/  nds32_pmu_get_event_idx ; 
 int /*<<< orphan*/  nds32_pmu_handle_irq ; 
 int /*<<< orphan*/  nds32_pmu_read_counter ; 
 int /*<<< orphan*/  nds32_pmu_reset ; 
 int /*<<< orphan*/  nds32_pmu_start ; 
 int /*<<< orphan*/  nds32_pmu_stop ; 
 int /*<<< orphan*/  nds32_pmu_write_counter ; 

__attribute__((used)) static void nds32_pmu_init(struct nds32_pmu *cpu_pmu)
{
	cpu_pmu->handle_irq = nds32_pmu_handle_irq;
	cpu_pmu->enable = nds32_pmu_enable_event;
	cpu_pmu->disable = nds32_pmu_disable_event;
	cpu_pmu->read_counter = nds32_pmu_read_counter;
	cpu_pmu->write_counter = nds32_pmu_write_counter;
	cpu_pmu->get_event_idx = nds32_pmu_get_event_idx;
	cpu_pmu->start = nds32_pmu_start;
	cpu_pmu->stop = nds32_pmu_stop;
	cpu_pmu->reset = nds32_pmu_reset;
	cpu_pmu->max_period = 0xFFFFFFFF;	/* Maximum counts */
}
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
struct pmu_hw_events {int /*<<< orphan*/  pmu_lock; } ;
struct hw_perf_event {int idx; unsigned int config_base; } ;
struct perf_event {int /*<<< orphan*/  attr; int /*<<< orphan*/  pmu; struct hw_perf_event hw; } ;
struct nds32_pmu {scalar_t__ (* set_event_filter ) (struct hw_perf_event*,int /*<<< orphan*/ *) ;struct pmu_hw_events* (* get_hw_events ) () ;} ;

/* Variables and functions */
 scalar_t__ event_requires_mode_exclusion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nds32_pfm_counter_valid (struct nds32_pmu*,int) ; 
 int /*<<< orphan*/  nds32_pfm_disable_counter (int) ; 
 int /*<<< orphan*/  nds32_pfm_enable_counter (int) ; 
 int /*<<< orphan*/  nds32_pfm_enable_intens (int) ; 
 int /*<<< orphan*/  nds32_pfm_write_evtsel (int,unsigned int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_notice (char*) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct pmu_hw_events* stub1 () ; 
 scalar_t__ stub2 (struct hw_perf_event*,int /*<<< orphan*/ *) ; 
 struct nds32_pmu* to_nds32_pmu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nds32_pmu_enable_event(struct perf_event *event)
{
	unsigned long flags;
	unsigned int evnum = 0;
	struct hw_perf_event *hwc = &event->hw;
	struct nds32_pmu *cpu_pmu = to_nds32_pmu(event->pmu);
	struct pmu_hw_events *events = cpu_pmu->get_hw_events();
	int idx = hwc->idx;

	if (!nds32_pfm_counter_valid(cpu_pmu, idx)) {
		pr_err("CPU enabling wrong pfm counter IRQ enable\n");
		return;
	}

	/*
	 * Enable counter and interrupt, and set the counter to count
	 * the event that we're interested in.
	 */
	raw_spin_lock_irqsave(&events->pmu_lock, flags);

	/*
	 * Disable counter
	 */
	nds32_pfm_disable_counter(idx);

	/*
	 * Check whether we need to exclude the counter from certain modes.
	 */
	if ((!cpu_pmu->set_event_filter ||
	     cpu_pmu->set_event_filter(hwc, &event->attr)) &&
	     event_requires_mode_exclusion(&event->attr)) {
		pr_notice
		("NDS32 performance counters do not support mode exclusion\n");
		hwc->config_base = 0;
	}
	/* Write event */
	evnum = hwc->config_base;
	nds32_pfm_write_evtsel(idx, evnum);

	/*
	 * Enable interrupt for this counter
	 */
	nds32_pfm_enable_intens(idx);

	/*
	 * Enable counter
	 */
	nds32_pfm_enable_counter(idx);

	raw_spin_unlock_irqrestore(&events->pmu_lock, flags);
}
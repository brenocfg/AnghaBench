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
struct perf_event {int /*<<< orphan*/  pmu; } ;
struct arm_pmu {int /*<<< orphan*/  hw_events; } ;

/* Variables and functions */
 int /*<<< orphan*/  armv8pmu_disable_event_counter (struct perf_event*) ; 
 int /*<<< orphan*/  armv8pmu_enable_event_counter (struct perf_event*) ; 
 int /*<<< orphan*/  armv8pmu_enable_event_irq (struct perf_event*) ; 
 int /*<<< orphan*/  armv8pmu_write_event_type (struct perf_event*) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct pmu_hw_events* this_cpu_ptr (int /*<<< orphan*/ ) ; 
 struct arm_pmu* to_arm_pmu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void armv8pmu_enable_event(struct perf_event *event)
{
	unsigned long flags;
	struct arm_pmu *cpu_pmu = to_arm_pmu(event->pmu);
	struct pmu_hw_events *events = this_cpu_ptr(cpu_pmu->hw_events);

	/*
	 * Enable counter and interrupt, and set the counter to count
	 * the event that we're interested in.
	 */
	raw_spin_lock_irqsave(&events->pmu_lock, flags);

	/*
	 * Disable counter
	 */
	armv8pmu_disable_event_counter(event);

	/*
	 * Set event (if destined for PMNx counters).
	 */
	armv8pmu_write_event_type(event);

	/*
	 * Enable interrupt for this counter
	 */
	armv8pmu_enable_event_irq(event);

	/*
	 * Enable counter
	 */
	armv8pmu_enable_event_counter(event);

	raw_spin_unlock_irqrestore(&events->pmu_lock, flags);
}
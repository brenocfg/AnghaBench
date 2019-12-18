#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ type; int config; } ;
struct hw_perf_event {int config_base; } ;
struct perf_event {int attach_state; scalar_t__ cpu; TYPE_1__ attr; struct hw_perf_event hw; } ;
struct TYPE_4__ {scalar_t__ type; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int L2X0_EVENT_CNT_CFG_SRC_MASK ; 
 int PERF_ATTACH_TASK ; 
 scalar_t__ cpumask_first (int /*<<< orphan*/ *) ; 
 scalar_t__ is_sampling_event (struct perf_event*) ; 
 TYPE_2__* l2x0_pmu ; 
 int /*<<< orphan*/  l2x0_pmu_group_is_valid (struct perf_event*) ; 
 int /*<<< orphan*/  pmu_cpu ; 

__attribute__((used)) static int l2x0_pmu_event_init(struct perf_event *event)
{
	struct hw_perf_event *hw = &event->hw;

	if (event->attr.type != l2x0_pmu->type)
		return -ENOENT;

	if (is_sampling_event(event) ||
	    event->attach_state & PERF_ATTACH_TASK)
		return -EINVAL;

	if (event->cpu < 0)
		return -EINVAL;

	if (event->attr.config & ~L2X0_EVENT_CNT_CFG_SRC_MASK)
		return -EINVAL;

	hw->config_base = event->attr.config;

	if (!l2x0_pmu_group_is_valid(event))
		return -EINVAL;

	event->cpu = cpumask_first(&pmu_cpu);

	return 0;
}
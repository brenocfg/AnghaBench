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
struct TYPE_3__ {scalar_t__ type; int /*<<< orphan*/  config1; int /*<<< orphan*/  config; } ;
struct hw_perf_event {int /*<<< orphan*/  conf1; int /*<<< orphan*/  conf; } ;
struct perf_event {int attach_state; scalar_t__ cpu; TYPE_1__ attr; TYPE_2__* pmu; struct hw_perf_event hw; } ;
struct TYPE_4__ {scalar_t__ type; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int PERF_ATTACH_TASK ; 
 scalar_t__ is_sampling_event (struct perf_event*) ; 

__attribute__((used)) static int perf_iommu_event_init(struct perf_event *event)
{
	struct hw_perf_event *hwc = &event->hw;

	/* test the event attr type check for PMU enumeration */
	if (event->attr.type != event->pmu->type)
		return -ENOENT;

	/*
	 * IOMMU counters are shared across all cores.
	 * Therefore, it does not support per-process mode.
	 * Also, it does not support event sampling mode.
	 */
	if (is_sampling_event(event) || event->attach_state & PERF_ATTACH_TASK)
		return -EINVAL;

	if (event->cpu < 0)
		return -EINVAL;

	/* update the hw_perf_event struct with the iommu config data */
	hwc->conf  = event->attr.config;
	hwc->conf1 = event->attr.config1;

	return 0;
}
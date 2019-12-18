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
struct perf_event_attr {int type; int config; } ;
struct hw_perf_event {int config; } ;
struct perf_event {int /*<<< orphan*/  destroy; struct hw_perf_event hw; struct perf_event_attr attr; } ;
struct TYPE_2__ {int raw_event_mask; int max_events; int (* event_map ) (int) ;} ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENODEV ; 
#define  PERF_TYPE_HARDWARE 130 
#define  PERF_TYPE_HW_CACHE 129 
#define  PERF_TYPE_RAW 128 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc_not_zero (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int hw_perf_cache_event (int,int*) ; 
 int /*<<< orphan*/  hw_perf_event_destroy ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  num_events ; 
 int /*<<< orphan*/  pmc_reserve_mutex ; 
 scalar_t__ reserve_pmc_hardware () ; 
 TYPE_1__* sh_pmu ; 
 int /*<<< orphan*/  sh_pmu_initialized () ; 
 int stub1 (int) ; 

__attribute__((used)) static int __hw_perf_event_init(struct perf_event *event)
{
	struct perf_event_attr *attr = &event->attr;
	struct hw_perf_event *hwc = &event->hw;
	int config = -1;
	int err;

	if (!sh_pmu_initialized())
		return -ENODEV;

	/*
	 * See if we need to reserve the counter.
	 *
	 * If no events are currently in use, then we have to take a
	 * mutex to ensure that we don't race with another task doing
	 * reserve_pmc_hardware or release_pmc_hardware.
	 */
	err = 0;
	if (!atomic_inc_not_zero(&num_events)) {
		mutex_lock(&pmc_reserve_mutex);
		if (atomic_read(&num_events) == 0 &&
		    reserve_pmc_hardware())
			err = -EBUSY;
		else
			atomic_inc(&num_events);
		mutex_unlock(&pmc_reserve_mutex);
	}

	if (err)
		return err;

	event->destroy = hw_perf_event_destroy;

	switch (attr->type) {
	case PERF_TYPE_RAW:
		config = attr->config & sh_pmu->raw_event_mask;
		break;
	case PERF_TYPE_HW_CACHE:
		err = hw_perf_cache_event(attr->config, &config);
		if (err)
			return err;
		break;
	case PERF_TYPE_HARDWARE:
		if (attr->config >= sh_pmu->max_events)
			return -EINVAL;

		config = sh_pmu->event_map(attr->config);
		break;
	}

	if (config == -1)
		return -EINVAL;

	hwc->config |= config;

	return 0;
}
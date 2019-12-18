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
struct TYPE_2__ {int type; } ;
struct perf_event {scalar_t__ cpu; TYPE_1__ attr; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOENT ; 
 int EOPNOTSUPP ; 
#define  PERF_TYPE_HARDWARE 130 
#define  PERF_TYPE_HW_CACHE 129 
#define  PERF_TYPE_RAW 128 
 int __hw_perf_event_init (struct perf_event*) ; 
 int /*<<< orphan*/  active_events ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc_not_zero (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_online (scalar_t__) ; 
 scalar_t__ has_branch_stack (struct perf_event*) ; 
 int mipspmu_get_irq () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmu_reserve_mutex ; 

__attribute__((used)) static int mipspmu_event_init(struct perf_event *event)
{
	int err = 0;

	/* does not support taken branch sampling */
	if (has_branch_stack(event))
		return -EOPNOTSUPP;

	switch (event->attr.type) {
	case PERF_TYPE_RAW:
	case PERF_TYPE_HARDWARE:
	case PERF_TYPE_HW_CACHE:
		break;

	default:
		return -ENOENT;
	}

	if (event->cpu >= 0 && !cpu_online(event->cpu))
		return -ENODEV;

	if (!atomic_inc_not_zero(&active_events)) {
		mutex_lock(&pmu_reserve_mutex);
		if (atomic_read(&active_events) == 0)
			err = mipspmu_get_irq();

		if (!err)
			atomic_inc(&active_events);
		mutex_unlock(&pmu_reserve_mutex);
	}

	if (err)
		return err;

	return __hw_perf_event_init(event);
}
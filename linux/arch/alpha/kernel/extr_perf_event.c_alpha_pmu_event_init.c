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
struct perf_event {TYPE_1__ attr; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOENT ; 
 int EOPNOTSUPP ; 
#define  PERF_TYPE_HARDWARE 130 
#define  PERF_TYPE_HW_CACHE 129 
#define  PERF_TYPE_RAW 128 
 int __hw_perf_event_init (struct perf_event*) ; 
 int /*<<< orphan*/  alpha_pmu ; 
 scalar_t__ has_branch_stack (struct perf_event*) ; 

__attribute__((used)) static int alpha_pmu_event_init(struct perf_event *event)
{
	int err;

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

	if (!alpha_pmu)
		return -ENODEV;

	/* Do the real initialisation work. */
	err = __hw_perf_event_init(event);

	return err;
}
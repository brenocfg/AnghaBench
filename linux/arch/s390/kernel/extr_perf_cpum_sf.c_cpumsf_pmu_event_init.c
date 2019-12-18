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
struct TYPE_2__ {int type; scalar_t__ exclude_idle; scalar_t__ exclude_hv; int /*<<< orphan*/  config; } ;
struct perf_event {scalar_t__ cpu; int /*<<< orphan*/  (* destroy ) (struct perf_event*) ;TYPE_1__ attr; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOENT ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  PERF_COUNT_HW_CPU_CYCLES ; 
 int /*<<< orphan*/  PERF_EVENT_CPUM_SF ; 
 int /*<<< orphan*/  PERF_EVENT_CPUM_SF_DIAG ; 
#define  PERF_TYPE_HARDWARE 129 
#define  PERF_TYPE_RAW 128 
 int __hw_perf_event_init (struct perf_event*) ; 
 int /*<<< orphan*/  cpu_online (scalar_t__) ; 
 scalar_t__ has_branch_stack (struct perf_event*) ; 
 int /*<<< orphan*/  is_sampling_event (struct perf_event*) ; 
 int /*<<< orphan*/  stub1 (struct perf_event*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int cpumsf_pmu_event_init(struct perf_event *event)
{
	int err;

	/* No support for taken branch sampling */
	if (has_branch_stack(event))
		return -EOPNOTSUPP;

	switch (event->attr.type) {
	case PERF_TYPE_RAW:
		if ((event->attr.config != PERF_EVENT_CPUM_SF) &&
		    (event->attr.config != PERF_EVENT_CPUM_SF_DIAG))
			return -ENOENT;
		break;
	case PERF_TYPE_HARDWARE:
		/* Support sampling of CPU cycles in addition to the
		 * counter facility.  However, the counter facility
		 * is more precise and, hence, restrict this PMU to
		 * sampling events only.
		 */
		if (event->attr.config != PERF_COUNT_HW_CPU_CYCLES)
			return -ENOENT;
		if (!is_sampling_event(event))
			return -ENOENT;
		break;
	default:
		return -ENOENT;
	}

	/* Check online status of the CPU to which the event is pinned */
	if (event->cpu >= 0 && !cpu_online(event->cpu))
		return -ENODEV;

	/* Force reset of idle/hv excludes regardless of what the
	 * user requested.
	 */
	if (event->attr.exclude_hv)
		event->attr.exclude_hv = 0;
	if (event->attr.exclude_idle)
		event->attr.exclude_idle = 0;

	err = __hw_perf_event_init(event);
	if (unlikely(err))
		if (event->destroy)
			event->destroy(event);
	return err;
}
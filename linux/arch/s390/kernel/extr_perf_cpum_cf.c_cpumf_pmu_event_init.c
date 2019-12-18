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
struct perf_event {int /*<<< orphan*/  (* destroy ) (struct perf_event*) ;TYPE_1__ attr; } ;

/* Variables and functions */
 int ENOENT ; 
#define  PERF_TYPE_HARDWARE 130 
#define  PERF_TYPE_HW_CACHE 129 
#define  PERF_TYPE_RAW 128 
 int __hw_perf_event_init (struct perf_event*) ; 
 int /*<<< orphan*/  stub1 (struct perf_event*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int cpumf_pmu_event_init(struct perf_event *event)
{
	int err;

	switch (event->attr.type) {
	case PERF_TYPE_HARDWARE:
	case PERF_TYPE_HW_CACHE:
	case PERF_TYPE_RAW:
		err = __hw_perf_event_init(event);
		break;
	default:
		return -ENOENT;
	}

	if (unlikely(err) && event->destroy)
		event->destroy(event);

	return err;
}
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
struct hw_perf_event {int state; } ;
struct perf_event {struct hw_perf_event hw; } ;
struct cpu_hw_events {int /*<<< orphan*/  active_mask; } ;
struct TYPE_2__ {scalar_t__ event; } ;
struct bts_ctx {TYPE_1__ handle; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  INTEL_PMC_IDX_FIXED_BTS ; 
 int PERF_EF_START ; 
 int PERF_HES_STOPPED ; 
 int /*<<< orphan*/  bts_ctx ; 
 int /*<<< orphan*/  bts_event_start (struct perf_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_hw_events ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bts_event_add(struct perf_event *event, int mode)
{
	struct bts_ctx *bts = this_cpu_ptr(&bts_ctx);
	struct cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	struct hw_perf_event *hwc = &event->hw;

	event->hw.state = PERF_HES_STOPPED;

	if (test_bit(INTEL_PMC_IDX_FIXED_BTS, cpuc->active_mask))
		return -EBUSY;

	if (bts->handle.event)
		return -EBUSY;

	if (mode & PERF_EF_START) {
		bts_event_start(event, 0);
		if (hwc->state & PERF_HES_STOPPED)
			return -EINVAL;
	}

	return 0;
}
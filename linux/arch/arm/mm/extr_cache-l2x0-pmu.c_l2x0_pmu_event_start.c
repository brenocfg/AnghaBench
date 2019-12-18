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
struct hw_perf_event {int state; int /*<<< orphan*/  config_base; int /*<<< orphan*/  idx; } ;
struct perf_event {struct hw_perf_event hw; } ;

/* Variables and functions */
 int PERF_EF_RELOAD ; 
 int PERF_HES_STOPPED ; 
 int PERF_HES_UPTODATE ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  __l2x0_pmu_event_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2x0_pmu_event_configure (struct perf_event*) ; 

__attribute__((used)) static void l2x0_pmu_event_start(struct perf_event *event, int flags)
{
	struct hw_perf_event *hw = &event->hw;

	if (WARN_ON_ONCE(!(event->hw.state & PERF_HES_STOPPED)))
		return;

	if (flags & PERF_EF_RELOAD) {
		WARN_ON_ONCE(!(hw->state & PERF_HES_UPTODATE));
		l2x0_pmu_event_configure(event);
	}

	hw->state = 0;

	__l2x0_pmu_event_enable(hw->idx, hw->config_base);
}
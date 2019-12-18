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
typedef  int /*<<< orphan*/  u64 ;
struct hw_perf_event {int /*<<< orphan*/  config_base; int /*<<< orphan*/  config; } ;
struct perf_event {struct hw_perf_event hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  wrmsrl_safe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void p6_pmu_enable_event(struct perf_event *event)
{
	struct hw_perf_event *hwc = &event->hw;
	u64 val;

	val = hwc->config;

	/*
	 * p6 only has a global event enable, set on PerfEvtSel0
	 * We "disable" events by programming P6_NOP_EVENT
	 * and we rely on p6_pmu_enable_all() being called
	 * to actually enable the events.
	 */

	(void)wrmsrl_safe(hwc->config_base, val);
}
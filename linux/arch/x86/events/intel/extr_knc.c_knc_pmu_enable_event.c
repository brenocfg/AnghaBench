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
struct hw_perf_event {scalar_t__ idx; scalar_t__ config_base; int /*<<< orphan*/  config; } ;
struct perf_event {struct hw_perf_event hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCH_PERFMON_EVENTSEL_ENABLE ; 
 int /*<<< orphan*/  wrmsrl_safe (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void knc_pmu_enable_event(struct perf_event *event)
{
	struct hw_perf_event *hwc = &event->hw;
	u64 val;

	val = hwc->config;
	val |= ARCH_PERFMON_EVENTSEL_ENABLE;

	(void)wrmsrl_safe(hwc->config_base + hwc->idx, val);
}
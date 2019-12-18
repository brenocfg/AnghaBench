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
struct hw_perf_event {int /*<<< orphan*/  sample_period; int /*<<< orphan*/  period_left; int /*<<< orphan*/  last_period; } ;

/* Variables and functions */
 int /*<<< orphan*/  local64_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hw_init_period(struct hw_perf_event *hwc, u64 period)
{
	hwc->sample_period = period;
	hwc->last_period = hwc->sample_period;
	local64_set(&hwc->period_left, hwc->sample_period);
}
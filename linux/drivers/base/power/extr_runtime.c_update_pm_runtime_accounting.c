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
typedef  scalar_t__ u64 ;
struct TYPE_2__ {scalar_t__ disable_depth; scalar_t__ accounting_timestamp; scalar_t__ runtime_status; int /*<<< orphan*/  active_time; int /*<<< orphan*/  suspended_time; } ;
struct device {TYPE_1__ power; } ;

/* Variables and functions */
 scalar_t__ RPM_SUSPENDED ; 
 scalar_t__ ktime_get_mono_fast_ns () ; 

__attribute__((used)) static void update_pm_runtime_accounting(struct device *dev)
{
	u64 now, last, delta;

	if (dev->power.disable_depth > 0)
		return;

	last = dev->power.accounting_timestamp;

	now = ktime_get_mono_fast_ns();
	dev->power.accounting_timestamp = now;

	/*
	 * Because ktime_get_mono_fast_ns() is not monotonic during
	 * timekeeping updates, ensure that 'now' is after the last saved
	 * timesptamp.
	 */
	if (now < last)
		return;

	delta = now - last;

	if (dev->power.runtime_status == RPM_SUSPENDED)
		dev->power.suspended_time += delta;
	else
		dev->power.active_time += delta;
}
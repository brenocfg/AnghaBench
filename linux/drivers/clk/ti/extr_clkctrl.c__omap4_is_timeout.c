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
union omap4_timeout {int /*<<< orphan*/  start; int /*<<< orphan*/  cycles; } ;
typedef  scalar_t__ u32 ;

/* Variables and functions */
 scalar_t__ _early_timeout ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  ktime_to_ns (int /*<<< orphan*/ ) ; 
 scalar_t__ ktime_us_delta (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ timekeeping_suspended ; 
 int /*<<< orphan*/  udelay (int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool _omap4_is_timeout(union omap4_timeout *time, u32 timeout)
{
	/*
	 * There are two special cases where ktime_to_ns() can't be
	 * used to track the timeouts. First one is during early boot
	 * when the timers haven't been initialized yet. The second
	 * one is during suspend-resume cycle while timekeeping is
	 * being suspended / resumed. Clocksource for the system
	 * can be from a timer that requires pm_runtime access, which
	 * will eventually bring us here with timekeeping_suspended,
	 * during both suspend entry and resume paths. This happens
	 * at least on am43xx platform. Account for flakeyness
	 * with udelay() by multiplying the timeout value by 2.
	 */
	if (unlikely(_early_timeout || timekeeping_suspended)) {
		if (time->cycles++ < timeout) {
			udelay(1 * 2);
			return false;
		}
	} else {
		if (!ktime_to_ns(time->start)) {
			time->start = ktime_get();
			return false;
		}

		if (ktime_us_delta(ktime_get(), time->start) < timeout) {
			cpu_relax();
			return false;
		}
	}

	return true;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ expires; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  POWERDOWN_FREQ ; 
 int POWERDOWN_TIMEOUT ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  blink_timeout (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blink_timer ; 
 int /*<<< orphan*/  blink_timer_timeout ; 
 scalar_t__ has_panicked ; 
 int /*<<< orphan*/  ip32_poweroff (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ip32_rtc_device ; 
 scalar_t__ jiffies ; 
 scalar_t__ kill_cad_pid (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  power_timeout ; 
 TYPE_1__ power_timer ; 
 int shutting_down ; 
 int /*<<< orphan*/  timer_setup (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ip32_prepare_poweroff(void)
{
	if (has_panicked)
		return;

	if (shutting_down || kill_cad_pid(SIGINT, 1)) {
		/* No init process or button pressed twice.  */
		ip32_poweroff(&ip32_rtc_device);
	}

	shutting_down = 1;
	blink_timer_timeout = POWERDOWN_FREQ;
	blink_timeout(&blink_timer);

	timer_setup(&power_timer, power_timeout, 0);
	power_timer.expires = jiffies + POWERDOWN_TIMEOUT * HZ;
	add_timer(&power_timer);
}
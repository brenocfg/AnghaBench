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

/* Variables and functions */
 int /*<<< orphan*/  LED_FULL ; 
 int /*<<< orphan*/  cpu_wait () ; 
 int /*<<< orphan*/  led_trigger_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  power_off_led_trigger ; 

void cobalt_machine_halt(void)
{
	/*
	 * turn on power off LED on RaQ
	 */
	led_trigger_event(power_off_led_trigger, LED_FULL);

	local_irq_disable();
	while (1) {
		if (cpu_wait)
			cpu_wait();
	}
}
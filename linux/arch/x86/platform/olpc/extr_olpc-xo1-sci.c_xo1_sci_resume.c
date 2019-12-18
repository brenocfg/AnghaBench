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
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EC_SCI_SRC_ALL ; 
 int /*<<< orphan*/  GPIO_EVENTS_ENABLE ; 
 int /*<<< orphan*/  OLPC_GPIO_LID ; 
 int /*<<< orphan*/  ac_status_changed () ; 
 int /*<<< orphan*/  battery_status_changed () ; 
 int /*<<< orphan*/  cs5535_gpio_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  detect_lid_state () ; 
 int /*<<< orphan*/  olpc_ec_mask_write (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_lid_state () ; 

__attribute__((used)) static int xo1_sci_resume(struct platform_device *pdev)
{
	/*
	 * We don't know what may have happened while we were asleep.
	 * Reestablish our lid setup so we're sure to catch all transitions.
	 */
	detect_lid_state();
	send_lid_state();
	cs5535_gpio_set(OLPC_GPIO_LID, GPIO_EVENTS_ENABLE);

	/* Enable all EC events */
	olpc_ec_mask_write(EC_SCI_SRC_ALL);

	/* Power/battery status might have changed too */
	battery_status_changed();
	ac_status_changed();
	return 0;
}
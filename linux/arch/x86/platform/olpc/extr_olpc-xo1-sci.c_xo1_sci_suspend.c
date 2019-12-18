#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int dummy; } ;
typedef  int /*<<< orphan*/  pm_message_t ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS5536_PM_PWRBTN ; 
 int /*<<< orphan*/  EC_SCI_SRC_EBOOK ; 
 int /*<<< orphan*/  GPIO_EVENTS_ENABLE ; 
 int /*<<< orphan*/  GPIO_NEGATIVE_EDGE_STS ; 
 int /*<<< orphan*/  GPIO_POSITIVE_EDGE_STS ; 
 scalar_t__ LID_WAKE_CLOSE ; 
 scalar_t__ LID_WAKE_OPEN ; 
 int /*<<< orphan*/  OLPC_GPIO_LID ; 
 int /*<<< orphan*/  cs5535_gpio_clear (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cs5535_gpio_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ device_may_wakeup (int /*<<< orphan*/ *) ; 
 TYPE_3__* ebook_switch_idev ; 
 int /*<<< orphan*/  flip_lid_inverter () ; 
 scalar_t__ lid_open ; 
 TYPE_2__* lid_switch_idev ; 
 scalar_t__ lid_wake_mode ; 
 int /*<<< orphan*/  olpc_ec_wakeup_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  olpc_ec_wakeup_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  olpc_xo1_pm_wakeup_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  olpc_xo1_pm_wakeup_set (int /*<<< orphan*/ ) ; 
 TYPE_1__* power_button_idev ; 

__attribute__((used)) static int xo1_sci_suspend(struct platform_device *pdev, pm_message_t state)
{
	if (device_may_wakeup(&power_button_idev->dev))
		olpc_xo1_pm_wakeup_set(CS5536_PM_PWRBTN);
	else
		olpc_xo1_pm_wakeup_clear(CS5536_PM_PWRBTN);

	if (device_may_wakeup(&ebook_switch_idev->dev))
		olpc_ec_wakeup_set(EC_SCI_SRC_EBOOK);
	else
		olpc_ec_wakeup_clear(EC_SCI_SRC_EBOOK);

	if (!device_may_wakeup(&lid_switch_idev->dev)) {
		cs5535_gpio_clear(OLPC_GPIO_LID, GPIO_EVENTS_ENABLE);
	} else if ((lid_open && lid_wake_mode == LID_WAKE_OPEN) ||
		   (!lid_open && lid_wake_mode == LID_WAKE_CLOSE)) {
		flip_lid_inverter();

		/* we may have just caused an event */
		cs5535_gpio_set(OLPC_GPIO_LID, GPIO_NEGATIVE_EDGE_STS);
		cs5535_gpio_set(OLPC_GPIO_LID, GPIO_POSITIVE_EDGE_STS);

		cs5535_gpio_set(OLPC_GPIO_LID, GPIO_EVENTS_ENABLE);
	}

	return 0;
}
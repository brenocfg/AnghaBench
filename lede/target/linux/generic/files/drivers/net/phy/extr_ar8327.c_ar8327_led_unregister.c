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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct ar8327_led {scalar_t__ mode; int /*<<< orphan*/  led_work; TYPE_1__ cdev; } ;

/* Variables and functions */
 scalar_t__ AR8327_LED_MODE_HW ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_attr_enable_hw_mode ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  led_classdev_unregister (TYPE_1__*) ; 

__attribute__((used)) static void
ar8327_led_unregister(struct ar8327_led *aled)
{
	if (aled->mode == AR8327_LED_MODE_HW)
		device_remove_file(aled->cdev.dev, &dev_attr_enable_hw_mode);

	led_classdev_unregister(&aled->cdev);
	cancel_work_sync(&aled->led_work);
}
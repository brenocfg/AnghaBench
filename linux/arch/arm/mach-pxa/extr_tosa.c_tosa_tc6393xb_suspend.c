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
 int /*<<< orphan*/  TOSA_GPIO_TC6393XB_L3V_ON ; 
 int /*<<< orphan*/  TOSA_GPIO_TC6393XB_SUSPEND ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tosa_tc6393xb_suspend(struct platform_device *dev)
{
	gpio_set_value(TOSA_GPIO_TC6393XB_L3V_ON, 0);
	gpio_set_value(TOSA_GPIO_TC6393XB_SUSPEND, 0);
	return 0;
}
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
 int /*<<< orphan*/  GPIO_ESERIES_TMIO_PCLR ; 
 int /*<<< orphan*/  GPIO_ESERIES_TMIO_SUSPEND ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int eseries_tmio_disable(struct platform_device *dev)
{
	gpio_set_value(GPIO_ESERIES_TMIO_SUSPEND, 0);
	gpio_set_value(GPIO_ESERIES_TMIO_PCLR, 0);
	return 0;
}
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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */

__attribute__((used)) static int
rk_gpio_pin_getcaps(device_t dev, uint32_t pin, uint32_t *caps)
{

	/* Caps are managed by the pinctrl device */
	/* XXX Pass this to parent (pinctrl) */
	*caps = 0;
	return (0);
}
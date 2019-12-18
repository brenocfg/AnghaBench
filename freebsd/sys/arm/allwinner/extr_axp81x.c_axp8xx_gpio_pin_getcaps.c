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
 int EINVAL ; 
 scalar_t__ GPIO_PIN_INPUT ; 
 scalar_t__ GPIO_PIN_OUTPUT ; 
 int /*<<< orphan*/  axp8xx_pins ; 
 scalar_t__ nitems (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
axp8xx_gpio_pin_getcaps(device_t dev, uint32_t pin, uint32_t *caps)
{
	if (pin >= nitems(axp8xx_pins))
		return (EINVAL);

	*caps = GPIO_PIN_INPUT | GPIO_PIN_OUTPUT;

	return (0);
}
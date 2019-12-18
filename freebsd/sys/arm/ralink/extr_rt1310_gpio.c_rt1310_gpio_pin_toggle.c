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
typedef  int uint32_t ;
struct rt1310_gpio_pinmap {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
 int GPIO_PIN_OUTPUT ; 
 int /*<<< orphan*/  panic (char*) ; 
 struct rt1310_gpio_pinmap* rt1310_gpio_get_pinmap (int) ; 
 scalar_t__ rt1310_gpio_pin_getflags (int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static int
rt1310_gpio_pin_toggle(device_t dev, uint32_t pin)
{
	const struct rt1310_gpio_pinmap *map;
	uint32_t flags;

	map = rt1310_gpio_get_pinmap(pin);

	if (rt1310_gpio_pin_getflags(dev, pin, &flags))
		return (ENXIO);

	if ((flags & GPIO_PIN_OUTPUT) == 0)
		return (EINVAL);
	
	panic("not implemented yet");

	return (0);

}
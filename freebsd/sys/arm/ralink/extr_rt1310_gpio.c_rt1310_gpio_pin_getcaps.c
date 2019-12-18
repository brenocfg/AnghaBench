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
struct rt1310_gpio_pinmap {scalar_t__ lp_flags; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ RT_GPIO_NPINS ; 
 struct rt1310_gpio_pinmap* rt1310_gpio_get_pinmap (scalar_t__) ; 

__attribute__((used)) static int
rt1310_gpio_pin_getcaps(device_t dev, uint32_t pin, uint32_t *caps)
{
	const struct rt1310_gpio_pinmap *map;

	if (pin > RT_GPIO_NPINS)
		return (ENODEV);

	map = rt1310_gpio_get_pinmap(pin);

	*caps = map->lp_flags;
	return (0);
}
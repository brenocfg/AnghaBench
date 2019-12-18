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
struct rt1310_gpio_pinmap {int lp_start_idx; int lp_pin_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  panic (char*,int) ; 
 struct rt1310_gpio_pinmap* rt1310_gpio_pins ; 

__attribute__((used)) static const struct rt1310_gpio_pinmap *
rt1310_gpio_get_pinmap(int pin)
{
	const struct rt1310_gpio_pinmap *map;

	for (map = &rt1310_gpio_pins[0]; map->lp_start_idx != -1; map++) {
		if (pin >= map->lp_start_idx &&
		    pin < map->lp_start_idx + map->lp_pin_count)
			return map;
	}

	panic("pin number %d out of range", pin);
}
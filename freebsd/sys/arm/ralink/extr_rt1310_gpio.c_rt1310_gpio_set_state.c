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
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  lg_dev; } ;

/* Variables and functions */
 int ENXIO ; 
 int rt1310_gpio_pin_set (int /*<<< orphan*/ ,int,int) ; 
 TYPE_1__* rt1310_gpio_sc ; 

int
rt1310_gpio_set_state(device_t dev, int pin, int state)
{
	if (rt1310_gpio_sc == NULL)
		return (ENXIO);

	return rt1310_gpio_pin_set(rt1310_gpio_sc->lg_dev, pin, state); 
}
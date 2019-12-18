#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  TYPE_1__* gpio_pin_t ;
struct TYPE_3__ {int flags; int /*<<< orphan*/  pin; int /*<<< orphan*/ * dev; } ;

/* Variables and functions */
 int GPIO_ACTIVE_LOW ; 
 int GPIO_PIN_SET (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 

int
gpio_pin_set_active(gpio_pin_t pin, bool active)
{
	int rv;
	uint32_t tmp;

	if (pin->flags & GPIO_ACTIVE_LOW)
		tmp = active ? 0 : 1;
	else
		tmp = active ? 1 : 0;

	KASSERT(pin != NULL, ("GPIO pin is NULL."));
	KASSERT(pin->dev != NULL, ("GPIO pin device is NULL."));
	rv = GPIO_PIN_SET(pin->dev, pin->pin, tmp);
	return (rv);
}
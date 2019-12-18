#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* gpio_pin_t ;
typedef  int /*<<< orphan*/ * device_t ;
struct TYPE_4__ {int /*<<< orphan*/  pin; int /*<<< orphan*/ * dev; } ;

/* Variables and functions */
 int /*<<< orphan*/ * GPIO_GET_BUS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  free (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiobus_release_pin (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
gpio_pin_release(gpio_pin_t gpio)
{
	device_t busdev;

	if (gpio == NULL)
		return;

	KASSERT(gpio->dev != NULL, ("invalid pin state"));

	busdev = GPIO_GET_BUS(gpio->dev);
	if (busdev != NULL)
		gpiobus_release_pin(busdev, gpio->pin);

	/* XXXX Unreserve pin. */
	free(gpio, M_DEVBUF);
}
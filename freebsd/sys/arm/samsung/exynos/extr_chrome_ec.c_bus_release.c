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
struct ec_softc {scalar_t__ ec_gpio; int /*<<< orphan*/  our_gpio; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_PIN_HIGH ; 
 int /*<<< orphan*/  GPIO_PIN_SET (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devclass_find (char*) ; 
 int /*<<< orphan*/ * devclass_get_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
bus_release(struct ec_softc *sc)
{
	device_t gpio_dev;

	if (sc->our_gpio == 0 || sc->ec_gpio == 0) {
		device_printf(sc->dev, "i2c arbitrator is not configured\n");
		return (1);
	}

	gpio_dev = devclass_get_device(devclass_find("gpio"), 0);
	if (gpio_dev == NULL) {
		device_printf(sc->dev, "cant find gpio_dev\n");
		return (1);
	}

	GPIO_PIN_SET(gpio_dev, sc->our_gpio, GPIO_PIN_HIGH);

	return (0);
}
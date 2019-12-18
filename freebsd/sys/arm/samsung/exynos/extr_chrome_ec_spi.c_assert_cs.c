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
struct ec_softc {int /*<<< orphan*/ * dev_gpio; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EC_SPI_CS ; 
 int /*<<< orphan*/  GPIO_PIN_HIGH ; 
 int /*<<< orphan*/  GPIO_PIN_LOW ; 
 int /*<<< orphan*/  GPIO_PIN_OUTPUT ; 
 int /*<<< orphan*/  GPIO_PIN_SET (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPIO_PIN_SETFLAGS (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devclass_find (char*) ; 
 int /*<<< orphan*/ * devclass_get_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
assert_cs(struct ec_softc *sc, int enable)
{
	/* Get the GPIO device */
	sc->dev_gpio = devclass_get_device(devclass_find("gpio"), 0);
	if (sc->dev_gpio == NULL) {
		device_printf(sc->dev, "Error: failed to get the GPIO dev\n");
		return (1);
	}

	GPIO_PIN_SETFLAGS(sc->dev_gpio, EC_SPI_CS, GPIO_PIN_OUTPUT);

	if (enable) {
		GPIO_PIN_SET(sc->dev_gpio, EC_SPI_CS, GPIO_PIN_LOW);
	} else {
		GPIO_PIN_SET(sc->dev_gpio, EC_SPI_CS, GPIO_PIN_HIGH);
	}

	return (0);
}
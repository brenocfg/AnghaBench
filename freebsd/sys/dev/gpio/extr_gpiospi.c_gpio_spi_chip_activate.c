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
struct gpio_spi_softc {int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_cs3; int /*<<< orphan*/  sc_busdev; int /*<<< orphan*/  sc_cs2; int /*<<< orphan*/  sc_cs1; int /*<<< orphan*/  sc_cs0; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOBUS_PIN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  gpio_delay (struct gpio_spi_softc*) ; 

__attribute__((used)) static void
gpio_spi_chip_activate(struct gpio_spi_softc *sc, int cs)
{

	/* called with locked gpiobus */
	switch (cs) {
	case 0:
		GPIOBUS_PIN_SET(sc->sc_busdev, sc->sc_dev,
		    sc->sc_cs0, 0);
		break;
	case 1:
		GPIOBUS_PIN_SET(sc->sc_busdev, sc->sc_dev,
		    sc->sc_cs1, 0);
		break;
	case 2:
		GPIOBUS_PIN_SET(sc->sc_busdev, sc->sc_dev,
		    sc->sc_cs2, 0);
		break;
	case 3:
		GPIOBUS_PIN_SET(sc->sc_busdev, sc->sc_dev,
		    sc->sc_cs3, 0);
		break;
	default:
		device_printf(sc->sc_dev, "don't have CS%d\n", cs);
	}

	gpio_delay(sc);
}
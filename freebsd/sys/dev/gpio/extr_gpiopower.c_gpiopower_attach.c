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
struct gpiopower_softc {int sc_rbmask; int /*<<< orphan*/ * sc_pin; } ;
typedef  int phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPIO_PIN_OUTPUT ; 
 int RB_HALT ; 
 int RB_POWEROFF ; 
 int /*<<< orphan*/  SHUTDOWN_PRI_LAST ; 
 struct gpiopower_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gpio_pin_setflags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiopower_assert ; 
 int ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 scalar_t__ ofw_bus_is_compatible (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ofw_gpiobus_parse_gpios (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  shutdown_final ; 

__attribute__((used)) static int
gpiopower_attach(device_t dev)
{
	struct gpiopower_softc *sc;
	phandle_t node;

	sc = device_get_softc(dev);

	if ((node = ofw_bus_get_node(dev)) == -1)
		return (ENXIO);

	ofw_gpiobus_parse_gpios(dev, "gpios", &sc->sc_pin);
	if (sc->sc_pin == NULL) {
		device_printf(dev, "failed to map GPIO pin\n");
		return (ENXIO);
	}

	if (ofw_bus_is_compatible(dev, "gpio-poweroff"))
		sc->sc_rbmask = RB_HALT | RB_POWEROFF;
	else
		sc->sc_rbmask = 0;
	EVENTHANDLER_REGISTER(shutdown_final, gpiopower_assert, dev,
	    SHUTDOWN_PRI_LAST);
	gpio_pin_setflags(sc->sc_pin, GPIO_PIN_OUTPUT);

	return (0);
}
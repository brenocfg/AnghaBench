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
struct a37x0_gpio_softc {scalar_t__ sc_npins; scalar_t__ sc_max_pins; int /*<<< orphan*/ * sc_busdev; int /*<<< orphan*/  syscon; } ;
typedef  scalar_t__ pcell_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int OF_getencprop_alloc (int /*<<< orphan*/ ,char*,void**) ; 
 int /*<<< orphan*/  OF_prop_free (scalar_t__*) ; 
 struct a37x0_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * gpiobus_attach_bus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int syscon_get_handle_default (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
a37x0_gpio_attach(device_t dev)
{
	int err, ncells;
	pcell_t *ranges;
	struct a37x0_gpio_softc *sc;

	sc = device_get_softc(dev);

	err = syscon_get_handle_default(dev, &sc->syscon);
	if (err != 0) {
		device_printf(dev, "Cannot get syscon handle from parent\n");
		return (ENXIO);
	}

	/* Read and verify the "gpio-ranges" property. */
	ncells = OF_getencprop_alloc(ofw_bus_get_node(dev), "gpio-ranges",
	    (void **)&ranges);
	if (ncells == -1)
		return (ENXIO);
	if (ncells != sizeof(*ranges) * 4 || ranges[1] != 0 || ranges[2] != 0) {
		OF_prop_free(ranges);
		return (ENXIO);
	}
	sc->sc_npins = ranges[3];
	OF_prop_free(ranges);

	/* Check the number of pins in the DTS vs HW capabilities. */
	if (sc->sc_npins > sc->sc_max_pins)
		return (ENXIO);

	sc->sc_busdev = gpiobus_attach_bus(dev);
	if (sc->sc_busdev == NULL)
		return (ENXIO);

	return (0);
}
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
struct a37x0_gpio_softc {int sc_type; int sc_max_pins; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int ocd_data; } ;

/* Variables and functions */
#define  A37X0_NB_GPIO 129 
#define  A37X0_SB_GPIO 128 
 int BUS_PROBE_DEFAULT ; 
 int ENXIO ; 
 int /*<<< orphan*/  OF_hasprop (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  compat_data ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct a37x0_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 TYPE_1__* ofw_bus_search_compatible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
a37x0_gpio_probe(device_t dev)
{
	const char *desc;
	struct a37x0_gpio_softc *sc;

	if (!OF_hasprop(ofw_bus_get_node(dev), "gpio-controller"))
		return (ENXIO);

	sc = device_get_softc(dev);
	sc->sc_type = ofw_bus_search_compatible(
	    device_get_parent(dev), compat_data)->ocd_data;
	switch (sc->sc_type) {
	case A37X0_NB_GPIO:
		sc->sc_max_pins = 36;
		desc = "Armada 37x0 North Bridge GPIO Controller";
		break;
	case A37X0_SB_GPIO:
		sc->sc_max_pins = 30;
		desc = "Armada 37x0 South Bridge GPIO Controller";
		break;
	default:
		return (ENXIO);
	}
	device_set_desc(dev, desc);

	return (BUS_PROBE_DEFAULT);
}
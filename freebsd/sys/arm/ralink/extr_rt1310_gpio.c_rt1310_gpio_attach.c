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
struct rt1310_gpio_softc {int /*<<< orphan*/  lg_res; int /*<<< orphan*/ * lg_busdev; int /*<<< orphan*/  lg_bsh; int /*<<< orphan*/  lg_bst; int /*<<< orphan*/  lg_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct rt1310_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * gpiobus_attach_bus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ ) ; 
 struct rt1310_gpio_softc* rt1310_gpio_sc ; 

__attribute__((used)) static int
rt1310_gpio_attach(device_t dev)
{
	struct rt1310_gpio_softc *sc = device_get_softc(dev);
	int rid;

	sc->lg_dev = dev;

	rid = 0;
	sc->lg_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid,
	    RF_ACTIVE);
	if (!sc->lg_res) {
		device_printf(dev, "cannot allocate memory window\n");
		return (ENXIO);
	}

	sc->lg_bst = rman_get_bustag(sc->lg_res);
	sc->lg_bsh = rman_get_bushandle(sc->lg_res);

	rt1310_gpio_sc = sc;

	sc->lg_busdev = gpiobus_attach_bus(dev);
	if (sc->lg_busdev == NULL) {
		bus_release_resource(dev, SYS_RES_MEMORY, rid, sc->lg_res);
		return (ENXIO);
	}

	return (0);
}
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
struct omap4_prcm_softc {int sc_instance; int /*<<< orphan*/ * sc_res; int /*<<< orphan*/  sc_rid; } ;
struct ofw_compat_data {scalar_t__ ocd_data; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compat_data ; 
 struct omap4_prcm_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 struct ofw_compat_data* ofw_bus_search_compatible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap4_prcm_reset ; 
 int /*<<< orphan*/  ti_cpu_reset ; 

__attribute__((used)) static int
omap4_prcm_attach(device_t dev)
{
	struct omap4_prcm_softc *sc;
	const struct ofw_compat_data *ocd;

	sc = device_get_softc(dev);
	ocd = ofw_bus_search_compatible(dev, compat_data);
	sc->sc_instance = (int)ocd->ocd_data;

	sc->sc_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &sc->sc_rid,
	    RF_ACTIVE);
	if (sc->sc_res == NULL) {
		device_printf(dev, "could not allocate resources\n");
		return (ENXIO);
	}

	ti_cpu_reset = omap4_prcm_reset;

	return (0);
}
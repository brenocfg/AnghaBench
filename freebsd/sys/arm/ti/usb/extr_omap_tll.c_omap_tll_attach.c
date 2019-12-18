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
struct omap_tll_softc {int /*<<< orphan*/  tll_mem_res; scalar_t__ tll_mem_rid; int /*<<< orphan*/  sc_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 struct omap_tll_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  omap_tll_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_tll_init (struct omap_tll_softc*) ; 
 struct omap_tll_softc* omap_tll_sc ; 

__attribute__((used)) static int
omap_tll_attach(device_t dev)
{
	struct omap_tll_softc *sc;

	sc = device_get_softc(dev);
	/* save the device */
	sc->sc_dev = dev;

	/* Allocate resource for the TLL register set */
	sc->tll_mem_rid = 0;
	sc->tll_mem_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY,
	    &sc->tll_mem_rid, RF_ACTIVE);
	if (!sc->tll_mem_res) {
		device_printf(dev, "Error: Could not map TLL memory\n");
		goto error;
	}

	omap_tll_init(sc);

	omap_tll_sc = sc;

	return (0);

error:
	omap_tll_detach(dev);
	return (ENXIO);
}
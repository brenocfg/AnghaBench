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
struct soctherm_softc {int ntsensors; int /*<<< orphan*/ * mem_res; int /*<<< orphan*/ * irq_res; int /*<<< orphan*/ * reset; int /*<<< orphan*/ * soctherm_clk; int /*<<< orphan*/ * tsensor_clk; int /*<<< orphan*/ * irq_ih; int /*<<< orphan*/  dev; scalar_t__ tsensors; } ;
struct soctherm_shared_cal {int dummy; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  OF_device_register_xref (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OF_xref_from_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  TSENSOR_HOTSPOT_OFF ; 
 int /*<<< orphan*/  TSENSOR_HOTSPOT_OFF_T124 ; 
 int /*<<< orphan*/  TSENSOR_PDIV ; 
 int /*<<< orphan*/  TSENSOR_PDIV_T124 ; 
 int /*<<< orphan*/  WR4 (struct soctherm_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int clk_enable (int /*<<< orphan*/ *) ; 
 int clk_get_by_ofw_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  clk_release (int /*<<< orphan*/ *) ; 
 struct soctherm_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  get_shared_cal (struct soctherm_softc*,struct soctherm_shared_cal*) ; 
 int hwreset_assert (int /*<<< orphan*/ *) ; 
 int hwreset_deassert (int /*<<< orphan*/ *) ; 
 int hwreset_get_by_ofw_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  hwreset_release (int /*<<< orphan*/ *) ; 
 int nitems (scalar_t__) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int soctherm_init_sysctl (struct soctherm_softc*) ; 
 int /*<<< orphan*/  soctherm_init_tsensor (struct soctherm_softc*,scalar_t__,struct soctherm_shared_cal*) ; 
 int /*<<< orphan*/  soctherm_sysctl_ctx ; 
 int /*<<< orphan*/  sysctl_ctx_free (int /*<<< orphan*/ *) ; 
 scalar_t__ t124_tsensors ; 

__attribute__((used)) static int
soctherm_attach(device_t dev)
{
	struct soctherm_softc *sc;
	phandle_t node;
	int i, rid, rv;
	struct soctherm_shared_cal shared_calib;

	sc = device_get_softc(dev);
	sc->dev = dev;
	node = ofw_bus_get_node(sc->dev);

	rid = 0;
	sc->mem_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid,
	    RF_ACTIVE);
	if (sc->mem_res == NULL) {
		device_printf(dev, "Cannot allocate memory resources\n");
		goto fail;
	}

	rid = 0;
	sc->irq_res = bus_alloc_resource_any(dev, SYS_RES_IRQ, &rid, RF_ACTIVE);
	if (sc->irq_res == NULL) {
		device_printf(dev, "Cannot allocate IRQ resources\n");
		goto fail;
	}

/*
	if ((bus_setup_intr(dev, sc->irq_res, INTR_TYPE_MISC,
	    soctherm_intr, NULL, sc, &sc->irq_ih))) {
		device_printf(dev,
		    "WARNING: unable to register interrupt handler\n");
		goto fail;
	}
*/

	/* OWF resources */
	rv = hwreset_get_by_ofw_name(dev, 0, "soctherm", &sc->reset);
	if (rv != 0) {
		device_printf(dev, "Cannot get fuse reset\n");
		goto fail;
	}
	rv = clk_get_by_ofw_name(dev, 0, "tsensor", &sc->tsensor_clk);
	if (rv != 0) {
		device_printf(dev, "Cannot get 'tsensor' clock: %d\n", rv);
		goto fail;
	}
	rv = clk_get_by_ofw_name(dev, 0, "soctherm", &sc->soctherm_clk);
	if (rv != 0) {
		device_printf(dev, "Cannot get 'soctherm' clock: %d\n", rv);
		goto fail;
	}

	rv = hwreset_assert(sc->reset);
	if (rv != 0) {
		device_printf(dev, "Cannot assert reset\n");
		goto fail;
	}
	rv = clk_enable(sc->tsensor_clk);
	if (rv != 0) {
		device_printf(dev, "Cannot enable 'tsensor' clock: %d\n", rv);
		goto fail;
	}
	rv = clk_enable(sc->soctherm_clk);
	if (rv != 0) {
		device_printf(dev, "Cannot enable 'soctherm' clock: %d\n", rv);
		goto fail;
	}
	rv = hwreset_deassert(sc->reset);
	if (rv != 0) {
		device_printf(dev, "Cannot clear reset\n");
		goto fail;
	}

	/* Tegra 124 */
	sc->tsensors = t124_tsensors;
	sc->ntsensors = nitems(t124_tsensors);
	get_shared_cal(sc, &shared_calib);

	WR4(sc, TSENSOR_PDIV, TSENSOR_PDIV_T124);
	WR4(sc, TSENSOR_HOTSPOT_OFF, TSENSOR_HOTSPOT_OFF_T124);

	for (i = 0; i < sc->ntsensors; i++)
		soctherm_init_tsensor(sc, sc->tsensors + i, &shared_calib);

	rv = soctherm_init_sysctl(sc);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot initialize sysctls\n");
		goto fail;
	}

	OF_device_register_xref(OF_xref_from_node(node), dev);
	return (bus_generic_attach(dev));

fail:
	if (sc->irq_ih != NULL)
		bus_teardown_intr(dev, sc->irq_res, sc->irq_ih);
	sysctl_ctx_free(&soctherm_sysctl_ctx);
	if (sc->tsensor_clk != NULL)
		clk_release(sc->tsensor_clk);
	if (sc->soctherm_clk != NULL)
		clk_release(sc->soctherm_clk);
	if (sc->reset != NULL)
		hwreset_release(sc->reset);
	if (sc->irq_res != NULL)
		bus_release_resource(dev, SYS_RES_IRQ, 0, sc->irq_res);
	if (sc->mem_res != NULL)
		bus_release_resource(dev, SYS_RES_MEMORY, 0, sc->mem_res);

	return (ENXIO);
}
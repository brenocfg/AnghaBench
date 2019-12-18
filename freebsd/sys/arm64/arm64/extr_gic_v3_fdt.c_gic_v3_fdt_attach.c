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
struct TYPE_2__ {int nregions; } ;
struct gic_v3_softc {scalar_t__ gic_nchildren; int /*<<< orphan*/  gic_children; int /*<<< orphan*/ * gic_pic; TYPE_1__ gic_redists; int /*<<< orphan*/  gic_bus; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  redist_regions ;
typedef  int pcell_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  GIC_BUS_FDT ; 
 scalar_t__ GIC_FIRST_SGI ; 
 scalar_t__ GIC_LAST_SGI ; 
 int /*<<< orphan*/  OF_device_register_xref (intptr_t,int /*<<< orphan*/ ) ; 
 scalar_t__ OF_getencprop (int /*<<< orphan*/ ,char*,int*,int) ; 
 intptr_t OF_xref_from_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arm_gic_v3_intr ; 
 scalar_t__ bootverbose ; 
 scalar_t__ device_get_children (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*) ; 
 struct gic_v3_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int gic_v3_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gic_v3_detach (int /*<<< orphan*/ ) ; 
 scalar_t__ gic_v3_ofw_bus_attach (int /*<<< orphan*/ ) ; 
 scalar_t__ intr_pic_claim_root (int /*<<< orphan*/ ,intptr_t,int /*<<< orphan*/ ,struct gic_v3_softc*,scalar_t__) ; 
 int /*<<< orphan*/ * intr_pic_register (int /*<<< orphan*/ ,intptr_t) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
gic_v3_fdt_attach(device_t dev)
{
	struct gic_v3_softc *sc;
	pcell_t redist_regions;
	intptr_t xref;
	int err;

	sc = device_get_softc(dev);
	sc->dev = dev;
	sc->gic_bus = GIC_BUS_FDT;

	/*
	 * Recover number of the Re-Distributor regions.
	 */
	if (OF_getencprop(ofw_bus_get_node(dev), "#redistributor-regions",
	    &redist_regions, sizeof(redist_regions)) <= 0)
		sc->gic_redists.nregions = 1;
	else
		sc->gic_redists.nregions = redist_regions;

	err = gic_v3_attach(dev);
	if (err != 0)
		goto error;

	xref = OF_xref_from_node(ofw_bus_get_node(dev));
	sc->gic_pic = intr_pic_register(dev, xref);
	if (sc->gic_pic == NULL) {
		device_printf(dev, "could not register PIC\n");
		err = ENXIO;
		goto error;
	}

	/* Register xref */
	OF_device_register_xref(xref, dev);

	if (intr_pic_claim_root(dev, xref, arm_gic_v3_intr, sc,
	    GIC_LAST_SGI - GIC_FIRST_SGI + 1) != 0) {
		err = ENXIO;
		goto error;
	}

	/*
	 * Try to register ITS to this GIC.
	 * GIC will act as a bus in that case.
	 * Failure here will not affect main GIC functionality.
	 */
	if (gic_v3_ofw_bus_attach(dev) != 0) {
		if (bootverbose) {
			device_printf(dev,
			    "Failed to attach ITS to this GIC\n");
		}
	}

	if (device_get_children(dev, &sc->gic_children, &sc->gic_nchildren) != 0)
		sc->gic_nchildren = 0;

	return (err);

error:
	if (bootverbose) {
		device_printf(dev,
		    "Failed to attach. Error %d\n", err);
	}
	/* Failure so free resources */
	gic_v3_detach(dev);

	return (err);
}
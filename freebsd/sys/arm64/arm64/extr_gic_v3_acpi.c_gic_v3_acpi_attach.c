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
struct gic_v3_softc {scalar_t__ gic_nchildren; int /*<<< orphan*/  gic_children; int /*<<< orphan*/ * gic_pic; int /*<<< orphan*/  gic_bus; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_INTR_XREF ; 
 int ENXIO ; 
 int /*<<< orphan*/  GIC_BUS_ACPI ; 
 scalar_t__ GIC_FIRST_SGI ; 
 scalar_t__ GIC_LAST_SGI ; 
 int /*<<< orphan*/  arm_gic_v3_intr ; 
 scalar_t__ bootverbose ; 
 scalar_t__ device_get_children (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*) ; 
 struct gic_v3_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  gic_v3_acpi_bus_attach (int /*<<< orphan*/ ) ; 
 int gic_v3_acpi_count_regions (int /*<<< orphan*/ ) ; 
 int gic_v3_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gic_v3_detach (int /*<<< orphan*/ ) ; 
 scalar_t__ intr_pic_claim_root (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gic_v3_softc*,scalar_t__) ; 
 int /*<<< orphan*/ * intr_pic_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
gic_v3_acpi_attach(device_t dev)
{
	struct gic_v3_softc *sc;
	int err;

	sc = device_get_softc(dev);
	sc->dev = dev;
	sc->gic_bus = GIC_BUS_ACPI;

	err = gic_v3_acpi_count_regions(dev);
	if (err != 0)
		goto error;

	err = gic_v3_attach(dev);
	if (err != 0)
		goto error;

	sc->gic_pic = intr_pic_register(dev, ACPI_INTR_XREF);
	if (sc->gic_pic == NULL) {
		device_printf(dev, "could not register PIC\n");
		err = ENXIO;
		goto error;
	}

	if (intr_pic_claim_root(dev, ACPI_INTR_XREF, arm_gic_v3_intr, sc,
	    GIC_LAST_SGI - GIC_FIRST_SGI + 1) != 0) {
		err = ENXIO;
		goto error;
	}

	/*
	 * Try to register the ITS driver to this GIC. The GIC will act as
	 * a bus in that case. Failure here will not affect the main GIC
	 * functionality.
	 */
	gic_v3_acpi_bus_attach(dev);

	if (device_get_children(dev, &sc->gic_children, &sc->gic_nchildren) !=0)
		sc->gic_nchildren = 0;

	return (0);

error:
	if (bootverbose) {
		device_printf(dev,
		    "Failed to attach. Error %d\n", err);
	}
	/* Failure so free resources */
	gic_v3_detach(dev);

	return (err);
}
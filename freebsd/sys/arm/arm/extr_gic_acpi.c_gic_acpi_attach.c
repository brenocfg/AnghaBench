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
struct arm_gic_softc {int /*<<< orphan*/  gic_bus; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 intptr_t ACPI_INTR_XREF ; 
 int ENXIO ; 
 int /*<<< orphan*/  GIC_BUS_ACPI ; 
 scalar_t__ GIC_FIRST_SGI ; 
 scalar_t__ GIC_LAST_SGI ; 
 scalar_t__ arm_gic_add_children (int /*<<< orphan*/ ) ; 
 int arm_gic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arm_gic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arm_gic_intr ; 
 int bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_generic_probe (int /*<<< orphan*/ ) ; 
 struct arm_gic_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ intr_pic_claim_root (int /*<<< orphan*/ ,intptr_t,int /*<<< orphan*/ ,struct arm_gic_softc*,scalar_t__) ; 
 int /*<<< orphan*/  intr_pic_deregister (int /*<<< orphan*/ ,intptr_t) ; 
 int /*<<< orphan*/ * intr_pic_register (int /*<<< orphan*/ ,intptr_t) ; 

__attribute__((used)) static int
gic_acpi_attach(device_t dev)
{
	struct arm_gic_softc *sc = device_get_softc(dev);
	intptr_t xref;
	int err;

	sc->gic_bus = GIC_BUS_ACPI;

	err = arm_gic_attach(dev);
	if (err != 0)
		return (err);

	xref = ACPI_INTR_XREF;

	/*
	 * Now, when everything is initialized, it's right time to
	 * register interrupt controller to interrupt framefork.
	 */
	if (intr_pic_register(dev, xref) == NULL) {
		device_printf(dev, "could not register PIC\n");
		goto cleanup;
	}

	/*
	 * Controller is root:
	 */
	if (intr_pic_claim_root(dev, xref, arm_gic_intr, sc,
	    GIC_LAST_SGI - GIC_FIRST_SGI + 1) != 0) {
		device_printf(dev, "could not set PIC as a root\n");
		intr_pic_deregister(dev, xref);
		goto cleanup;
	}
	/* If we have children probe and attach them */
	if (arm_gic_add_children(dev)) {
		bus_generic_probe(dev);
		return (bus_generic_attach(dev));
	}

	return (0);

cleanup:
	arm_gic_detach(dev);
	return(ENXIO);
}
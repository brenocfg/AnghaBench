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
struct TYPE_2__ {int /*<<< orphan*/  gic_intrhand; int /*<<< orphan*/ ** gic_res; int /*<<< orphan*/  gic_bus; } ;
struct arm_gic_fdt_softc {TYPE_1__ base; } ;
typedef  intptr_t phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  GIC_BUS_FDT ; 
 scalar_t__ GIC_FIRST_SGI ; 
 scalar_t__ GIC_LAST_SGI ; 
 int /*<<< orphan*/  INTR_TYPE_CLK ; 
 int /*<<< orphan*/  OF_device_register_xref (intptr_t,int /*<<< orphan*/ ) ; 
 intptr_t OF_xref_from_node (int /*<<< orphan*/ ) ; 
 scalar_t__ arm_gic_add_children (int /*<<< orphan*/ ) ; 
 int arm_gic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arm_gic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arm_gic_intr ; 
 int bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_generic_probe (int /*<<< orphan*/ ) ; 
 scalar_t__ bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct arm_gic_fdt_softc*,int /*<<< orphan*/ *) ; 
 struct arm_gic_fdt_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ intr_pic_claim_root (int /*<<< orphan*/ ,intptr_t,int /*<<< orphan*/ ,struct arm_gic_fdt_softc*,scalar_t__) ; 
 int /*<<< orphan*/  intr_pic_deregister (int /*<<< orphan*/ ,intptr_t) ; 
 int /*<<< orphan*/ * intr_pic_register (int /*<<< orphan*/ ,intptr_t) ; 
 intptr_t ofw_bus_find_iparent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
gic_fdt_attach(device_t dev)
{
	struct arm_gic_fdt_softc *sc = device_get_softc(dev);
	phandle_t pxref;
	intptr_t xref;
	int err;

	sc->base.gic_bus = GIC_BUS_FDT;

	err = arm_gic_attach(dev);
	if (err != 0)
		return (err);

	xref = OF_xref_from_node(ofw_bus_get_node(dev));

	/*
	 * Now, when everything is initialized, it's right time to
	 * register interrupt controller to interrupt framefork.
	 */
	if (intr_pic_register(dev, xref) == NULL) {
		device_printf(dev, "could not register PIC\n");
		goto cleanup;
	}

	/*
	 * Controller is root if:
	 * - doesn't have interrupt parent
	 * - his interrupt parent is this controller
	 */
	pxref = ofw_bus_find_iparent(ofw_bus_get_node(dev));
	if (pxref == 0 || xref == pxref) {
		if (intr_pic_claim_root(dev, xref, arm_gic_intr, sc,
		    GIC_LAST_SGI - GIC_FIRST_SGI + 1) != 0) {
			device_printf(dev, "could not set PIC as a root\n");
			intr_pic_deregister(dev, xref);
			goto cleanup;
		}
	} else {
		if (sc->base.gic_res[2] == NULL) {
			device_printf(dev,
			    "not root PIC must have defined interrupt\n");
			intr_pic_deregister(dev, xref);
			goto cleanup;
		}
		if (bus_setup_intr(dev, sc->base.gic_res[2], INTR_TYPE_CLK,
		    arm_gic_intr, NULL, sc, &sc->base.gic_intrhand)) {
			device_printf(dev, "could not setup irq handler\n");
			intr_pic_deregister(dev, xref);
			goto cleanup;
		}
	}

	OF_device_register_xref(xref, dev);

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
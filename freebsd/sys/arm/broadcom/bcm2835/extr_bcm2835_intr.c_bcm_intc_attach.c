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
struct bcm_intc_softc {int /*<<< orphan*/ * intc_res; int /*<<< orphan*/  intc_bsh; int /*<<< orphan*/  intc_bst; int /*<<< orphan*/  intc_irq_hdl; int /*<<< orphan*/ * intc_irq_res; int /*<<< orphan*/  sc_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  INTR_TYPE_CLK ; 
 intptr_t OF_xref_from_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bcm2835_intc_intr ; 
 scalar_t__ bcm_intc_pic_register (struct bcm_intc_softc*,intptr_t) ; 
 struct bcm_intc_softc* bcm_intc_sc ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct bcm_intc_softc*,int /*<<< orphan*/ *) ; 
 struct bcm_intc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ intr_pic_claim_root (int /*<<< orphan*/ ,intptr_t,int /*<<< orphan*/ ,struct bcm_intc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
bcm_intc_attach(device_t dev)
{
	struct		bcm_intc_softc *sc = device_get_softc(dev);
	int		rid = 0;
	intptr_t	xref;
	sc->sc_dev = dev;

	if (bcm_intc_sc)
		return (ENXIO);

	sc->intc_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid, RF_ACTIVE);
	if (sc->intc_res == NULL) {
		device_printf(dev, "could not allocate memory resource\n");
		return (ENXIO);
	}

	xref = OF_xref_from_node(ofw_bus_get_node(dev));
	if (bcm_intc_pic_register(sc, xref) != 0) {
		bus_release_resource(dev, SYS_RES_MEMORY, 0, sc->intc_res);
		device_printf(dev, "could not register PIC\n");
		return (ENXIO);
	}

	rid = 0;
	sc->intc_irq_res = bus_alloc_resource_any(dev, SYS_RES_IRQ, &rid,
	    RF_ACTIVE);
	if (sc->intc_irq_res == NULL) {
		if (intr_pic_claim_root(dev, xref, bcm2835_intc_intr, sc, 0) != 0) {
			/* XXX clean up */
			device_printf(dev, "could not set PIC as a root\n");
			return (ENXIO);
		}
	} else {
		if (bus_setup_intr(dev, sc->intc_irq_res, INTR_TYPE_CLK,
		    bcm2835_intc_intr, NULL, sc, &sc->intc_irq_hdl)) {
			/* XXX clean up */
			device_printf(dev, "could not setup irq handler\n");
			return (ENXIO);
		}
	}
	sc->intc_bst = rman_get_bustag(sc->intc_res);
	sc->intc_bsh = rman_get_bushandle(sc->intc_res);

	bcm_intc_sc = sc;

	return (0);
}
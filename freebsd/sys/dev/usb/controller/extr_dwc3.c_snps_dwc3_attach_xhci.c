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
struct TYPE_2__ {int /*<<< orphan*/ * bdev; } ;
struct xhci_softc {TYPE_1__ sc_bus; int /*<<< orphan*/ * sc_intr_hdl; int /*<<< orphan*/ * sc_irq_res; int /*<<< orphan*/  sc_vendor; int /*<<< orphan*/  sc_io_size; int /*<<< orphan*/  sc_io_hdl; int /*<<< orphan*/  sc_io_tag; int /*<<< orphan*/  sc_io_res; } ;
struct snps_dwc3_softc {int /*<<< orphan*/  mem_res; int /*<<< orphan*/  bsh; int /*<<< orphan*/  bst; struct xhci_softc sc; } ;
typedef  int /*<<< orphan*/  driver_intr_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_BIO ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct xhci_softc*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 struct snps_dwc3_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int device_probe_and_attach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  rman_get_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*) ; 
 int xhci_init (struct xhci_softc*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ xhci_interrupt ; 
 int xhci_start_controller (struct xhci_softc*) ; 

__attribute__((used)) static int
snps_dwc3_attach_xhci(device_t dev)
{
	struct snps_dwc3_softc *snps_sc = device_get_softc(dev);
	struct xhci_softc *sc = &snps_sc->sc;
	int err = 0, rid = 0;

	sc->sc_io_res = snps_sc->mem_res;
	sc->sc_io_tag = snps_sc->bst;
	sc->sc_io_hdl = snps_sc->bsh;
	sc->sc_io_size = rman_get_size(snps_sc->mem_res);

	sc->sc_irq_res = bus_alloc_resource_any(dev, SYS_RES_IRQ, &rid,
	    RF_SHAREABLE | RF_ACTIVE);
	if (sc->sc_irq_res == NULL) {
		device_printf(dev, "Failed to allocate IRQ\n");
		return (ENXIO);
	}

	sc->sc_bus.bdev = device_add_child(dev, "usbus", -1);
	if (sc->sc_bus.bdev == NULL) {
		device_printf(dev, "Failed to add USB device\n");
		return (ENXIO);
	}

	device_set_ivars(sc->sc_bus.bdev, &sc->sc_bus);

	sprintf(sc->sc_vendor, "Synopsys");
	device_set_desc(sc->sc_bus.bdev, "Synopsys");

	err = bus_setup_intr(dev, sc->sc_irq_res, INTR_TYPE_BIO | INTR_MPSAFE,
	    NULL, (driver_intr_t *)xhci_interrupt, sc, &sc->sc_intr_hdl);
	if (err != 0) {
		device_printf(dev, "Failed to setup IRQ, %d\n", err);
		sc->sc_intr_hdl = NULL;
		return (err);
	}

	err = xhci_init(sc, dev, 1);
	if (err != 0) {
		device_printf(dev, "Failed to init XHCI, with error %d\n", err);
		return (ENXIO);
	}

	err = xhci_start_controller(sc);
	if (err != 0) {
		device_printf(dev, "Failed to start XHCI controller, with error %d\n", err);
		return (ENXIO);
	}

	device_printf(sc->sc_bus.bdev, "trying to attach\n");
	err = device_probe_and_attach(sc->sc_bus.bdev);
	if (err != 0) {
		device_printf(dev, "Failed to initialize USB, with error %d\n", err);
		return (ENXIO);
	}

	return (0);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * bdev; } ;
struct TYPE_6__ {TYPE_4__ sc_bus; int /*<<< orphan*/  sc_vendor; int /*<<< orphan*/ * sc_intr_hdl; int /*<<< orphan*/  sc_io_hdl; int /*<<< orphan*/  sc_io_size; void* sc_io_tag; } ;
struct exynos_xhci_softc {TYPE_1__ base; int /*<<< orphan*/ * res; void* bsh; void* bst; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  driver_intr_t ;
typedef  int /*<<< orphan*/  device_t ;
typedef  void* bus_space_handle_t ;

/* Variables and functions */
 int ENXIO ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_BIO ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_release_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ **) ; 
 int bus_space_subregion (void*,void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 struct exynos_xhci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int device_probe_and_attach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  dwc3_init (struct exynos_xhci_softc*) ; 
 int /*<<< orphan*/  exynos_xhci_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exynos_xhci_spec ; 
 void* rman_get_bushandle (int /*<<< orphan*/ ) ; 
 void* rman_get_bustag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 int xhci_halt_controller (TYPE_1__*) ; 
 scalar_t__ xhci_init (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ xhci_interrupt ; 
 int xhci_start_controller (TYPE_1__*) ; 

__attribute__((used)) static int
exynos_xhci_attach(device_t dev)
{
	struct exynos_xhci_softc *esc = device_get_softc(dev);
	bus_space_handle_t bsh;
	int err;

	esc->dev = dev;

	if (bus_alloc_resources(dev, exynos_xhci_spec, esc->res)) {
		device_printf(dev, "could not allocate resources\n");
		return (ENXIO);
	}

	/* XHCI registers */
	esc->base.sc_io_tag = rman_get_bustag(esc->res[0]);
	bsh = rman_get_bushandle(esc->res[0]);
	esc->base.sc_io_size = rman_get_size(esc->res[0]);

	/* DWC3 ctrl registers */
	esc->bst = rman_get_bustag(esc->res[1]);
	esc->bsh = rman_get_bushandle(esc->res[1]);

	/*
	 * Set handle to USB related registers subregion used by
	 * generic XHCI driver.
	 */
	err = bus_space_subregion(esc->base.sc_io_tag, bsh, 0x0,
	    esc->base.sc_io_size, &esc->base.sc_io_hdl);
	if (err != 0) {
		device_printf(dev, "Subregion failed\n");
		bus_release_resources(dev, exynos_xhci_spec, esc->res);
		return (ENXIO);
	}

	if (xhci_init(&esc->base, dev, 0)) {
		device_printf(dev, "Could not initialize softc\n");
		bus_release_resources(dev, exynos_xhci_spec, esc->res);
		return (ENXIO);
	}

	/* Setup interrupt handler */
	err = bus_setup_intr(dev, esc->res[2], INTR_TYPE_BIO | INTR_MPSAFE,
	    NULL, (driver_intr_t *)xhci_interrupt, &esc->base,
	    &esc->base.sc_intr_hdl);
	if (err) {
		device_printf(dev, "Could not setup irq, %d\n", err);
		esc->base.sc_intr_hdl = NULL;
		goto error;
	}

	/* Add USB device */
	esc->base.sc_bus.bdev = device_add_child(dev, "usbus", -1);
	if (esc->base.sc_bus.bdev == NULL) {
		device_printf(dev, "Could not add USB device\n");
		goto error;
	}
	device_set_ivars(esc->base.sc_bus.bdev, &esc->base.sc_bus);
	strlcpy(esc->base.sc_vendor, "Samsung", sizeof(esc->base.sc_vendor));

	dwc3_init(esc);

	err = xhci_halt_controller(&esc->base);
	if (err == 0) {
		device_printf(dev, "Starting controller\n");
		err = xhci_start_controller(&esc->base);
	}
	if (err == 0) {
		device_printf(dev, "Controller started\n");
		err = device_probe_and_attach(esc->base.sc_bus.bdev);
	}
	if (err != 0)
		goto error;
	return (0);

error:
	exynos_xhci_detach(dev);
	return (ENXIO);
}
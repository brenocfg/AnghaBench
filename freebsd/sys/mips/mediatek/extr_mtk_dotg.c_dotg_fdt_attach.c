#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int dma_bits; int /*<<< orphan*/  bdev; int /*<<< orphan*/  devices_max; int /*<<< orphan*/  devices; int /*<<< orphan*/  parent; } ;
struct dwc_otg_softc {TYPE_1__ sc_bus; int /*<<< orphan*/ * sc_intr_hdl; void* sc_irq_res; void* sc_io_res; int /*<<< orphan*/  sc_io_size; int /*<<< orphan*/  sc_io_hdl; int /*<<< orphan*/  sc_io_tag; int /*<<< orphan*/  sc_devices; int /*<<< orphan*/  sc_mode; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_MODE_HOST ; 
 int /*<<< orphan*/  DWC_OTG_MAX_DEVICES ; 
 int ENOMEM ; 
 int ENXIO ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_TTY ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  USB_GET_DMA_TAG (int /*<<< orphan*/ ) ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dwc_otg_softc*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 struct dwc_otg_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int device_probe_and_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  dotg_fdt_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc_otg_filter_interrupt ; 
 int dwc_otg_init (struct dwc_otg_softc*) ; 
 int /*<<< orphan*/  dwc_otg_interrupt ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  rman_get_bushandle (void*) ; 
 int /*<<< orphan*/  rman_get_bustag (void*) ; 
 int /*<<< orphan*/  rman_get_size (void*) ; 
 scalar_t__ usb_bus_mem_alloc_all (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
dotg_fdt_attach(device_t dev)
{
	struct dwc_otg_softc *sc = device_get_softc(dev);
	int err, rid;

	/* setup controller interface softc */

	/* initialise some bus fields */
	sc->sc_mode = DWC_MODE_HOST;
	sc->sc_bus.parent = dev;
	sc->sc_bus.devices = sc->sc_devices;
	sc->sc_bus.devices_max = DWC_OTG_MAX_DEVICES;
	sc->sc_bus.dma_bits = 32;

	/* get all DMA memory */
	if (usb_bus_mem_alloc_all(&sc->sc_bus,
	    USB_GET_DMA_TAG(dev), NULL)) {
		printf("No mem\n");
		return (ENOMEM);
	}
	rid = 0;
	sc->sc_io_res =
	    bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid, RF_ACTIVE);
	if (!(sc->sc_io_res)) {
		printf("Can`t alloc MEM\n");
		goto error;
	}
	sc->sc_io_tag = rman_get_bustag(sc->sc_io_res);
	sc->sc_io_hdl = rman_get_bushandle(sc->sc_io_res);
	sc->sc_io_size = rman_get_size(sc->sc_io_res);

	rid = 0;
	sc->sc_irq_res = bus_alloc_resource_any(dev, SYS_RES_IRQ, 
	    &rid, RF_ACTIVE);
	if (!(sc->sc_irq_res)) {
		printf("Can`t alloc IRQ\n");
		goto error;
	}

	sc->sc_bus.bdev = device_add_child(dev, "usbus", -1);
	if (!(sc->sc_bus.bdev)) {
		printf("Can`t add usbus\n");
		goto error;
	}
	device_set_ivars(sc->sc_bus.bdev, &sc->sc_bus);

	err = bus_setup_intr(dev, sc->sc_irq_res,
	    INTR_TYPE_TTY | INTR_MPSAFE, dwc_otg_filter_interrupt,
	    dwc_otg_interrupt, sc, &sc->sc_intr_hdl);
	if (err) {
		sc->sc_intr_hdl = NULL;
		printf("Can`t set IRQ handle\n");
		goto error;
	}

	err = dwc_otg_init(sc);
	if (err) printf("dotg_init fail\n");
	if (!err) {
		err = device_probe_and_attach(sc->sc_bus.bdev);
		if (err) printf("device_probe_and_attach fail %d\n", err);
	}
	if (err) {
		goto error;
	}
	return (0);

error:
	dotg_fdt_detach(dev);
	return (ENXIO);
}
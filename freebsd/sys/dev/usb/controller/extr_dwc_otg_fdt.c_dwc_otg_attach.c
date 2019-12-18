#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  usb_mode ;
struct TYPE_4__ {int dma_bits; int /*<<< orphan*/ * bdev; int /*<<< orphan*/  devices_max; int /*<<< orphan*/  devices; int /*<<< orphan*/  parent; } ;
struct TYPE_5__ {TYPE_1__ sc_bus; int /*<<< orphan*/ * sc_intr_hdl; int /*<<< orphan*/ * sc_irq_res; void* sc_io_res; int /*<<< orphan*/  sc_io_size; int /*<<< orphan*/  sc_io_hdl; int /*<<< orphan*/  sc_io_tag; int /*<<< orphan*/  sc_mode; int /*<<< orphan*/  sc_devices; } ;
struct dwc_otg_fdt_softc {TYPE_2__ sc_otg; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_MODE_DEVICE ; 
 int /*<<< orphan*/  DWC_MODE_HOST ; 
 int /*<<< orphan*/  DWC_OTG_MAX_DEVICES ; 
 int ENOMEM ; 
 int ENXIO ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_TTY ; 
 scalar_t__ OF_getprop (int /*<<< orphan*/ ,char*,char**,int) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  USB_GET_DMA_TAG (int /*<<< orphan*/ ) ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct dwc_otg_fdt_softc*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 struct dwc_otg_fdt_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,char*) ; 
 int device_probe_and_attach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  dwc_otg_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc_otg_filter_interrupt ; 
 int dwc_otg_init (TYPE_2__*) ; 
 int /*<<< orphan*/  dwc_otg_interrupt ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 scalar_t__ ofw_bus_is_compatible (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rman_get_bushandle (void*) ; 
 int /*<<< orphan*/  rman_get_bustag (void*) ; 
 int /*<<< orphan*/  rman_get_size (void*) ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 scalar_t__ usb_bus_mem_alloc_all (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
dwc_otg_attach(device_t dev)
{
	struct dwc_otg_fdt_softc *sc = device_get_softc(dev);
	char usb_mode[24];
	int err;
	int rid;

	/* initialise some bus fields */
	sc->sc_otg.sc_bus.parent = dev;
	sc->sc_otg.sc_bus.devices = sc->sc_otg.sc_devices;
	sc->sc_otg.sc_bus.devices_max = DWC_OTG_MAX_DEVICES;
	sc->sc_otg.sc_bus.dma_bits = 32;

	/* get USB mode, if any */
	if (OF_getprop(ofw_bus_get_node(dev), "dr_mode",
	    &usb_mode, sizeof(usb_mode)) > 0) {

		/* ensure proper zero termination */
		usb_mode[sizeof(usb_mode) - 1] = 0;

		if (strcasecmp(usb_mode, "host") == 0)
			sc->sc_otg.sc_mode = DWC_MODE_HOST;
		else if (strcasecmp(usb_mode, "peripheral") == 0)
			sc->sc_otg.sc_mode = DWC_MODE_DEVICE;
		else if (strcasecmp(usb_mode, "otg") != 0) {
			device_printf(dev, "Invalid FDT dr_mode: %s\n",
			    usb_mode);
		}
	}

	/* get all DMA memory */
	if (usb_bus_mem_alloc_all(&sc->sc_otg.sc_bus,
	    USB_GET_DMA_TAG(dev), NULL)) {
		return (ENOMEM);
	}
	rid = 0;
	sc->sc_otg.sc_io_res =
	    bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid, RF_ACTIVE);

	if (!(sc->sc_otg.sc_io_res)) {
		err = ENOMEM;
		goto error;
	}
	sc->sc_otg.sc_io_tag = rman_get_bustag(sc->sc_otg.sc_io_res);
	sc->sc_otg.sc_io_hdl = rman_get_bushandle(sc->sc_otg.sc_io_res);
	sc->sc_otg.sc_io_size = rman_get_size(sc->sc_otg.sc_io_res);


	/*
	 * brcm,bcm2708-usb FDT provides two interrupts,
	 * we need only second one (VC_USB)
	 */
	rid = ofw_bus_is_compatible(dev, "brcm,bcm2708-usb") ? 1 : 0;
	sc->sc_otg.sc_irq_res =
	    bus_alloc_resource_any(dev, SYS_RES_IRQ, &rid, RF_ACTIVE);
	if (sc->sc_otg.sc_irq_res == NULL)
		goto error;

	sc->sc_otg.sc_bus.bdev = device_add_child(dev, "usbus", -1);
	if (sc->sc_otg.sc_bus.bdev == NULL)
		goto error;

	device_set_ivars(sc->sc_otg.sc_bus.bdev, &sc->sc_otg.sc_bus);

	err = bus_setup_intr(dev, sc->sc_otg.sc_irq_res, INTR_TYPE_TTY | INTR_MPSAFE,
	    &dwc_otg_filter_interrupt, &dwc_otg_interrupt, sc, &sc->sc_otg.sc_intr_hdl);
	if (err) {
		sc->sc_otg.sc_intr_hdl = NULL;
		goto error;
	}
	err = dwc_otg_init(&sc->sc_otg);
	if (err == 0) {
		err = device_probe_and_attach(sc->sc_otg.sc_bus.bdev);
	}
	if (err)
		goto error;


	return (0);

error:
	dwc_otg_detach(dev);
	return (ENXIO);
}
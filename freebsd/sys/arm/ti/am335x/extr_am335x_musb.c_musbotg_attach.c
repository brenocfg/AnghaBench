#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_5__ {int dma_bits; int /*<<< orphan*/  bdev; int /*<<< orphan*/  devices_max; int /*<<< orphan*/  devices; int /*<<< orphan*/  parent; } ;
struct TYPE_6__ {scalar_t__ sc_id; scalar_t__ sc_mode; TYPE_1__ sc_bus; struct musbotg_super_softc* sc_platform_data; int /*<<< orphan*/ * sc_intr_hdl; int /*<<< orphan*/ * sc_irq_res; int /*<<< orphan*/  sc_io_res; int /*<<< orphan*/  sc_io_size; int /*<<< orphan*/  sc_io_hdl; int /*<<< orphan*/  sc_io_tag; int /*<<< orphan*/  sc_devices; int /*<<< orphan*/  sc_ep_int_set; struct TYPE_6__* sc_clocks_arg; int /*<<< orphan*/ * sc_clocks_off; int /*<<< orphan*/ * sc_clocks_on; } ;
struct musbotg_super_softc {TYPE_2__ sc_otg; int /*<<< orphan*/ * sc_mem_res; int /*<<< orphan*/  sc_irq_rid; } ;
typedef  int /*<<< orphan*/  mode ;
typedef  int /*<<< orphan*/  driver_intr_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_BIO ; 
 void* MUSB2_DEVICE_MODE ; 
 scalar_t__ MUSB2_HOST_MODE ; 
 int /*<<< orphan*/  MUSB2_MAX_DEVICES ; 
 scalar_t__ OF_getprop (int /*<<< orphan*/ ,char*,char*,int) ; 
 size_t RES_USBCORE ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  USBCTRL_INTEN_CLR0 ; 
 int /*<<< orphan*/  USBCTRL_INTEN_SET1 ; 
 int USBCTRL_INTEN_USB_ALL ; 
 int USBCTRL_INTEN_USB_SOF ; 
 int /*<<< orphan*/  USBCTRL_MODE ; 
 int USBCTRL_MODE_IDDIG ; 
 int USBCTRL_MODE_IDDIGMUX ; 
 int USBCTRL_READ4 (struct musbotg_super_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBCTRL_UTMI ; 
 int USBCTRL_UTMI_FSDATAEXT ; 
 int /*<<< orphan*/  USBCTRL_WRITE4 (struct musbotg_super_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  USB_GET_DMA_TAG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  am335x_musbotg_mem_spec ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 struct musbotg_super_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int device_probe_and_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  musbotg_clocks_off ; 
 int /*<<< orphan*/  musbotg_clocks_on ; 
 int /*<<< orphan*/  musbotg_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  musbotg_ep_int_set ; 
 int musbotg_init (TYPE_2__*) ; 
 int /*<<< orphan*/  musbotg_vbus_poll (struct musbotg_super_softc*) ; 
 scalar_t__ musbotg_wrapper_interrupt ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_size (int /*<<< orphan*/ ) ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 scalar_t__ usb_bus_mem_alloc_all (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
musbotg_attach(device_t dev)
{
	struct musbotg_super_softc *sc = device_get_softc(dev);
	char mode[16];
	int err;
	uint32_t reg;

	sc->sc_otg.sc_id = device_get_unit(dev);

	/* Request the memory resources */
	err = bus_alloc_resources(dev, am335x_musbotg_mem_spec,
		sc->sc_mem_res);
	if (err) {
		device_printf(dev,
		    "Error: could not allocate mem resources\n");
		return (ENXIO);
	}

	/* Request the IRQ resources */
	sc->sc_otg.sc_irq_res = bus_alloc_resource_any(dev, SYS_RES_IRQ,
	    &sc->sc_irq_rid, RF_ACTIVE);
	if (sc->sc_otg.sc_irq_res == NULL) {
		device_printf(dev,
		    "Error: could not allocate irq resources\n");
		return (ENXIO);
	}

	/* setup MUSB OTG USB controller interface softc */
	sc->sc_otg.sc_clocks_on = &musbotg_clocks_on;
	sc->sc_otg.sc_clocks_off = &musbotg_clocks_off;
	sc->sc_otg.sc_clocks_arg = &sc->sc_otg;

	sc->sc_otg.sc_ep_int_set = musbotg_ep_int_set;

	/* initialise some bus fields */
	sc->sc_otg.sc_bus.parent = dev;
	sc->sc_otg.sc_bus.devices = sc->sc_otg.sc_devices;
	sc->sc_otg.sc_bus.devices_max = MUSB2_MAX_DEVICES;
	sc->sc_otg.sc_bus.dma_bits = 32;

	/* get all DMA memory */
	if (usb_bus_mem_alloc_all(&sc->sc_otg.sc_bus,
	    USB_GET_DMA_TAG(dev), NULL)) {
		device_printf(dev,
		    "Failed allocate bus mem for musb\n");
		return (ENOMEM);
	}
	sc->sc_otg.sc_io_res = sc->sc_mem_res[RES_USBCORE];
	sc->sc_otg.sc_io_tag =
	    rman_get_bustag(sc->sc_otg.sc_io_res);
	sc->sc_otg.sc_io_hdl =
	    rman_get_bushandle(sc->sc_otg.sc_io_res);
	sc->sc_otg.sc_io_size =
	    rman_get_size(sc->sc_otg.sc_io_res);

	sc->sc_otg.sc_bus.bdev = device_add_child(dev, "usbus", -1);
	if (!(sc->sc_otg.sc_bus.bdev)) {
		device_printf(dev, "No busdev for musb\n");
		goto error;
	}
	device_set_ivars(sc->sc_otg.sc_bus.bdev,
	    &sc->sc_otg.sc_bus);

	err = bus_setup_intr(dev, sc->sc_otg.sc_irq_res,
	    INTR_TYPE_BIO | INTR_MPSAFE,
	    NULL, (driver_intr_t *)musbotg_wrapper_interrupt,
	    &sc->sc_otg, &sc->sc_otg.sc_intr_hdl);
	if (err) {
		sc->sc_otg.sc_intr_hdl = NULL;
		device_printf(dev,
		    "Failed to setup interrupt for musb\n");
		goto error;
	}

	sc->sc_otg.sc_platform_data = sc;
	if (OF_getprop(ofw_bus_get_node(dev), "dr_mode", mode,
	    sizeof(mode)) > 0) {
		if (strcasecmp(mode, "host") == 0)
			sc->sc_otg.sc_mode = MUSB2_HOST_MODE;
		else
			sc->sc_otg.sc_mode = MUSB2_DEVICE_MODE;
	} else {
		/* Beaglebone defaults: USB0 device, USB1 HOST. */
		if (sc->sc_otg.sc_id == 0)
			sc->sc_otg.sc_mode = MUSB2_DEVICE_MODE;
		else
			sc->sc_otg.sc_mode = MUSB2_HOST_MODE;
	}

	/*
	 * software-controlled function
	 */

	if (sc->sc_otg.sc_mode == MUSB2_HOST_MODE) {
		reg = USBCTRL_READ4(sc, USBCTRL_MODE);
		reg |= USBCTRL_MODE_IDDIGMUX;
		reg &= ~USBCTRL_MODE_IDDIG;
		USBCTRL_WRITE4(sc, USBCTRL_MODE, reg);
		USBCTRL_WRITE4(sc, USBCTRL_UTMI,
		    USBCTRL_UTMI_FSDATAEXT);
	} else {
		reg = USBCTRL_READ4(sc, USBCTRL_MODE);
		reg |= USBCTRL_MODE_IDDIGMUX;
		reg |= USBCTRL_MODE_IDDIG;
		USBCTRL_WRITE4(sc, USBCTRL_MODE, reg);
	}

	reg = USBCTRL_INTEN_USB_ALL & ~USBCTRL_INTEN_USB_SOF;
	USBCTRL_WRITE4(sc, USBCTRL_INTEN_SET1, reg);
	USBCTRL_WRITE4(sc, USBCTRL_INTEN_CLR0, 0xffffffff);

	err = musbotg_init(&sc->sc_otg);
	if (!err)
		err = device_probe_and_attach(sc->sc_otg.sc_bus.bdev);

	if (err)
		goto error;

	/* poll VBUS one time */
	musbotg_vbus_poll(sc);

	return (0);

error:
	musbotg_detach(dev);
	return (ENXIO);
}
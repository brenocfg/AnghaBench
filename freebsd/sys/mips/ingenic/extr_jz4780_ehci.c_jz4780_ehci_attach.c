#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_9__ {int dma_bits; int /*<<< orphan*/  bdev; int /*<<< orphan*/  usbrev; int /*<<< orphan*/  devices_max; int /*<<< orphan*/  devices; int /*<<< orphan*/  parent; } ;
struct TYPE_8__ {TYPE_2__ sc_bus; int /*<<< orphan*/ * sc_intr_hdl; int /*<<< orphan*/ * sc_irq_res; int /*<<< orphan*/  sc_vendor; void* sc_io_res; int /*<<< orphan*/  sc_io_size; int /*<<< orphan*/  sc_io_hdl; int /*<<< orphan*/  sc_io_tag; int /*<<< orphan*/  sc_devices; } ;
struct jz4780_ehci_softc {TYPE_1__ base; } ;
typedef  TYPE_1__ ehci_softc_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  EHCI_HC_DEVSTR ; 
 int /*<<< orphan*/  EHCI_MAX_DEVICES ; 
 int /*<<< orphan*/  EHCI_USBINTR ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  EREAD4 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EWRITE4 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_BIO ; 
 int /*<<< orphan*/  JZ_EHCI_REG_UTMI_BUS ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  USB_GET_DMA_TAG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_REV_2_0 ; 
 int /*<<< orphan*/  UTMI_BUS_WIDTH ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 struct jz4780_ehci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int device_probe_and_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int ehci_init (TYPE_1__*) ; 
 int /*<<< orphan*/  ehci_iterate_hw_softc ; 
 int jz4780_ehci_clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jz4780_ehci_detach (int /*<<< orphan*/ ) ; 
 scalar_t__ jz4780_ehci_enable () ; 
 int /*<<< orphan*/  jz4780_ehci_intr ; 
 int jz4780_ehci_vbus_gpio_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bushandle (void*) ; 
 int /*<<< orphan*/  rman_get_bustag (void*) ; 
 int /*<<< orphan*/  rman_get_size (void*) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ usb_bus_mem_alloc_all (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
jz4780_ehci_attach(device_t dev)
{
	struct jz4780_ehci_softc *isc;
	ehci_softc_t *sc;
	int err;
	int rid;
	uint32_t reg;

	isc = device_get_softc(dev);
	sc = &isc->base;

	/* initialise some bus fields */
	sc->sc_bus.parent = dev;
	sc->sc_bus.devices = sc->sc_devices;
	sc->sc_bus.devices_max = EHCI_MAX_DEVICES;
	sc->sc_bus.dma_bits = 32;

	/* get all DMA memory */
	if (usb_bus_mem_alloc_all(&sc->sc_bus,
	    USB_GET_DMA_TAG(dev), &ehci_iterate_hw_softc)) {
		return (ENOMEM);
	}

	sc->sc_bus.usbrev = USB_REV_2_0;

	err = jz4780_ehci_vbus_gpio_enable(dev);
	if (err)
		goto error;

	rid = 0;
	sc->sc_io_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid, RF_ACTIVE);
	if (!sc->sc_io_res) {
		device_printf(dev, "Could not map memory\n");
		goto error;
	}

	/*
	 * Craft special resource for bus space ops that handle
	 * byte-alignment of non-word addresses.
	 */
	sc->sc_io_tag = rman_get_bustag(sc->sc_io_res);
	sc->sc_io_hdl = rman_get_bushandle(sc->sc_io_res);
	sc->sc_io_size = rman_get_size(sc->sc_io_res);

	err = jz4780_ehci_clk_enable(dev);
	if (err)
		goto error;

	if (jz4780_ehci_enable() != 0) {
		device_printf(dev, "CGU failed to enable EHCI\n");
		err = ENXIO;
		goto error;
	}

	EWRITE4(sc, EHCI_USBINTR, 0);

	rid = 0;
	sc->sc_irq_res = bus_alloc_resource_any(dev, SYS_RES_IRQ, &rid,
	    RF_ACTIVE | RF_SHAREABLE);
	if (sc->sc_irq_res == NULL) {
		device_printf(dev, "Could not allocate irq\n");
		goto error;
	}
	sc->sc_bus.bdev = device_add_child(dev, "usbus", -1);
	if (!sc->sc_bus.bdev) {
		device_printf(dev, "Could not add USB device\n");
		goto error;
	}
	device_set_ivars(sc->sc_bus.bdev, &sc->sc_bus);
	device_set_desc(sc->sc_bus.bdev, EHCI_HC_DEVSTR);

	sprintf(sc->sc_vendor, "Ingenic");

	err = bus_setup_intr(dev, sc->sc_irq_res, INTR_TYPE_BIO | INTR_MPSAFE,
	    NULL, jz4780_ehci_intr, sc, &sc->sc_intr_hdl);
	if (err) {
		device_printf(dev, "Could not setup irq, %d\n", err);
		sc->sc_intr_hdl = NULL;
		goto error;
	}

	err = ehci_init(sc);
	if (!err) {
		/* Voodoo: set utmi data bus width on controller to 16 bit */
		reg = EREAD4(sc, JZ_EHCI_REG_UTMI_BUS);
		reg |= UTMI_BUS_WIDTH;
		EWRITE4(sc, JZ_EHCI_REG_UTMI_BUS, reg);

		err = device_probe_and_attach(sc->sc_bus.bdev);
	}
	if (err) {
		device_printf(dev, "USB init failed err=%d\n", err);
		goto error;
	}
	return (0);

error:
	jz4780_ehci_detach(dev);
	return (ENXIO);
}
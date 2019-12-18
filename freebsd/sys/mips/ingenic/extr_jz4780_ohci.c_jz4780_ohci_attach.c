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
struct TYPE_4__ {int dma_bits; int /*<<< orphan*/ * bdev; int /*<<< orphan*/  devices_max; int /*<<< orphan*/  devices; void* parent; } ;
struct TYPE_5__ {TYPE_1__ sc_bus; int /*<<< orphan*/  sc_io_hdl; int /*<<< orphan*/  sc_io_tag; int /*<<< orphan*/  sc_vendor; int /*<<< orphan*/  sc_intr_hdl; int /*<<< orphan*/ * sc_irq_res; int /*<<< orphan*/ * sc_io_res; int /*<<< orphan*/  sc_io_size; void* sc_dev; int /*<<< orphan*/  sc_devices; } ;
struct jz4780_ohci_softc {TYPE_2__ sc_ohci; } ;
typedef  int /*<<< orphan*/  driver_intr_t ;
typedef  void* device_t ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_BIO ; 
 int /*<<< orphan*/  OHCI_CONTROL ; 
 int /*<<< orphan*/  OHCI_MAX_DEVICES ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  USB_GET_DMA_TAG (void*) ; 
 void* bus_alloc_resource_any (void*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int bus_setup_intr (void*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct jz4780_ohci_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_space_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * device_add_child (void*,char*,int) ; 
 struct jz4780_ohci_softc* device_get_softc (void*) ; 
 int /*<<< orphan*/  device_printf (void*,char*) ; 
 int device_probe_and_attach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int jz4780_ohci_clk_enable (void*) ; 
 int /*<<< orphan*/  jz4780_ohci_detach (void*) ; 
 scalar_t__ jz4780_ohci_enable () ; 
 int jz4780_ohci_vbus_gpio_enable (void*,struct jz4780_ohci_softc*) ; 
 int ohci_init (TYPE_2__*) ; 
 scalar_t__ ohci_interrupt ; 
 int /*<<< orphan*/  ohci_iterate_hw_softc ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ usb_bus_mem_alloc_all (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
jz4780_ohci_attach(device_t dev)
{
	struct jz4780_ohci_softc *sc = device_get_softc(dev);
	int err;
	int rid;

	/* initialize some bus fields */
	sc->sc_ohci.sc_bus.parent = dev;
	sc->sc_ohci.sc_bus.devices = sc->sc_ohci.sc_devices;
	sc->sc_ohci.sc_bus.devices_max = OHCI_MAX_DEVICES;
	sc->sc_ohci.sc_bus.dma_bits = 32;

	/* get all DMA memory */
	if (usb_bus_mem_alloc_all(&sc->sc_ohci.sc_bus,
	    USB_GET_DMA_TAG(dev), &ohci_iterate_hw_softc)) {
		return (ENOMEM);
	}

	sc->sc_ohci.sc_dev = dev;

	/* frob vbus gpio */
	err = jz4780_ohci_vbus_gpio_enable(dev, sc);
	if (err)
		goto error;

	err = jz4780_ohci_clk_enable(dev);
	if (err)
		goto error;

	rid = 0;
	sc->sc_ohci.sc_io_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid,
	    RF_ACTIVE);
	if (sc->sc_ohci.sc_io_res == NULL) {
		err = ENOMEM;
		goto error;
	}
	sc->sc_ohci.sc_io_tag = rman_get_bustag(sc->sc_ohci.sc_io_res);
	sc->sc_ohci.sc_io_hdl = rman_get_bushandle(sc->sc_ohci.sc_io_res);
	sc->sc_ohci.sc_io_size = rman_get_size(sc->sc_ohci.sc_io_res);

	rid = 0;
	sc->sc_ohci.sc_irq_res = bus_alloc_resource_any(dev, SYS_RES_IRQ, &rid,
	    RF_ACTIVE);
	if (sc->sc_ohci.sc_irq_res == NULL) {
		err = ENOMEM;
		goto error;
	}

	if (jz4780_ohci_enable() != 0) {
		device_printf(dev, "CGU failed to enable OHCI\n");
		err = ENXIO;
		goto error;
	}

	sc->sc_ohci.sc_bus.bdev = device_add_child(dev, "usbus", -1);
	if (sc->sc_ohci.sc_bus.bdev == NULL) {
		err = ENOMEM;
		goto error;
	}
	device_set_ivars(sc->sc_ohci.sc_bus.bdev, &sc->sc_ohci.sc_bus);

	err = bus_setup_intr(dev, sc->sc_ohci.sc_irq_res,
	    INTR_TYPE_BIO | INTR_MPSAFE, NULL,
	    (driver_intr_t *)ohci_interrupt, sc, &sc->sc_ohci.sc_intr_hdl);
	if (err) {
		err = ENXIO;
		goto error;
	}

	strlcpy(sc->sc_ohci.sc_vendor, "Ingenic", sizeof(sc->sc_ohci.sc_vendor));
	bus_space_write_4(sc->sc_ohci.sc_io_tag, sc->sc_ohci.sc_io_hdl, OHCI_CONTROL, 0);

	err = ohci_init(&sc->sc_ohci);
	if (!err)
		err = device_probe_and_attach(sc->sc_ohci.sc_bus.bdev);

	if (err)
		goto error;
	return (0);

error:
	if (err)
		jz4780_ohci_detach(dev);
	return (err);
}
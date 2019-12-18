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
struct TYPE_3__ {int dma_bits; int /*<<< orphan*/ * bdev; int /*<<< orphan*/  devices_max; int /*<<< orphan*/  devices; int /*<<< orphan*/  parent; } ;
struct saf1761_otg_softc {TYPE_1__ sc_bus; int /*<<< orphan*/ * sc_intr_hdl; int /*<<< orphan*/ * sc_irq_res; int /*<<< orphan*/ * sc_io_res; int /*<<< orphan*/  sc_io_size; int /*<<< orphan*/  sc_io_hdl; int /*<<< orphan*/  sc_io_tag; int /*<<< orphan*/  sc_devices; int /*<<< orphan*/  sc_hw_mode; int /*<<< orphan*/  sc_interrupt_cfg; } ;
typedef  int /*<<< orphan*/  param ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_TTY ; 
 scalar_t__ OF_getprop (int /*<<< orphan*/ ,char*,char**,int) ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SOTG_HW_MODE_CTRL_ANA_DIGI_OC ; 
 int /*<<< orphan*/  SOTG_HW_MODE_CTRL_DACK_POL ; 
 int /*<<< orphan*/  SOTG_HW_MODE_CTRL_DATA_BUS_WIDTH ; 
 int /*<<< orphan*/  SOTG_HW_MODE_CTRL_DREQ_POL ; 
 int /*<<< orphan*/  SOTG_HW_MODE_CTRL_INTR_LEVEL ; 
 int /*<<< orphan*/  SOTG_HW_MODE_CTRL_INTR_POL ; 
 int /*<<< orphan*/  SOTG_INTERRUPT_CFG_INTLVL ; 
 int /*<<< orphan*/  SOTG_INTERRUPT_CFG_INTPOL ; 
 int /*<<< orphan*/  SOTG_MAX_DEVICES ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  USB_GET_DMA_TAG (int /*<<< orphan*/ ) ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct saf1761_otg_softc*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 struct saf1761_otg_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int device_probe_and_attach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  saf1761_otg_fdt_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saf1761_otg_filter_interrupt ; 
 int saf1761_otg_init (struct saf1761_otg_softc*) ; 
 int /*<<< orphan*/  saf1761_otg_interrupt ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ usb_bus_mem_alloc_all (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
saf1761_otg_fdt_attach(device_t dev)
{
	struct saf1761_otg_softc *sc = device_get_softc(dev);
	char param[24];
	int err;
	int rid;

	/* get configuration from FDT */

	/* get bus-width, if any */
	if (OF_getprop(ofw_bus_get_node(dev), "bus-width",
	    &param, sizeof(param)) > 0) {
		param[sizeof(param) - 1] = 0;
		if (strcmp(param, "32") == 0)
			sc->sc_hw_mode |= SOTG_HW_MODE_CTRL_DATA_BUS_WIDTH;
	} else {
		/* assume 32-bit data bus */
		sc->sc_hw_mode |= SOTG_HW_MODE_CTRL_DATA_BUS_WIDTH;
	}

	/* get analog over-current setting */
	if (OF_getprop(ofw_bus_get_node(dev), "analog-oc",
	    &param, sizeof(param)) > 0) {
		sc->sc_hw_mode |= SOTG_HW_MODE_CTRL_ANA_DIGI_OC;
	}

	/* get DACK polarity */
	if (OF_getprop(ofw_bus_get_node(dev), "dack-polarity",
	    &param, sizeof(param)) > 0) {
		sc->sc_hw_mode |= SOTG_HW_MODE_CTRL_DACK_POL;
	}

	/* get DREQ polarity */
	if (OF_getprop(ofw_bus_get_node(dev), "dreq-polarity",
	    &param, sizeof(param)) > 0) {
		sc->sc_hw_mode |= SOTG_HW_MODE_CTRL_DREQ_POL;
	}

	/* get IRQ polarity */
	if (OF_getprop(ofw_bus_get_node(dev), "int-polarity",
	    &param, sizeof(param)) > 0) {
		sc->sc_interrupt_cfg |= SOTG_INTERRUPT_CFG_INTPOL;
		sc->sc_hw_mode |= SOTG_HW_MODE_CTRL_INTR_POL;
	}

	/* get IRQ level triggering */
	if (OF_getprop(ofw_bus_get_node(dev), "int-level",
	    &param, sizeof(param)) > 0) {
		sc->sc_interrupt_cfg |= SOTG_INTERRUPT_CFG_INTLVL;
		sc->sc_hw_mode |= SOTG_HW_MODE_CTRL_INTR_LEVEL;
	}

	/* initialise some bus fields */
	sc->sc_bus.parent = dev;
	sc->sc_bus.devices = sc->sc_devices;
	sc->sc_bus.devices_max = SOTG_MAX_DEVICES;
	sc->sc_bus.dma_bits = 32;

	/* get all DMA memory */
	if (usb_bus_mem_alloc_all(&sc->sc_bus,
	    USB_GET_DMA_TAG(dev), NULL)) {
		return (ENOMEM);
	}
	rid = 0;
	sc->sc_io_res =
	    bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid, RF_ACTIVE);

	if (sc->sc_io_res == NULL) 
		goto error;

	sc->sc_io_tag = rman_get_bustag(sc->sc_io_res);
	sc->sc_io_hdl = rman_get_bushandle(sc->sc_io_res);
	sc->sc_io_size = rman_get_size(sc->sc_io_res);

	/* try to allocate the HC interrupt first */
	rid = 1;
	sc->sc_irq_res = bus_alloc_resource_any(dev, SYS_RES_IRQ, &rid,
	    RF_SHAREABLE | RF_ACTIVE);
	if (sc->sc_irq_res == NULL) {
		/* try to allocate a common IRQ second */
		rid = 0;
		sc->sc_irq_res = bus_alloc_resource_any(dev, SYS_RES_IRQ, &rid,
		    RF_SHAREABLE | RF_ACTIVE);
		if (sc->sc_irq_res == NULL)
			goto error;
	}

	sc->sc_bus.bdev = device_add_child(dev, "usbus", -1);
	if (sc->sc_bus.bdev == NULL)
		goto error;

	device_set_ivars(sc->sc_bus.bdev, &sc->sc_bus);

	err = bus_setup_intr(dev, sc->sc_irq_res, INTR_TYPE_TTY | INTR_MPSAFE,
	    &saf1761_otg_filter_interrupt, &saf1761_otg_interrupt, sc, &sc->sc_intr_hdl);
	if (err) {
		sc->sc_intr_hdl = NULL;
		goto error;
	}
	err = saf1761_otg_init(sc);
	if (err) {
		device_printf(dev, "Init failed\n");
		goto error;
	}
	err = device_probe_and_attach(sc->sc_bus.bdev);
	if (err) {
		device_printf(dev, "USB probe and attach failed\n");
		goto error;
	}
	return (0);

error:
	saf1761_otg_fdt_detach(dev);
	return (ENXIO);
}
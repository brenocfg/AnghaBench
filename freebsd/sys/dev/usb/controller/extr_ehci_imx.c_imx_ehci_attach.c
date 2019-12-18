#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int dma_bits; int /*<<< orphan*/ * bdev; int /*<<< orphan*/  devices_max; int /*<<< orphan*/  devices; void* parent; } ;
struct TYPE_6__ {int sc_flags; TYPE_2__ sc_bus; int /*<<< orphan*/  sc_vendor_get_port_speed; int /*<<< orphan*/  sc_vendor_post_reset; int /*<<< orphan*/  sc_vendor; int /*<<< orphan*/  sc_id_vendor; int /*<<< orphan*/  sc_intr_hdl; int /*<<< orphan*/  sc_io_hdl; int /*<<< orphan*/  sc_io_tag; int /*<<< orphan*/  sc_devices; } ;
struct imx_ehci_softc {void* dev; int /*<<< orphan*/ * ehci_irq_res; int /*<<< orphan*/ * ehci_mem_res; TYPE_1__ ehci_softc; } ;
typedef  TYPE_1__ ehci_softc_t ;
typedef  int /*<<< orphan*/  driver_intr_t ;
typedef  void* device_t ;

/* Variables and functions */
 int /*<<< orphan*/  EHCI_MAX_DEVICES ; 
 int EHCI_SCFLG_DONEINIT ; 
 int EHCI_SCFLG_NORESTERM ; 
 int EHCI_SCFLG_TT ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  IMX_EHCI_REG_OFF ; 
 int /*<<< orphan*/  IMX_EHCI_REG_SIZE ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_BIO ; 
 scalar_t__ OF_hasprop (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  USB_GET_DMA_TAG (void*) ; 
 int /*<<< orphan*/  USB_VENDOR_FREESCALE ; 
 void* bus_alloc_resource_any (void*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int bus_setup_intr (void*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int bus_space_subregion (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * device_add_child (void*,char*,int) ; 
 struct imx_ehci_softc* device_get_softc (void*) ; 
 int /*<<< orphan*/  device_printf (void*,char*,...) ; 
 int device_probe_and_attach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  ehci_get_port_speed_portsc ; 
 int ehci_init (TYPE_1__*) ; 
 scalar_t__ ehci_interrupt ; 
 int /*<<< orphan*/  ehci_iterate_hw_softc ; 
 int /*<<< orphan*/  imx_ccm_usb_enable (void*) ; 
 int /*<<< orphan*/  imx_ehci_detach (void*) ; 
 int /*<<< orphan*/  imx_ehci_disable_oc (struct imx_ehci_softc*) ; 
 int /*<<< orphan*/  imx_ehci_post_reset ; 
 int /*<<< orphan*/  ofw_bus_get_node (void*) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ usb_bus_mem_alloc_all (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
imx_ehci_attach(device_t dev)
{
	struct imx_ehci_softc *sc;
	ehci_softc_t *esc;
	int err, rid;

	sc = device_get_softc(dev);
	sc->dev = dev;
	esc = &sc->ehci_softc;
	err = 0;

	/* Allocate bus_space resources. */
	rid = 0;
	sc->ehci_mem_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid,
	    RF_ACTIVE);
	if (sc->ehci_mem_res == NULL) {
		device_printf(dev, "Cannot allocate memory resources\n");
		err = ENXIO;
		goto out;
	}

	rid = 0;
	sc->ehci_irq_res = bus_alloc_resource_any(dev, SYS_RES_IRQ, &rid,
	    RF_ACTIVE);
	if (sc->ehci_irq_res == NULL) {
		device_printf(dev, "Cannot allocate IRQ resources\n");
		err = ENXIO;
		goto out;
	}

	esc->sc_io_tag = rman_get_bustag(sc->ehci_mem_res);
	esc->sc_bus.parent = dev;
	esc->sc_bus.devices = esc->sc_devices;
	esc->sc_bus.devices_max = EHCI_MAX_DEVICES;
	esc->sc_bus.dma_bits = 32;

	/* allocate all DMA memory */
	if (usb_bus_mem_alloc_all(&esc->sc_bus, USB_GET_DMA_TAG(dev),
	    &ehci_iterate_hw_softc) != 0) {
		device_printf(dev, "usb_bus_mem_alloc_all() failed\n");
		err = ENOMEM;
		goto out;
	}

	/*
	 * Set handle to USB related registers subregion used by
	 * generic EHCI driver.
	 */
	err = bus_space_subregion(esc->sc_io_tag, 
	    rman_get_bushandle(sc->ehci_mem_res),
	    IMX_EHCI_REG_OFF, IMX_EHCI_REG_SIZE, &esc->sc_io_hdl);
	if (err != 0) {
		device_printf(dev, "bus_space_subregion() failed\n");
		err = ENXIO;
		goto out;
	}

	/* Setup interrupt handler. */
	err = bus_setup_intr(dev, sc->ehci_irq_res, INTR_TYPE_BIO | INTR_MPSAFE,
	    NULL, (driver_intr_t *)ehci_interrupt, esc, &esc->sc_intr_hdl);
	if (err != 0) {
		device_printf(dev, "Could not setup IRQ\n");
		goto out;
	}

	/* Turn on clocks. */
	imx_ccm_usb_enable(dev);

	/* Disable overcurrent detection, if configured to do so. */
	if (OF_hasprop(ofw_bus_get_node(sc->dev), "disable-over-current"))
		imx_ehci_disable_oc(sc);

	/* Add USB bus device. */
	esc->sc_bus.bdev = device_add_child(dev, "usbus", -1);
	if (esc->sc_bus.bdev == NULL) {
		device_printf(dev, "Could not add USB device\n");
		goto out;
	}
	device_set_ivars(esc->sc_bus.bdev, &esc->sc_bus);

	esc->sc_id_vendor = USB_VENDOR_FREESCALE;
	strlcpy(esc->sc_vendor, "Freescale", sizeof(esc->sc_vendor));

	/*
	 * Set flags that affect ehci_init() behavior, and hook our post-reset
	 * code into the standard controller code.
	 */
	esc->sc_flags |= EHCI_SCFLG_NORESTERM | EHCI_SCFLG_TT;
	esc->sc_vendor_post_reset = imx_ehci_post_reset;
	esc->sc_vendor_get_port_speed = ehci_get_port_speed_portsc;

	err = ehci_init(esc);
	if (err != 0) {
		device_printf(dev, "USB init failed, usb_err_t=%d\n", 
		    err);
		goto out;
	}
	esc->sc_flags |= EHCI_SCFLG_DONEINIT;

	/* Probe the bus. */
	err = device_probe_and_attach(esc->sc_bus.bdev);
	if (err != 0) {
		device_printf(dev,
		    "device_probe_and_attach() failed\n");
		goto out;
	}

	err = 0;

out:

	if (err != 0)
		imx_ehci_detach(dev);

	return (err);
}
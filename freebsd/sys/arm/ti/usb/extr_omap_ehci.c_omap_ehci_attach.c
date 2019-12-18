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
struct TYPE_7__ {int dma_bits; int /*<<< orphan*/  bdev; int /*<<< orphan*/  devices_max; int /*<<< orphan*/  devices; void* parent; } ;
struct TYPE_6__ {TYPE_2__ sc_bus; int /*<<< orphan*/ * sc_intr_hdl; int /*<<< orphan*/ * sc_irq_res; void* sc_io_res; int /*<<< orphan*/  sc_io_size; int /*<<< orphan*/  sc_io_tag; int /*<<< orphan*/  sc_io_hdl; int /*<<< orphan*/  sc_vendor; int /*<<< orphan*/  sc_devices; } ;
struct omap_ehci_softc {void* sc_dev; TYPE_1__ base; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  TYPE_1__ ehci_softc_t ;
typedef  int /*<<< orphan*/  driver_intr_t ;
typedef  void* device_t ;

/* Variables and functions */
 int /*<<< orphan*/  EHCI_MAX_DEVICES ; 
 int ENOMEM ; 
 int ENXIO ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_BIO ; 
 int /*<<< orphan*/  OF_finddevice (char*) ; 
 int /*<<< orphan*/  OMAP_EHCI_HC_DEVSTR ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  USB_GET_DMA_TAG (void*) ; 
 void* bus_alloc_resource_any (void*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int bus_setup_intr (void*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  device_add_child (void*,char*,int) ; 
 struct omap_ehci_softc* device_get_softc (void*) ; 
 int /*<<< orphan*/  device_printf (void*,char*,...) ; 
 int device_probe_and_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int ehci_init (TYPE_1__*) ; 
 scalar_t__ ehci_interrupt ; 
 int /*<<< orphan*/  ehci_iterate_hw_softc ; 
 scalar_t__ ofw_bus_node_is_compatible (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  omap_ehci_detach (void*) ; 
 int omap_ehci_init (struct omap_ehci_softc*) ; 
 int /*<<< orphan*/  pandaboard_usb_hub_init () ; 
 int /*<<< orphan*/  rman_get_bushandle (void*) ; 
 int /*<<< orphan*/  rman_get_bustag (void*) ; 
 int /*<<< orphan*/  rman_get_size (void*) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ usb_bus_mem_alloc_all (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
omap_ehci_attach(device_t dev)
{
	struct omap_ehci_softc *isc = device_get_softc(dev);
	ehci_softc_t *sc = &isc->base;
#ifdef SOC_OMAP4
	phandle_t root;
#endif
	int err;
	int rid;

#ifdef SOC_OMAP4
	/* 
	 * If we're running a Pandaboard, run Pandaboard-specific 
	 * init code.
	 */
	root = OF_finddevice("/");
	if (ofw_bus_node_is_compatible(root, "ti,omap4-panda"))
		pandaboard_usb_hub_init();
#endif

	/* initialise some bus fields */
	sc->sc_bus.parent = dev;
	sc->sc_bus.devices = sc->sc_devices;
	sc->sc_bus.devices_max = EHCI_MAX_DEVICES;
	sc->sc_bus.dma_bits = 32;

	sprintf(sc->sc_vendor, "Texas Instruments");

	/* save the device */
	isc->sc_dev = dev;
	
	/* get all DMA memory */
	if (usb_bus_mem_alloc_all(&sc->sc_bus, USB_GET_DMA_TAG(dev),
	                          &ehci_iterate_hw_softc)) {
		return (ENOMEM);
	}
	
	/* Allocate resource for the EHCI register set */
	rid = 0;
	sc->sc_io_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid, RF_ACTIVE);
	if (!sc->sc_io_res) {
		device_printf(dev, "Error: Could not map EHCI memory\n");
		goto error;
	}
	/* Request an interrupt resource */
	rid = 0;
	sc->sc_irq_res = bus_alloc_resource_any(dev, SYS_RES_IRQ, &rid, RF_ACTIVE);
	if (sc->sc_irq_res == NULL) {
		device_printf(dev, "Error: could not allocate irq\n");
		goto error;
	}

	/* Add this device as a child of the USBus device */
	sc->sc_bus.bdev = device_add_child(dev, "usbus", -1);
	if (!sc->sc_bus.bdev) {
		device_printf(dev, "Error: could not add USB device\n");
		goto error;
	}

	device_set_ivars(sc->sc_bus.bdev, &sc->sc_bus);
	device_set_desc(sc->sc_bus.bdev, OMAP_EHCI_HC_DEVSTR);
	
	/* Initialise the ECHI registers */
	err = omap_ehci_init(isc);
	if (err) {
		device_printf(dev, "Error: could not setup OMAP EHCI, %d\n", err);
		goto error;
	}
		
	/* Set the tag and size of the register set in the EHCI context */
	sc->sc_io_hdl = rman_get_bushandle(sc->sc_io_res);
	sc->sc_io_tag = rman_get_bustag(sc->sc_io_res);
	sc->sc_io_size = rman_get_size(sc->sc_io_res);

	/* Setup the interrupt */
	err = bus_setup_intr(dev, sc->sc_irq_res, INTR_TYPE_BIO | INTR_MPSAFE,
						 NULL, (driver_intr_t *)ehci_interrupt, sc, &sc->sc_intr_hdl);
	if (err) {
		device_printf(dev, "Error: could not setup irq, %d\n", err);
		sc->sc_intr_hdl = NULL;
		goto error;
	}
	
	/* Finally we are ready to kick off the ECHI host controller */
	err = ehci_init(sc);
	if (err == 0) {
		err = device_probe_and_attach(sc->sc_bus.bdev);
	}
	if (err) {
		device_printf(dev, "Error: USB init failed err=%d\n", err);
		goto error;
	}
	
	return (0);
	
error:
	omap_ehci_detach(dev);
	return (ENXIO);
}
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
struct TYPE_9__ {int dma_bits; int /*<<< orphan*/  bdev; int /*<<< orphan*/  usbrev; int /*<<< orphan*/  devices_max; int /*<<< orphan*/  devices; void* parent; } ;
struct TYPE_8__ {TYPE_2__ sc_bus; int /*<<< orphan*/ * sc_intr_hdl; int /*<<< orphan*/ * sc_irq_res; int /*<<< orphan*/  sc_vendor; int /*<<< orphan*/  sc_io_hdl; int /*<<< orphan*/  sc_io_tag; void* sc_io_res; int /*<<< orphan*/  sc_io_size; void* sc_dev; int /*<<< orphan*/  sc_devices; } ;
typedef  TYPE_1__ uhci_softc_t ;
typedef  int /*<<< orphan*/  driver_intr_t ;
typedef  void* device_t ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_BIO ; 
 int /*<<< orphan*/  PCI_LEGSUP ; 
 int PCI_LEGSUP_USBPIRQDEN ; 
 int PCI_UHCI_BASE_REG ; 
#define  PCI_UHCI_VENDORID_HP 132 
#define  PCI_UHCI_VENDORID_INTEL 131 
#define  PCI_UHCI_VENDORID_VIA 130 
 int /*<<< orphan*/  PCI_USBREV ; 
#define  PCI_USB_REV_1_0 129 
 int PCI_USB_REV_MASK ; 
#define  PCI_USB_REV_PRE_1_0 128 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  UHCI_INTR ; 
 int /*<<< orphan*/  UHCI_MAX_DEVICES ; 
 int /*<<< orphan*/  USB_GET_DMA_TAG (void*) ; 
 int /*<<< orphan*/  USB_REV_1_0 ; 
 int /*<<< orphan*/  USB_REV_1_1 ; 
 int /*<<< orphan*/  USB_REV_PRE_1_0 ; 
 int /*<<< orphan*/  bootverbose ; 
 void* bus_alloc_resource_any (void*,int /*<<< orphan*/ ,int*,int) ; 
 int bus_setup_intr (void*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*,...) ; 
 int /*<<< orphan*/  bus_space_write_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_add_child (void*,char*,int) ; 
 TYPE_1__* device_get_softc (void*) ; 
 int /*<<< orphan*/  device_printf (void*,char*,...) ; 
 int device_probe_and_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  pci_enable_busmaster (void*) ; 
 int /*<<< orphan*/  pci_get_devid (void*) ; 
 int pci_get_vendor (void*) ; 
 int pci_read_config (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_config (void*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rman_get_bushandle (void*) ; 
 int /*<<< orphan*/  rman_get_bustag (void*) ; 
 int /*<<< orphan*/  rman_get_size (void*) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,...) ; 
 int uhci_init (TYPE_1__*) ; 
 scalar_t__ uhci_interrupt ; 
 int /*<<< orphan*/  uhci_iterate_hw_softc ; 
 int /*<<< orphan*/  uhci_pci_detach (void*) ; 
 int /*<<< orphan*/  uhci_pci_match (void*) ; 
 scalar_t__ usb_bus_mem_alloc_all (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
uhci_pci_attach(device_t self)
{
	uhci_softc_t *sc = device_get_softc(self);
	int rid;
	int err;

	/* initialise some bus fields */
	sc->sc_bus.parent = self;
	sc->sc_bus.devices = sc->sc_devices;
	sc->sc_bus.devices_max = UHCI_MAX_DEVICES;
	sc->sc_bus.dma_bits = 32;

	/* get all DMA memory */
	if (usb_bus_mem_alloc_all(&sc->sc_bus, USB_GET_DMA_TAG(self),
	    &uhci_iterate_hw_softc)) {
		return ENOMEM;
	}
	sc->sc_dev = self;

	pci_enable_busmaster(self);

	rid = PCI_UHCI_BASE_REG;
	sc->sc_io_res = bus_alloc_resource_any(self, SYS_RES_IOPORT, &rid,
	    RF_ACTIVE);
	if (!sc->sc_io_res) {
		device_printf(self, "Could not map ports\n");
		goto error;
	}
	sc->sc_io_tag = rman_get_bustag(sc->sc_io_res);
	sc->sc_io_hdl = rman_get_bushandle(sc->sc_io_res);
	sc->sc_io_size = rman_get_size(sc->sc_io_res);

	/* disable interrupts */
	bus_space_write_2(sc->sc_io_tag, sc->sc_io_hdl, UHCI_INTR, 0);

	rid = 0;
	sc->sc_irq_res = bus_alloc_resource_any(self, SYS_RES_IRQ, &rid,
	    RF_SHAREABLE | RF_ACTIVE);
	if (sc->sc_irq_res == NULL) {
		device_printf(self, "Could not allocate irq\n");
		goto error;
	}
	sc->sc_bus.bdev = device_add_child(self, "usbus", -1);
	if (!sc->sc_bus.bdev) {
		device_printf(self, "Could not add USB device\n");
		goto error;
	}
	device_set_ivars(sc->sc_bus.bdev, &sc->sc_bus);

	/*
	 * uhci_pci_match must never return NULL if uhci_pci_probe
	 * succeeded
	 */
	device_set_desc(sc->sc_bus.bdev, uhci_pci_match(self));
	switch (pci_get_vendor(self)) {
	case PCI_UHCI_VENDORID_INTEL:
		sprintf(sc->sc_vendor, "Intel");
		break;
	case PCI_UHCI_VENDORID_HP:
		sprintf(sc->sc_vendor, "HP");
		break;
	case PCI_UHCI_VENDORID_VIA:
		sprintf(sc->sc_vendor, "VIA");
		break;
	default:
		if (bootverbose) {
			device_printf(self, "(New UHCI DeviceId=0x%08x)\n",
			    pci_get_devid(self));
		}
		sprintf(sc->sc_vendor, "(0x%04x)", pci_get_vendor(self));
	}

	switch (pci_read_config(self, PCI_USBREV, 1) & PCI_USB_REV_MASK) {
	case PCI_USB_REV_PRE_1_0:
		sc->sc_bus.usbrev = USB_REV_PRE_1_0;
		break;
	case PCI_USB_REV_1_0:
		sc->sc_bus.usbrev = USB_REV_1_0;
		break;
	default:
		/* Quirk for Parallels Desktop 4.0 */
		device_printf(self, "USB revision is unknown. Assuming v1.1.\n");
		sc->sc_bus.usbrev = USB_REV_1_1;
		break;
	}

#if (__FreeBSD_version >= 700031)
	err = bus_setup_intr(self, sc->sc_irq_res, INTR_TYPE_BIO | INTR_MPSAFE,
	    NULL, (driver_intr_t *)uhci_interrupt, sc, &sc->sc_intr_hdl);
#else
	err = bus_setup_intr(self, sc->sc_irq_res, INTR_TYPE_BIO | INTR_MPSAFE,
	    (driver_intr_t *)uhci_interrupt, sc, &sc->sc_intr_hdl);
#endif

	if (err) {
		device_printf(self, "Could not setup irq, %d\n", err);
		sc->sc_intr_hdl = NULL;
		goto error;
	}
	/*
	 * Set the PIRQD enable bit and switch off all the others. We don't
	 * want legacy support to interfere with us XXX Does this also mean
	 * that the BIOS won't touch the keyboard anymore if it is connected
	 * to the ports of the root hub?
	 */
#ifdef USB_DEBUG
	if (pci_read_config(self, PCI_LEGSUP, 2) != PCI_LEGSUP_USBPIRQDEN) {
		device_printf(self, "LegSup = 0x%04x\n",
		    pci_read_config(self, PCI_LEGSUP, 2));
	}
#endif
	pci_write_config(self, PCI_LEGSUP, PCI_LEGSUP_USBPIRQDEN, 2);

	err = uhci_init(sc);
	if (!err) {
		err = device_probe_and_attach(sc->sc_bus.bdev);
	}
	if (err) {
		device_printf(self, "USB init failed\n");
		goto error;
	}
	return (0);

error:
	uhci_pci_detach(self);
	return (ENXIO);
}
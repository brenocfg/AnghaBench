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
struct TYPE_9__ {int dma_bits; int /*<<< orphan*/  bdev; int /*<<< orphan*/  devices_max; int /*<<< orphan*/  devices; void* parent; } ;
struct TYPE_8__ {TYPE_2__ sc_bus; int /*<<< orphan*/ * sc_intr_hdl; int /*<<< orphan*/ * sc_irq_res; int /*<<< orphan*/  sc_vendor; void* sc_io_res; int /*<<< orphan*/  sc_io_size; int /*<<< orphan*/  sc_io_hdl; int /*<<< orphan*/  sc_io_tag; void* sc_dev; int /*<<< orphan*/  sc_devices; } ;
typedef  TYPE_1__ ohci_softc_t ;
typedef  int /*<<< orphan*/  driver_intr_t ;
typedef  void* device_t ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_BIO ; 
 int /*<<< orphan*/  OHCI_MAX_DEVICES ; 
 int PCI_CBMEM ; 
#define  PCI_OHCI_VENDORID_ACERLABS 138 
#define  PCI_OHCI_VENDORID_AMD 137 
#define  PCI_OHCI_VENDORID_APPLE 136 
#define  PCI_OHCI_VENDORID_ATI 135 
#define  PCI_OHCI_VENDORID_CMDTECH 134 
#define  PCI_OHCI_VENDORID_NEC 133 
#define  PCI_OHCI_VENDORID_NVIDIA 132 
#define  PCI_OHCI_VENDORID_NVIDIA2 131 
#define  PCI_OHCI_VENDORID_OPTI 130 
#define  PCI_OHCI_VENDORID_SIS 129 
#define  PCI_OHCI_VENDORID_SUN 128 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  USB_GET_DMA_TAG (void*) ; 
 int /*<<< orphan*/  bootverbose ; 
 void* bus_alloc_resource_any (void*,int /*<<< orphan*/ ,int*,int) ; 
 int bus_setup_intr (void*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*,...) ; 
 int /*<<< orphan*/  device_add_child (void*,char*,int) ; 
 TYPE_1__* device_get_softc (void*) ; 
 int /*<<< orphan*/  device_printf (void*,char*,...) ; 
 int device_probe_and_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int ohci_init (TYPE_1__*) ; 
 scalar_t__ ohci_interrupt ; 
 int /*<<< orphan*/  ohci_iterate_hw_softc ; 
 int /*<<< orphan*/  ohci_pci_detach (void*) ; 
 int /*<<< orphan*/  ohci_pci_match (void*) ; 
 int /*<<< orphan*/  pci_enable_busmaster (void*) ; 
 int pci_get_devid (void*) ; 
 scalar_t__ pci_get_intpin (void*) ; 
 int pci_get_vendor (void*) ; 
 int /*<<< orphan*/  pci_set_intpin (void*,int) ; 
 int /*<<< orphan*/  rman_get_bushandle (void*) ; 
 int /*<<< orphan*/  rman_get_bustag (void*) ; 
 int /*<<< orphan*/  rman_get_size (void*) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ usb_bus_mem_alloc_all (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ohci_pci_attach(device_t self)
{
	ohci_softc_t *sc = device_get_softc(self);
	int rid;
	int err;

	/* initialise some bus fields */
	sc->sc_bus.parent = self;
	sc->sc_bus.devices = sc->sc_devices;
	sc->sc_bus.devices_max = OHCI_MAX_DEVICES;
	sc->sc_bus.dma_bits = 32;

	/* get all DMA memory */
	if (usb_bus_mem_alloc_all(&sc->sc_bus, USB_GET_DMA_TAG(self),
	    &ohci_iterate_hw_softc)) {
		return (ENOMEM);
	}
	sc->sc_dev = self;

	pci_enable_busmaster(self);

	/*
	 * Some Sun PCIO-2 USB controllers have their intpin register
	 * bogusly set to 0, although it should be 4.  Correct that.
	 */
	if (pci_get_devid(self) == 0x1103108e && pci_get_intpin(self) == 0)
		pci_set_intpin(self, 4);

	rid = PCI_CBMEM;
	sc->sc_io_res = bus_alloc_resource_any(self, SYS_RES_MEMORY, &rid,
	    RF_ACTIVE);
	if (!sc->sc_io_res) {
		device_printf(self, "Could not map memory\n");
		goto error;
	}
	sc->sc_io_tag = rman_get_bustag(sc->sc_io_res);
	sc->sc_io_hdl = rman_get_bushandle(sc->sc_io_res);
	sc->sc_io_size = rman_get_size(sc->sc_io_res);

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
	 * ohci_pci_match will never return NULL if ohci_pci_probe
	 * succeeded
	 */
	device_set_desc(sc->sc_bus.bdev, ohci_pci_match(self));
	switch (pci_get_vendor(self)) {
	case PCI_OHCI_VENDORID_ACERLABS:
		sprintf(sc->sc_vendor, "AcerLabs");
		break;
	case PCI_OHCI_VENDORID_AMD:
		sprintf(sc->sc_vendor, "AMD");
		break;
	case PCI_OHCI_VENDORID_APPLE:
		sprintf(sc->sc_vendor, "Apple");
		break;
	case PCI_OHCI_VENDORID_ATI:
		sprintf(sc->sc_vendor, "ATI");
		break;
	case PCI_OHCI_VENDORID_CMDTECH:
		sprintf(sc->sc_vendor, "CMDTECH");
		break;
	case PCI_OHCI_VENDORID_NEC:
		sprintf(sc->sc_vendor, "NEC");
		break;
	case PCI_OHCI_VENDORID_NVIDIA:
	case PCI_OHCI_VENDORID_NVIDIA2:
		sprintf(sc->sc_vendor, "nVidia");
		break;
	case PCI_OHCI_VENDORID_OPTI:
		sprintf(sc->sc_vendor, "OPTi");
		break;
	case PCI_OHCI_VENDORID_SIS:
		sprintf(sc->sc_vendor, "SiS");
		break;
	case PCI_OHCI_VENDORID_SUN:
		sprintf(sc->sc_vendor, "SUN");
		break;
	default:
		if (bootverbose) {
			device_printf(self, "(New OHCI DeviceId=0x%08x)\n",
			    pci_get_devid(self));
		}
		sprintf(sc->sc_vendor, "(0x%04x)", pci_get_vendor(self));
	}

	/* sc->sc_bus.usbrev; set by ohci_init() */

#if (__FreeBSD_version >= 700031)
	err = bus_setup_intr(self, sc->sc_irq_res, INTR_TYPE_BIO | INTR_MPSAFE,
	    NULL, (driver_intr_t *)ohci_interrupt, sc, &sc->sc_intr_hdl);
#else
	err = bus_setup_intr(self, sc->sc_irq_res, INTR_TYPE_BIO | INTR_MPSAFE,
	    (driver_intr_t *)ohci_interrupt, sc, &sc->sc_intr_hdl);
#endif
	if (err) {
		device_printf(self, "Could not setup irq, %d\n", err);
		sc->sc_intr_hdl = NULL;
		goto error;
	}
	err = ohci_init(sc);
	if (!err) {
		err = device_probe_and_attach(sc->sc_bus.bdev);
	}
	if (err) {
		device_printf(self, "USB init failed\n");
		goto error;
	}
	return (0);

error:
	ohci_pci_detach(self);
	return (ENXIO);
}
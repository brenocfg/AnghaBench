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
struct TYPE_9__ {int dma_bits; int /*<<< orphan*/  bdev; int /*<<< orphan*/  devices_max; int /*<<< orphan*/  devices; int /*<<< orphan*/  parent; } ;
struct TYPE_8__ {TYPE_2__ sc_bus; int /*<<< orphan*/  sc_flags; int /*<<< orphan*/ * sc_intr_hdl; int /*<<< orphan*/ * sc_irq_res; int /*<<< orphan*/  sc_vendor; void* sc_io_res; int /*<<< orphan*/  sc_io_size; int /*<<< orphan*/  sc_io_hdl; int /*<<< orphan*/  sc_io_tag; int /*<<< orphan*/  sc_devices; } ;
typedef  TYPE_1__ ehci_softc_t ;
typedef  int /*<<< orphan*/  driver_intr_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  EHCI_MAX_DEVICES ; 
 int /*<<< orphan*/  EHCI_SCFLG_IAADBUG ; 
 int /*<<< orphan*/  EHCI_SCFLG_LOSTINTRBUG ; 
 int ENOMEM ; 
 int ENXIO ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_BIO ; 
 int PCI_CBMEM ; 
#define  PCI_EHCI_VENDORID_ACERLABS 144 
#define  PCI_EHCI_VENDORID_AMD 143 
#define  PCI_EHCI_VENDORID_APPLE 142 
#define  PCI_EHCI_VENDORID_ATI 141 
#define  PCI_EHCI_VENDORID_CMDTECH 140 
#define  PCI_EHCI_VENDORID_INTEL 139 
#define  PCI_EHCI_VENDORID_NEC 138 
#define  PCI_EHCI_VENDORID_NVIDIA 137 
#define  PCI_EHCI_VENDORID_NVIDIA2 136 
#define  PCI_EHCI_VENDORID_OPTI 135 
#define  PCI_EHCI_VENDORID_PHILIPS 134 
#define  PCI_EHCI_VENDORID_SIS 133 
#define  PCI_EHCI_VENDORID_VIA 132 
 int /*<<< orphan*/  PCI_USBREV ; 
#define  PCI_USB_REV_1_0 131 
#define  PCI_USB_REV_1_1 130 
#define  PCI_USB_REV_2_0 129 
 int PCI_USB_REV_MASK ; 
#define  PCI_USB_REV_PRE_1_0 128 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  USB_GET_DMA_TAG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bootverbose ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*,...) ; 
 int /*<<< orphan*/  device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 TYPE_1__* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int device_probe_and_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int ehci_init (TYPE_1__*) ; 
 scalar_t__ ehci_interrupt ; 
 int /*<<< orphan*/  ehci_iterate_hw_softc ; 
 int /*<<< orphan*/  ehci_pci_ati_quirk (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ehci_pci_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ehci_pci_match (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ehci_pci_take_controller (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ehci_pci_via_quirk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_enable_busmaster (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_device (int /*<<< orphan*/ ) ; 
 int pci_get_devid (int /*<<< orphan*/ ) ; 
 int pci_get_vendor (int /*<<< orphan*/ ) ; 
 int pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rman_get_bushandle (void*) ; 
 int /*<<< orphan*/  rman_get_bustag (void*) ; 
 int /*<<< orphan*/  rman_get_size (void*) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ usb_bus_mem_alloc_all (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ehci_pci_attach(device_t self)
{
	ehci_softc_t *sc = device_get_softc(self);
	int err;
	int rid;

	/* initialise some bus fields */
	sc->sc_bus.parent = self;
	sc->sc_bus.devices = sc->sc_devices;
	sc->sc_bus.devices_max = EHCI_MAX_DEVICES;
	sc->sc_bus.dma_bits = 32;

	/* get all DMA memory */
	if (usb_bus_mem_alloc_all(&sc->sc_bus,
	    USB_GET_DMA_TAG(self), &ehci_iterate_hw_softc)) {
		return (ENOMEM);
	}

	pci_enable_busmaster(self);

	switch (pci_read_config(self, PCI_USBREV, 1) & PCI_USB_REV_MASK) {
	case PCI_USB_REV_PRE_1_0:
	case PCI_USB_REV_1_0:
	case PCI_USB_REV_1_1:
		/*
		 * NOTE: some EHCI USB controllers have the wrong USB
		 * revision number. It appears those controllers are
		 * fully compliant so we just ignore this value in
		 * some common cases.
		 */
		device_printf(self, "pre-2.0 USB revision (ignored)\n");
		/* fallthrough */
	case PCI_USB_REV_2_0:
		break;
	default:
		/* Quirk for Parallels Desktop 4.0 */
		device_printf(self, "USB revision is unknown. Assuming v2.0.\n");
		break;
	}

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
	 * ehci_pci_match will never return NULL if ehci_pci_probe
	 * succeeded
	 */
	device_set_desc(sc->sc_bus.bdev, ehci_pci_match(self));
	switch (pci_get_vendor(self)) {
	case PCI_EHCI_VENDORID_ACERLABS:
		sprintf(sc->sc_vendor, "AcerLabs");
		break;
	case PCI_EHCI_VENDORID_AMD:
		sprintf(sc->sc_vendor, "AMD");
		break;
	case PCI_EHCI_VENDORID_APPLE:
		sprintf(sc->sc_vendor, "Apple");
		break;
	case PCI_EHCI_VENDORID_ATI:
		sprintf(sc->sc_vendor, "ATI");
		break;
	case PCI_EHCI_VENDORID_CMDTECH:
		sprintf(sc->sc_vendor, "CMDTECH");
		break;
	case PCI_EHCI_VENDORID_INTEL:
		sprintf(sc->sc_vendor, "Intel");
		break;
	case PCI_EHCI_VENDORID_NEC:
		sprintf(sc->sc_vendor, "NEC");
		break;
	case PCI_EHCI_VENDORID_OPTI:
		sprintf(sc->sc_vendor, "OPTi");
		break;
	case PCI_EHCI_VENDORID_PHILIPS:
		sprintf(sc->sc_vendor, "Philips");
		break;
	case PCI_EHCI_VENDORID_SIS:
		sprintf(sc->sc_vendor, "SiS");
		break;
	case PCI_EHCI_VENDORID_NVIDIA:
	case PCI_EHCI_VENDORID_NVIDIA2:
		sprintf(sc->sc_vendor, "nVidia");
		break;
	case PCI_EHCI_VENDORID_VIA:
		sprintf(sc->sc_vendor, "VIA");
		break;
	default:
		if (bootverbose)
			device_printf(self, "(New EHCI DeviceId=0x%08x)\n",
			    pci_get_devid(self));
		sprintf(sc->sc_vendor, "(0x%04x)", pci_get_vendor(self));
	}

#if (__FreeBSD_version >= 700031)
	err = bus_setup_intr(self, sc->sc_irq_res, INTR_TYPE_BIO | INTR_MPSAFE,
	    NULL, (driver_intr_t *)ehci_interrupt, sc, &sc->sc_intr_hdl);
#else
	err = bus_setup_intr(self, sc->sc_irq_res, INTR_TYPE_BIO | INTR_MPSAFE,
	    (driver_intr_t *)ehci_interrupt, sc, &sc->sc_intr_hdl);
#endif
	if (err) {
		device_printf(self, "Could not setup irq, %d\n", err);
		sc->sc_intr_hdl = NULL;
		goto error;
	}
	ehci_pci_take_controller(self);

	/* Undocumented quirks taken from Linux */

	switch (pci_get_vendor(self)) {
	case PCI_EHCI_VENDORID_ATI:
		/* SB600 and SB700 EHCI quirk */
		switch (pci_get_device(self)) {
		case 0x4386:
			ehci_pci_ati_quirk(self, 0);
			break;
		case 0x4396:
			ehci_pci_ati_quirk(self, 1);
			break;
		default:
			break;
		}
		break;

	case PCI_EHCI_VENDORID_VIA:
		ehci_pci_via_quirk(self);
		break;

	default:
		break;
	}

	/* Dropped interrupts workaround */
	switch (pci_get_vendor(self)) {
	case PCI_EHCI_VENDORID_ATI:
	case PCI_EHCI_VENDORID_VIA:
		sc->sc_flags |= EHCI_SCFLG_LOSTINTRBUG;
		if (bootverbose)
			device_printf(self,
			    "Dropped interrupts workaround enabled\n");
		break;
	default:
		break;
	}

	/* Doorbell feature workaround */
	switch (pci_get_vendor(self)) {
	case PCI_EHCI_VENDORID_NVIDIA:
	case PCI_EHCI_VENDORID_NVIDIA2:
		sc->sc_flags |= EHCI_SCFLG_IAADBUG;
		if (bootverbose)
			device_printf(self,
			    "Doorbell workaround enabled\n");
		break;
	default:
		break;
	}

	err = ehci_init(sc);
	if (!err) {
		err = device_probe_and_attach(sc->sc_bus.bdev);
	}
	if (err) {
		device_printf(self, "USB init failed err=%d\n", err);
		goto error;
	}
	return (0);

error:
	ehci_pci_detach(self);
	return (ENXIO);
}
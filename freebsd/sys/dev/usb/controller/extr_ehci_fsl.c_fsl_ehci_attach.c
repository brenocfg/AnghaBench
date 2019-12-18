#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int dma_bits; int /*<<< orphan*/  bdev; int /*<<< orphan*/  devices_max; int /*<<< orphan*/  devices; int /*<<< orphan*/  parent; } ;
struct TYPE_10__ {int sc_id_vendor; int sc_flags; TYPE_2__ sc_bus; int /*<<< orphan*/  sc_vendor; int /*<<< orphan*/ * sc_intr_hdl; int /*<<< orphan*/ * sc_irq_res; int /*<<< orphan*/ * sc_io_tag; int /*<<< orphan*/  sc_io_hdl; int /*<<< orphan*/ * sc_io_res; int /*<<< orphan*/  sc_devices; } ;
typedef  TYPE_1__ ehci_softc_t ;
typedef  int /*<<< orphan*/  driver_intr_t ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  bus_space_tag_t ;
typedef  int /*<<< orphan*/  bus_space_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  EHCI_MAX_DEVICES ; 
 int EHCI_SCFLG_DONEINIT ; 
 int EHCI_SCFLG_DONTRESET ; 
 int EHCI_SCFLG_NORESTERM ; 
 int EIO ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  FSL_EHCI_REG_OFF ; 
 int /*<<< orphan*/  FSL_EHCI_REG_SIZE ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_BIO ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  USB_GET_DMA_TAG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bs_le_tag ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ **) ; 
 int bus_space_subregion (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_port_power (TYPE_1__*) ; 
 int /*<<< orphan*/  device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 TYPE_1__* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int device_probe_and_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int ehci_init (TYPE_1__*) ; 
 scalar_t__ ehci_interrupt ; 
 int /*<<< orphan*/  ehci_iterate_hw_softc ; 
 int ehci_reset (TYPE_1__*) ; 
 int /*<<< orphan*/  enable_usb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fsl_ehci_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_32b_prefetch (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_snooping (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_to_host_mode (TYPE_1__*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ usb_bus_mem_alloc_all (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
fsl_ehci_attach(device_t self)
{
	ehci_softc_t *sc;
	int rid;
	int err;
	bus_space_handle_t ioh;
	bus_space_tag_t iot;

	sc = device_get_softc(self);
	rid = 0;

	sc->sc_bus.parent = self;
	sc->sc_bus.devices = sc->sc_devices;
	sc->sc_bus.devices_max = EHCI_MAX_DEVICES;
	sc->sc_bus.dma_bits = 32;

	if (usb_bus_mem_alloc_all(&sc->sc_bus,
	    USB_GET_DMA_TAG(self), &ehci_iterate_hw_softc))
		return (ENOMEM);

	/* Allocate io resource for EHCI */
	sc->sc_io_res = bus_alloc_resource_any(self, SYS_RES_MEMORY, &rid,
	    RF_ACTIVE);
	if (sc->sc_io_res == NULL) {
		err = fsl_ehci_detach(self);
		if (err) {
			device_printf(self,
			    "Detach of the driver failed with error %d\n",
			    err);
		}
		return (ENXIO);
	}
	iot = rman_get_bustag(sc->sc_io_res);

	/*
	 * Set handle to USB related registers subregion used by generic
	 * EHCI driver
	 */
	ioh = rman_get_bushandle(sc->sc_io_res);

	err = bus_space_subregion(iot, ioh, FSL_EHCI_REG_OFF, FSL_EHCI_REG_SIZE,
	    &sc->sc_io_hdl);
	if (err != 0) {
		err = fsl_ehci_detach(self);
		if (err) {
			device_printf(self,
			    "Detach of the driver failed with error %d\n",
			    err);
		}
		return (ENXIO);
	}

	/* Set little-endian tag for use by the generic EHCI driver */
	sc->sc_io_tag = &bs_le_tag;

	/* Allocate irq */
	sc->sc_irq_res = bus_alloc_resource_any(self, SYS_RES_IRQ, &rid,
	    RF_ACTIVE);
	if (sc->sc_irq_res == NULL) {
		err = fsl_ehci_detach(self);
		if (err) {
			device_printf(self,
			    "Detach of the driver failed with error %d\n",
			    err);
		}
		return (ENXIO);
	}

	/* Setup interrupt handler */
	err = bus_setup_intr(self, sc->sc_irq_res, INTR_TYPE_BIO | INTR_MPSAFE,
	    NULL, (driver_intr_t *)ehci_interrupt, sc, &sc->sc_intr_hdl);
	if (err) {
		device_printf(self, "Could not setup irq, %d\n", err);
		sc->sc_intr_hdl = NULL;
		err = fsl_ehci_detach(self);
		if (err) {
			device_printf(self,
			    "Detach of the driver failed with error %d\n",
			    err);
		}
		return (ENXIO);
	}

	/* Add USB device */
	sc->sc_bus.bdev = device_add_child(self, "usbus", -1);
	if (!sc->sc_bus.bdev) {
		device_printf(self, "Could not add USB device\n");
		err = fsl_ehci_detach(self);
		if (err) {
			device_printf(self,
			    "Detach of the driver failed with error %d\n",
			    err);
		}
		return (ENOMEM);
	}
	device_set_ivars(sc->sc_bus.bdev, &sc->sc_bus);

	sc->sc_id_vendor = 0x1234;
	strlcpy(sc->sc_vendor, "Freescale", sizeof(sc->sc_vendor));

	/* Enable USB */
	err = ehci_reset(sc);
	if (err) {
		device_printf(self, "Could not reset the controller\n");
		err = fsl_ehci_detach(self);
		if (err) {
			device_printf(self,
			    "Detach of the driver failed with error %d\n",
			    err);
		}
		return (ENXIO);
	}

	enable_usb(self, iot, ioh);
	set_snooping(iot, ioh);
	set_to_host_mode(sc);
	set_32b_prefetch(iot, ioh);

	/*
	 * If usb subsystem is enabled in U-Boot, port power has to be turned
	 * off to allow proper discovery of devices during boot up.
	 */
	clear_port_power(sc);

	/* Set flags */
	sc->sc_flags |= EHCI_SCFLG_DONTRESET | EHCI_SCFLG_NORESTERM;

	err = ehci_init(sc);
	if (!err) {
		sc->sc_flags |= EHCI_SCFLG_DONEINIT;
		err = device_probe_and_attach(sc->sc_bus.bdev);
	}

	if (err) {
		device_printf(self, "USB init failed err=%d\n", err);
		err = fsl_ehci_detach(self);
		if (err) {
			device_printf(self,
			    "Detach of the driver failed with error %d\n",
			    err);
		}
		return (EIO);
	}

	return (0);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int dma_bits; int /*<<< orphan*/  bdev; int /*<<< orphan*/  devices_max; int /*<<< orphan*/  devices; int /*<<< orphan*/  parent; } ;
struct TYPE_7__ {int sc_flags; TYPE_2__ sc_bus; int /*<<< orphan*/  sc_io_tag; int /*<<< orphan*/  sc_vendor_get_port_speed; int /*<<< orphan*/  sc_vendor_post_reset; int /*<<< orphan*/  sc_intr_hdl; int /*<<< orphan*/ * sc_irq_res; int /*<<< orphan*/  sc_vendor; int /*<<< orphan*/  sc_io_hdl; int /*<<< orphan*/  sc_io_size; int /*<<< orphan*/ * sc_io_res; int /*<<< orphan*/  sc_devices; } ;
typedef  TYPE_1__ ehci_softc_t ;
typedef  int /*<<< orphan*/  driver_intr_t ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  bus_space_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  EHCI_MAX_DEVICES ; 
 int /*<<< orphan*/  EHCI_REG_OFFSET ; 
 int /*<<< orphan*/  EHCI_REG_SIZE ; 
 int EHCI_SCFLG_DONEINIT ; 
 int EHCI_SCFLG_NORESTERM ; 
 int EHCI_SCFLG_TT ; 
 int EIO ; 
 int ENOMEM ; 
 int ENXIO ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_BIO ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  USB_GET_DMA_TAG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZY7_USB_TXFILLTUNING ; 
 int ZY7_USB_TXFILLTUNING_TXFIFOTHRES_SHFT ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ bus_space_subregion (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_space_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 TYPE_1__* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int device_probe_and_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  ehci_get_port_speed_portsc ; 
 int ehci_init (TYPE_1__*) ; 
 scalar_t__ ehci_interrupt ; 
 int /*<<< orphan*/  ehci_iterate_hw_softc ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ usb_bus_mem_alloc_all (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zy7_ehci_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zy7_ehci_post_reset ; 
 scalar_t__ zy7_phy_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
zy7_ehci_attach(device_t dev)
{
	ehci_softc_t *sc = device_get_softc(dev);
	bus_space_handle_t bsh;
	int err, rid;
	
	/* initialize some bus fields */
	sc->sc_bus.parent = dev;
	sc->sc_bus.devices = sc->sc_devices;
	sc->sc_bus.devices_max = EHCI_MAX_DEVICES;
	sc->sc_bus.dma_bits = 32;

	/* get all DMA memory */
	if (usb_bus_mem_alloc_all(&sc->sc_bus,
	    USB_GET_DMA_TAG(dev), &ehci_iterate_hw_softc))
		return (ENOMEM);

	/* Allocate memory. */
	rid = 0;
	sc->sc_io_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY,
					       &rid, RF_ACTIVE);
	if (sc->sc_io_res == NULL) {
		device_printf(dev, "Can't allocate memory");
		zy7_ehci_detach(dev);
		return (ENOMEM);
	}

	sc->sc_io_tag = rman_get_bustag(sc->sc_io_res);
	bsh = rman_get_bushandle(sc->sc_io_res);
	sc->sc_io_size = EHCI_REG_SIZE;

	if (bus_space_subregion(sc->sc_io_tag, bsh, EHCI_REG_OFFSET,
				sc->sc_io_size, &sc->sc_io_hdl) != 0)
		panic("%s: unable to subregion USB host registers",
		      device_get_name(dev));

	/* Allocate IRQ. */
	rid = 0;
	sc->sc_irq_res = bus_alloc_resource_any(dev, SYS_RES_IRQ, &rid,
						RF_ACTIVE);
	if (sc->sc_irq_res == NULL) {
		device_printf(dev, "Can't allocate IRQ\n");
		zy7_ehci_detach(dev);
		return (ENOMEM);
	}

	/* Add USB device */
	sc->sc_bus.bdev = device_add_child(dev, "usbus", -1);
	if (!sc->sc_bus.bdev) {
		device_printf(dev, "Could not add USB device\n");
		zy7_ehci_detach(dev);
		return (ENXIO);
	}
	device_set_ivars(sc->sc_bus.bdev, &sc->sc_bus);
	device_set_desc(sc->sc_bus.bdev, "Zynq-7000 ehci USB 2.0 controller");

	strcpy(sc->sc_vendor, "Xilinx"); /* or IP vendor? */

	/* Activate the interrupt */
	err = bus_setup_intr(dev, sc->sc_irq_res, INTR_TYPE_BIO | INTR_MPSAFE,
			     NULL, (driver_intr_t *)ehci_interrupt, sc,
			     &sc->sc_intr_hdl);
	if (err) {
		device_printf(dev, "Cannot setup IRQ\n");
		zy7_ehci_detach(dev);
		return (err);
	}

	/* Customization. */
	sc->sc_flags |= EHCI_SCFLG_TT |	EHCI_SCFLG_NORESTERM;
	sc->sc_vendor_post_reset = zy7_ehci_post_reset;
	sc->sc_vendor_get_port_speed = ehci_get_port_speed_portsc;

	/* Modify FIFO burst threshold from 2 to 8. */
	bus_space_write_4(sc->sc_io_tag, bsh,
			  ZY7_USB_TXFILLTUNING,
			  8 << ZY7_USB_TXFILLTUNING_TXFIFOTHRES_SHFT);

	/* Handle PHY options. */
	if (zy7_phy_config(dev, sc->sc_io_tag, bsh) < 0) {
		device_printf(dev, "Cannot config phy!\n");
		zy7_ehci_detach(dev);
		return (EIO);
	}

	/* Init ehci. */
	err = ehci_init(sc);
	if (!err) {
		sc->sc_flags |= EHCI_SCFLG_DONEINIT;
		err = device_probe_and_attach(sc->sc_bus.bdev);
	}
	if (err) {
		device_printf(dev, "USB init failed err=%d\n", err);
		zy7_ehci_detach(dev);
		return (err);
	}

	return (0);
}
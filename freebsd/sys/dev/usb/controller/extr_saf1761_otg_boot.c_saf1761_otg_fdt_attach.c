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
struct saf1761_otg_softc {TYPE_1__ sc_bus; int /*<<< orphan*/  sc_io_size; void* sc_io_hdl; void* sc_io_tag; void* sc_io_res; int /*<<< orphan*/  sc_devices; int /*<<< orphan*/  sc_hw_mode; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  SOTG_HW_MODE_CTRL_DATA_BUS_WIDTH ; 
 int /*<<< orphan*/  SOTG_MAX_DEVICES ; 
 int /*<<< orphan*/  USB_GET_DMA_TAG (int /*<<< orphan*/ ) ; 
 scalar_t__ USB_PCI_MEMORY_ADDRESS ; 
 int /*<<< orphan*/  USB_PCI_MEMORY_SIZE ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 struct saf1761_otg_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int device_probe_and_attach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_set_interrupt (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct saf1761_otg_softc*) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  saf1761_otg_fdt_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saf1761_otg_filter_interrupt ; 
 int saf1761_otg_init (struct saf1761_otg_softc*) ; 
 int /*<<< orphan*/  saf1761_otg_interrupt ; 
 scalar_t__ usb_bus_mem_alloc_all (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
saf1761_otg_fdt_attach(device_t dev)
{
	struct saf1761_otg_softc *sc = device_get_softc(dev);
	int err;

	/* 32-bit data bus */
	sc->sc_hw_mode |= SOTG_HW_MODE_CTRL_DATA_BUS_WIDTH;

	/* initialise some bus fields */
	sc->sc_bus.parent = dev;
	sc->sc_bus.devices = sc->sc_devices;
	sc->sc_bus.devices_max = SOTG_MAX_DEVICES;
	sc->sc_bus.dma_bits = 32;

	/* get all DMA memory */
	if (usb_bus_mem_alloc_all(&sc->sc_bus, USB_GET_DMA_TAG(dev), NULL))
		return (ENOMEM);

	sc->sc_io_res = (void *)1;
	sc->sc_io_tag = (void *)1;
	sc->sc_io_hdl = (void *)USB_PCI_MEMORY_ADDRESS;
	sc->sc_io_size = USB_PCI_MEMORY_SIZE;

	sc->sc_bus.bdev = device_add_child(dev, "usbus", -1);
	if (sc->sc_bus.bdev == NULL)
		goto error;

	device_set_ivars(sc->sc_bus.bdev, &sc->sc_bus);
	device_set_interrupt(dev, &saf1761_otg_filter_interrupt, &saf1761_otg_interrupt, sc);

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
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ bdev; } ;
struct TYPE_4__ {TYPE_1__ sc_bus; scalar_t__ sc_io_hdl; scalar_t__ sc_io_tag; int /*<<< orphan*/ * sc_io_res; int /*<<< orphan*/ * sc_irq_res; int /*<<< orphan*/ * sc_intr_hdl; } ;
struct jz4780_ohci_softc {int /*<<< orphan*/  gpio_vbus; TYPE_2__ sc_ohci; int /*<<< orphan*/ * clk; } ;
typedef  scalar_t__ device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  OHCI_CONTROL ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_release_resource (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_space_write_4 (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_teardown_intr (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_delete_child (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  device_delete_children (scalar_t__) ; 
 int /*<<< orphan*/  device_detach (scalar_t__) ; 
 struct jz4780_ohci_softc* device_get_softc (scalar_t__) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ohci_detach (TYPE_2__*) ; 
 int /*<<< orphan*/  ohci_iterate_hw_softc ; 
 int /*<<< orphan*/  usb_bus_mem_free_all (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
jz4780_ohci_detach(device_t dev)
{
	struct jz4780_ohci_softc *sc = device_get_softc(dev);
	device_t bdev;

	if (sc->sc_ohci.sc_bus.bdev) {
		bdev = sc->sc_ohci.sc_bus.bdev;
		device_detach(bdev);
		device_delete_child(dev, bdev);
	}
	/* during module unload there are lots of children leftover */
	device_delete_children(dev);

	/*
	 * Put the controller into reset, then disable clocks and do
	 * the MI tear down.  We have to disable the clocks/hardware
	 * after we do the rest of the teardown.  We also disable the
	 * clocks in the opposite order we acquire them, but that
	 * doesn't seem to be absolutely necessary.  We free up the
	 * clocks after we disable them, so the system could, in
	 * theory, reuse them.
	 */
	if (sc->sc_ohci.sc_io_res != NULL) {
		bus_space_write_4(sc->sc_ohci.sc_io_tag, sc->sc_ohci.sc_io_hdl,
		    OHCI_CONTROL, 0);
	}

	if (sc->sc_ohci.sc_intr_hdl) {
		bus_teardown_intr(dev, sc->sc_ohci.sc_irq_res, sc->sc_ohci.sc_intr_hdl);
		sc->sc_ohci.sc_intr_hdl = NULL;
	}

	if (sc->sc_ohci.sc_irq_res && sc->sc_ohci.sc_intr_hdl) {
		/*
		 * only call ohci_detach() after ohci_init()
		 */
		ohci_detach(&sc->sc_ohci);

		bus_release_resource(dev, SYS_RES_IRQ, 0, sc->sc_ohci.sc_irq_res);
		sc->sc_ohci.sc_irq_res = NULL;
	}
	if (sc->sc_ohci.sc_io_res) {
		bus_release_resource(dev, SYS_RES_MEMORY, 0, sc->sc_ohci.sc_io_res);
		sc->sc_ohci.sc_io_res = NULL;
		sc->sc_ohci.sc_io_tag = 0;
		sc->sc_ohci.sc_io_hdl = 0;
	}

	if (sc->clk != NULL)
		clk_release(sc->clk);

	usb_bus_mem_free_all(&sc->sc_ohci.sc_bus, &ohci_iterate_hw_softc);
	free(sc->gpio_vbus, M_DEVBUF);
	return (0);
}
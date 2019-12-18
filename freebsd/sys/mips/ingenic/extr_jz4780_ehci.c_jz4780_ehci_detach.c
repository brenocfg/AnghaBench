#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ bdev; } ;
struct TYPE_4__ {TYPE_2__ sc_bus; int /*<<< orphan*/ * sc_io_res; int /*<<< orphan*/ * sc_irq_res; int /*<<< orphan*/ * sc_intr_hdl; } ;
struct jz4780_ehci_softc {int /*<<< orphan*/  gpio_vbus; scalar_t__ clk; TYPE_1__ base; } ;
typedef  TYPE_1__ ehci_softc_t ;
typedef  scalar_t__ device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_release_resource (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bus_teardown_intr (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_release (scalar_t__) ; 
 int /*<<< orphan*/  device_delete_child (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  device_delete_children (scalar_t__) ; 
 int /*<<< orphan*/  device_detach (scalar_t__) ; 
 struct jz4780_ehci_softc* device_get_softc (scalar_t__) ; 
 int /*<<< orphan*/  device_printf (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  ehci_detach (TYPE_1__*) ; 
 int /*<<< orphan*/  ehci_iterate_hw_softc ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_bus_mem_free_all (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
jz4780_ehci_detach(device_t dev)
{
	struct jz4780_ehci_softc *isc;
	ehci_softc_t *sc;
	device_t bdev;
	int err;

	isc = device_get_softc(dev);
	sc = &isc->base;

	if (sc->sc_bus.bdev) {
		bdev = sc->sc_bus.bdev;
		device_detach(bdev);
		device_delete_child(dev, bdev);
	}
	/* during module unload there are lots of children leftover */
	device_delete_children(dev);

	if (sc->sc_irq_res && sc->sc_intr_hdl) {
		/*
		 * only call ehci_detach() after ehci_init()
		 */
		ehci_detach(sc);

		err = bus_teardown_intr(dev, sc->sc_irq_res, sc->sc_intr_hdl);

		if (err)
			/* XXX or should we panic? */
			device_printf(dev, "Could not tear down irq, %d\n",
			    err);
		sc->sc_intr_hdl = NULL;
	}

	if (sc->sc_irq_res) {
		bus_release_resource(dev, SYS_RES_IRQ, 0, sc->sc_irq_res);
		sc->sc_irq_res = NULL;
	}
	if (sc->sc_io_res) {
		bus_release_resource(dev, SYS_RES_MEMORY, 0,
		    sc->sc_io_res);
		sc->sc_io_res = NULL;
	}

	if (isc->clk)
		clk_release(isc->clk);

	usb_bus_mem_free_all(&sc->sc_bus, &ehci_iterate_hw_softc);
	free(isc->gpio_vbus, M_DEVBUF);
	return (0);
}
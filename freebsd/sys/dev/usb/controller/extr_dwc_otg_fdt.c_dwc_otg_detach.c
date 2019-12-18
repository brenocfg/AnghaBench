#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  sc_bus; int /*<<< orphan*/ * sc_io_res; int /*<<< orphan*/ * sc_irq_res; int /*<<< orphan*/ * sc_intr_hdl; } ;
struct dwc_otg_fdt_softc {TYPE_1__ sc_otg; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_delete_children (int /*<<< orphan*/ ) ; 
 struct dwc_otg_fdt_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc_otg_uninit (TYPE_1__*) ; 
 int /*<<< orphan*/  usb_bus_mem_free_all (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
dwc_otg_detach(device_t dev)
{
	struct dwc_otg_fdt_softc *sc = device_get_softc(dev);

	/* during module unload there are lots of children leftover */
	device_delete_children(dev);

	if (sc->sc_otg.sc_irq_res && sc->sc_otg.sc_intr_hdl) {
		/*
		 * only call dwc_otg_uninit() after dwc_otg_init()
		 */
		dwc_otg_uninit(&sc->sc_otg);

		bus_teardown_intr(dev, sc->sc_otg.sc_irq_res,
		    sc->sc_otg.sc_intr_hdl);
		sc->sc_otg.sc_intr_hdl = NULL;
	}
	/* free IRQ channel, if any */
	if (sc->sc_otg.sc_irq_res) {
		bus_release_resource(dev, SYS_RES_IRQ, 0,
		    sc->sc_otg.sc_irq_res);
		sc->sc_otg.sc_irq_res = NULL;
	}
	/* free memory resource, if any */
	if (sc->sc_otg.sc_io_res) {
		bus_release_resource(dev, SYS_RES_MEMORY, 0,
		    sc->sc_otg.sc_io_res);
		sc->sc_otg.sc_io_res = NULL;
	}
	usb_bus_mem_free_all(&sc->sc_otg.sc_bus, NULL);

	return (0);
}
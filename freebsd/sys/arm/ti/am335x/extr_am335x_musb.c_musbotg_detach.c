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
struct TYPE_2__ {scalar_t__ sc_irq_res; int /*<<< orphan*/  sc_bus; int /*<<< orphan*/ * sc_intr_hdl; } ;
struct musbotg_super_softc {TYPE_1__ sc_otg; int /*<<< orphan*/  sc_irq_rid; scalar_t__* sc_mem_res; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  am335x_musbotg_mem_spec ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bus_release_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int bus_teardown_intr (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_delete_children (int /*<<< orphan*/ ) ; 
 struct musbotg_super_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  musbotg_uninit (TYPE_1__*) ; 
 int /*<<< orphan*/  usb_bus_mem_free_all (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
musbotg_detach(device_t dev)
{
	struct musbotg_super_softc *sc = device_get_softc(dev);
	int err;

	/* during module unload there are lots of children leftover */
	device_delete_children(dev);

	if (sc->sc_otg.sc_irq_res && sc->sc_otg.sc_intr_hdl) {
		/*
		 * only call musbotg_uninit() after musbotg_init()
		 */
		musbotg_uninit(&sc->sc_otg);

		err = bus_teardown_intr(dev, sc->sc_otg.sc_irq_res,
		    sc->sc_otg.sc_intr_hdl);
		sc->sc_otg.sc_intr_hdl = NULL;
	}

	usb_bus_mem_free_all(&sc->sc_otg.sc_bus, NULL);

	/* Free resources if any */
	if (sc->sc_mem_res[0])
		bus_release_resources(dev, am335x_musbotg_mem_spec,
		    sc->sc_mem_res);

	if (sc->sc_otg.sc_irq_res)
		bus_release_resource(dev, SYS_RES_IRQ, sc->sc_irq_rid,
		    sc->sc_otg.sc_irq_res);

	return (0);
}
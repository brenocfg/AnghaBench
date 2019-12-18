#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int sc_flags; int /*<<< orphan*/  sc_bus; scalar_t__ sc_io_res; scalar_t__ sc_irq_res; int /*<<< orphan*/ * sc_intr_hdl; } ;
typedef  TYPE_1__ ehci_softc_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EHCI_SCFLG_DONEINIT ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_delete_children (int /*<<< orphan*/ ) ; 
 TYPE_1__* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ehci_detach (TYPE_1__*) ; 
 int /*<<< orphan*/  ehci_iterate_hw_softc ; 
 int /*<<< orphan*/  rman_get_rid (scalar_t__) ; 
 int /*<<< orphan*/  usb_bus_mem_free_all (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
zy7_ehci_detach(device_t dev)
{
	ehci_softc_t *sc = device_get_softc(dev);

	/* during module unload there are lots of children leftover */
	device_delete_children(dev);
	
	if ((sc->sc_flags & EHCI_SCFLG_DONEINIT) != 0) {
		ehci_detach(sc);
		sc->sc_flags &= ~EHCI_SCFLG_DONEINIT;
	}

	if (sc->sc_irq_res) {
		if (sc->sc_intr_hdl != NULL)
			bus_teardown_intr(dev, sc->sc_irq_res,
					  sc->sc_intr_hdl);
		bus_release_resource(dev, SYS_RES_IRQ,
			     rman_get_rid(sc->sc_irq_res), sc->sc_irq_res);
	}

	if (sc->sc_io_res)
		bus_release_resource(dev, SYS_RES_MEMORY,
			     rman_get_rid(sc->sc_io_res), sc->sc_io_res);
	usb_bus_mem_free_all(&sc->sc_bus, &ehci_iterate_hw_softc);

	return (0);
}
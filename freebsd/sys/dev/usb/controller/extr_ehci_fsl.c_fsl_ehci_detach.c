#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * bdev; } ;
struct TYPE_6__ {int sc_flags; scalar_t__ sc_io_hdl; scalar_t__ sc_io_tag; int /*<<< orphan*/ * sc_io_res; int /*<<< orphan*/ * sc_irq_res; TYPE_1__ sc_bus; int /*<<< orphan*/ * sc_intr_hdl; } ;
typedef  TYPE_2__ ehci_softc_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EHCI_SCFLG_DONEINIT ; 
 int /*<<< orphan*/  EHCI_USBINTR ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_space_write_4 (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_delete_children (int /*<<< orphan*/ ) ; 
 TYPE_2__* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ehci_detach (TYPE_2__*) ; 

__attribute__((used)) static int
fsl_ehci_detach(device_t self)
{

	int err;
	ehci_softc_t *sc;

	sc = device_get_softc(self);
	/*
	 * only call ehci_detach() after ehci_init()
	 */
	if (sc->sc_flags & EHCI_SCFLG_DONEINIT) {
		ehci_detach(sc);
		sc->sc_flags &= ~EHCI_SCFLG_DONEINIT;
	}

	/* Disable interrupts that might have been switched on in ehci_init */
	if (sc->sc_io_tag && sc->sc_io_hdl)
		bus_space_write_4(sc->sc_io_tag, sc->sc_io_hdl, EHCI_USBINTR, 0);

	if (sc->sc_irq_res && sc->sc_intr_hdl) {
		err = bus_teardown_intr(self, sc->sc_irq_res, sc->sc_intr_hdl);
		if (err) {
			device_printf(self, "Could not tear down irq, %d\n",
			    err);
			return (err);
		}
		sc->sc_intr_hdl = NULL;
	}

	if (sc->sc_bus.bdev) {
		device_delete_child(self, sc->sc_bus.bdev);
		sc->sc_bus.bdev = NULL;
	}

	/* During module unload there are lots of children leftover */
	device_delete_children(self);

	if (sc->sc_irq_res) {
		bus_release_resource(self, SYS_RES_IRQ, 0, sc->sc_irq_res);
		sc->sc_irq_res = NULL;
	}

	if (sc->sc_io_res) {
		bus_release_resource(self, SYS_RES_MEMORY, 0, sc->sc_io_res);
		sc->sc_io_res = NULL;
		sc->sc_io_tag = 0;
		sc->sc_io_hdl = 0;
	}

	return (0);
}
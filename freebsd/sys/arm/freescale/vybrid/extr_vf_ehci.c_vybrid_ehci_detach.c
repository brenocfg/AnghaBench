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
struct TYPE_3__ {int sc_flags; int /*<<< orphan*/  sc_bus; int /*<<< orphan*/ * sc_intr_hdl; scalar_t__ sc_io_hdl; scalar_t__ sc_io_tag; } ;
struct vybrid_ehci_softc {scalar_t__* res; TYPE_1__ base; } ;
typedef  TYPE_1__ ehci_softc_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EHCI_SCFLG_DONEINIT ; 
 int /*<<< orphan*/  EHCI_USBINTR ; 
 int /*<<< orphan*/  bus_release_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  bus_space_write_4 (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bus_teardown_intr (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int device_delete_children (int /*<<< orphan*/ ) ; 
 struct vybrid_ehci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ehci_detach (TYPE_1__*) ; 
 int /*<<< orphan*/  ehci_iterate_hw_softc ; 
 int /*<<< orphan*/  usb_bus_mem_free_all (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vybrid_ehci_spec ; 

__attribute__((used)) static int
vybrid_ehci_detach(device_t dev)
{
	struct vybrid_ehci_softc *esc;
	ehci_softc_t *sc;
	int err;

	esc = device_get_softc(dev);
	sc = &esc->base;

	/* First detach all children; we can't detach if that fails. */
	if ((err = device_delete_children(dev)) != 0)
		return (err);

	/*
	 * only call ehci_detach() after ehci_init()
	 */
	if (sc->sc_flags & EHCI_SCFLG_DONEINIT) {
		ehci_detach(sc);
		sc->sc_flags &= ~EHCI_SCFLG_DONEINIT;
	}

	/*
	 * Disable interrupts that might have been switched on in
	 * ehci_init.
	 */
	if (sc->sc_io_tag && sc->sc_io_hdl)
		bus_space_write_4(sc->sc_io_tag, sc->sc_io_hdl,
		    EHCI_USBINTR, 0);

	if (esc->res[5] && sc->sc_intr_hdl) {
		err = bus_teardown_intr(dev, esc->res[5],
		    sc->sc_intr_hdl);
		if (err) {
			device_printf(dev, "Could not tear down irq,"
			    " %d\n", err);
			return (err);
		}
		sc->sc_intr_hdl = NULL;
	}

	usb_bus_mem_free_all(&sc->sc_bus, &ehci_iterate_hw_softc);

	bus_release_resources(dev, vybrid_ehci_spec, esc->res);

	return (0);
}
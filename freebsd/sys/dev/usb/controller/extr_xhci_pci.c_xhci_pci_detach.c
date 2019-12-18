#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct xhci_softc {int /*<<< orphan*/ * sc_msix_res; int /*<<< orphan*/ * sc_io_res; int /*<<< orphan*/ * sc_irq_res; int /*<<< orphan*/ * sc_intr_hdl; int /*<<< orphan*/  sc_callout; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_XHCI_CBMEM ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_delete_children (int /*<<< orphan*/ ) ; 
 struct xhci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_busmaster (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_msi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_rid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xhci_halt_controller (struct xhci_softc*) ; 
 int /*<<< orphan*/  xhci_reset_controller (struct xhci_softc*) ; 
 int /*<<< orphan*/  xhci_uninit (struct xhci_softc*) ; 

__attribute__((used)) static int
xhci_pci_detach(device_t self)
{
	struct xhci_softc *sc = device_get_softc(self);

	/* during module unload there are lots of children leftover */
	device_delete_children(self);

	usb_callout_drain(&sc->sc_callout);
	xhci_halt_controller(sc);
	xhci_reset_controller(sc);

	pci_disable_busmaster(self);

	if (sc->sc_irq_res && sc->sc_intr_hdl) {
		bus_teardown_intr(self, sc->sc_irq_res, sc->sc_intr_hdl);
		sc->sc_intr_hdl = NULL;
	}
	if (sc->sc_irq_res) {
		bus_release_resource(self, SYS_RES_IRQ,
		    rman_get_rid(sc->sc_irq_res), sc->sc_irq_res);
		sc->sc_irq_res = NULL;
		pci_release_msi(self);
	}
	if (sc->sc_io_res) {
		bus_release_resource(self, SYS_RES_MEMORY, PCI_XHCI_CBMEM,
		    sc->sc_io_res);
		sc->sc_io_res = NULL;
	}
	if (sc->sc_msix_res) {
		bus_release_resource(self, SYS_RES_MEMORY,
		    rman_get_rid(sc->sc_msix_res), sc->sc_msix_res);
		sc->sc_msix_res = NULL;
	}

	xhci_uninit(sc);

	return (0);
}
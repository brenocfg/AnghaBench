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
struct xhci_softc {int /*<<< orphan*/ * sc_io_res; int /*<<< orphan*/ * sc_irq_res; int /*<<< orphan*/ * sc_intr_hdl; int /*<<< orphan*/  sc_callout; } ;
struct tegra_xhci_softc {scalar_t__ fw_vaddr; int /*<<< orphan*/  fw_size; int /*<<< orphan*/ * irq_hdl_mbox; int /*<<< orphan*/ * irq_res_mbox; scalar_t__ xhci_inited; struct xhci_softc xhci_softc; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOCK_DESTROY (struct tegra_xhci_softc*) ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_delete_children (int /*<<< orphan*/ ) ; 
 struct tegra_xhci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_rid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xhci_halt_controller (struct xhci_softc*) ; 
 int /*<<< orphan*/  xhci_uninit (struct xhci_softc*) ; 

__attribute__((used)) static int
tegra_xhci_detach(device_t dev)
{
	struct tegra_xhci_softc *sc;
	struct xhci_softc *xsc;

	sc = device_get_softc(dev);
	xsc = &sc->xhci_softc;

	/* during module unload there are lots of children leftover */
	device_delete_children(dev);
	if (sc->xhci_inited) {
		usb_callout_drain(&xsc->sc_callout);
		xhci_halt_controller(xsc);
	}

	if (xsc->sc_irq_res && xsc->sc_intr_hdl) {
		bus_teardown_intr(dev, xsc->sc_irq_res, xsc->sc_intr_hdl);
		xsc->sc_intr_hdl = NULL;
	}
	if (xsc->sc_irq_res) {
		bus_release_resource(dev, SYS_RES_IRQ,
		    rman_get_rid(xsc->sc_irq_res), xsc->sc_irq_res);
		xsc->sc_irq_res = NULL;
	}
	if (xsc->sc_io_res != NULL) {
		bus_release_resource(dev, SYS_RES_MEMORY,
		    rman_get_rid(xsc->sc_io_res), xsc->sc_io_res);
		xsc->sc_io_res = NULL;
	}
	if (sc->xhci_inited)
		xhci_uninit(xsc);
	if (sc->irq_hdl_mbox != NULL)
		bus_teardown_intr(dev, sc->irq_res_mbox, sc->irq_hdl_mbox);
	if (sc->fw_vaddr != 0)
		kmem_free(sc->fw_vaddr, sc->fw_size);
	LOCK_DESTROY(sc);
	return (0);
}
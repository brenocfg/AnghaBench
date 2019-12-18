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
struct TYPE_3__ {int sc_flags; int /*<<< orphan*/  sc_bus; int /*<<< orphan*/ * sc_intr_hdl; int /*<<< orphan*/  sc_irq_res; } ;
struct imx_ehci_softc {int /*<<< orphan*/ * ehci_mem_res; int /*<<< orphan*/ * ehci_irq_res; TYPE_1__ ehci_softc; } ;
typedef  TYPE_1__ ehci_softc_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EHCI_SCFLG_DONEINIT ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int device_delete_children (int /*<<< orphan*/ ) ; 
 struct imx_ehci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ehci_detach (TYPE_1__*) ; 
 int /*<<< orphan*/  ehci_iterate_hw_softc ; 
 int /*<<< orphan*/  usb_bus_mem_free_all (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
imx_ehci_detach(device_t dev)
{
	struct imx_ehci_softc *sc;
	ehci_softc_t *esc;
	int err;

	sc = device_get_softc(dev);

	esc = &sc->ehci_softc;

	/* First detach all children; we can't detach if that fails. */
	if ((err = device_delete_children(dev)) != 0)
		return (err);

	if (esc->sc_flags & EHCI_SCFLG_DONEINIT)
		ehci_detach(esc);
	if (esc->sc_intr_hdl != NULL)
		bus_teardown_intr(dev, esc->sc_irq_res, 
		    esc->sc_intr_hdl);
	if (sc->ehci_irq_res != NULL)
		bus_release_resource(dev, SYS_RES_IRQ, 0, 
		    sc->ehci_irq_res);
	if (sc->ehci_mem_res != NULL)
		bus_release_resource(dev, SYS_RES_MEMORY, 0,
		    sc->ehci_mem_res);

	usb_bus_mem_free_all(&esc->sc_bus, &ehci_iterate_hw_softc);

	return (0);
}
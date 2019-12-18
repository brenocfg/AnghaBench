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
struct TYPE_5__ {int /*<<< orphan*/ * bdev; } ;
struct TYPE_4__ {int sc_flags; TYPE_2__ sc_bus; int /*<<< orphan*/ * sc_intr_hdl; int /*<<< orphan*/  sc_irq_res; } ;
struct tegra_ehci_softc {scalar_t__ usb_alloc_called; int /*<<< orphan*/ * ehci_mem_res; int /*<<< orphan*/ * ehci_irq_res; int /*<<< orphan*/ * clk; TYPE_1__ ehci_softc; } ;
typedef  TYPE_1__ ehci_softc_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EHCI_SCFLG_DONEINIT ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_delete_children (int /*<<< orphan*/ ) ; 
 struct tegra_ehci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ehci_detach (TYPE_1__*) ; 
 int /*<<< orphan*/  ehci_iterate_hw_softc ; 
 int /*<<< orphan*/  usb_bus_mem_free_all (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
tegra_ehci_detach(device_t dev)
{
	struct tegra_ehci_softc *sc;
	ehci_softc_t *esc;

	sc = device_get_softc(dev);

	esc = &sc->ehci_softc;
	if (sc->clk != NULL)
		clk_release(sc->clk);
	if (esc->sc_bus.bdev != NULL)
		device_delete_child(dev, esc->sc_bus.bdev);
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
	if (sc->usb_alloc_called)
		usb_bus_mem_free_all(&esc->sc_bus, &ehci_iterate_hw_softc);

	/* During module unload there are lots of children leftover. */
	device_delete_children(dev);

	return (0);
}
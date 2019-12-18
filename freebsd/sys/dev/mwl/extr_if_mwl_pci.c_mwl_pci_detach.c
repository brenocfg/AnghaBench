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
struct mwl_softc {int sc_invalid; int /*<<< orphan*/  sc_dmat; } ;
struct mwl_pci_softc {int /*<<< orphan*/  sc_sr0; int /*<<< orphan*/  sc_sr1; int /*<<< orphan*/  sc_irq; int /*<<< orphan*/  sc_ih; struct mwl_softc sc_sc; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BS_BAR0 ; 
 int /*<<< orphan*/  BS_BAR1 ; 
 int /*<<< orphan*/  MWL_LOCK_DESTROY (struct mwl_softc*) ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_child_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mwl_pci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwl_detach (struct mwl_softc*) ; 

__attribute__((used)) static int
mwl_pci_detach(device_t dev)
{
	struct mwl_pci_softc *psc = device_get_softc(dev);
	struct mwl_softc *sc = &psc->sc_sc;

	/* check if device was removed */
	sc->sc_invalid = !bus_child_present(dev);

	mwl_detach(sc);

	bus_generic_detach(dev);
	bus_teardown_intr(dev, psc->sc_irq, psc->sc_ih);
	bus_release_resource(dev, SYS_RES_IRQ, 0, psc->sc_irq);

	bus_dma_tag_destroy(sc->sc_dmat);
	bus_release_resource(dev, SYS_RES_MEMORY, BS_BAR1, psc->sc_sr1);
	bus_release_resource(dev, SYS_RES_MEMORY, BS_BAR0, psc->sc_sr0);

	MWL_LOCK_DESTROY(sc);

	return (0);
}
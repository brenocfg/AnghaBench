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
struct bwi_softc {int sc_invalid; int /*<<< orphan*/  sc_mem_res; int /*<<< orphan*/  sc_irq_res; int /*<<< orphan*/  sc_irq_handle; } ;
struct bwi_pci_softc {struct bwi_softc sc_sc; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BS_BAR ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_child_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bwi_detach (struct bwi_softc*) ; 
 struct bwi_pci_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bwi_pci_detach(device_t dev)
{
	struct bwi_pci_softc *psc = device_get_softc(dev);
	struct bwi_softc *sc = &psc->sc_sc;

	/* check if device was removed */
	sc->sc_invalid = !bus_child_present(dev);

	bwi_detach(sc);

	bus_generic_detach(dev);
	bus_teardown_intr(dev, sc->sc_irq_res, sc->sc_irq_handle);
	bus_release_resource(dev, SYS_RES_IRQ, 0, sc->sc_irq_res);

	bus_release_resource(dev, SYS_RES_MEMORY, BS_BAR, sc->sc_mem_res);

	return (0);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rt2560_softc {int sc_invalid; } ;
struct TYPE_4__ {struct rt2560_softc sc_rt2560; } ;
struct ral_pci_softc {int /*<<< orphan*/  mem; int /*<<< orphan*/  irq; TYPE_1__* sc_opns; int /*<<< orphan*/ * sc_ih; TYPE_2__ u; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_3__ {int /*<<< orphan*/  (* detach ) (struct ral_pci_softc*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_child_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct ral_pci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_msi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_rid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct ral_pci_softc*) ; 

__attribute__((used)) static int
ral_pci_detach(device_t dev)
{
	struct ral_pci_softc *psc = device_get_softc(dev);
	struct rt2560_softc *sc = &psc->u.sc_rt2560;
	
	/* check if device was removed */
	sc->sc_invalid = !bus_child_present(dev);

	if (psc->sc_ih != NULL)
		bus_teardown_intr(dev, psc->irq, psc->sc_ih);
	(*psc->sc_opns->detach)(psc);

	bus_generic_detach(dev);
	bus_release_resource(dev, SYS_RES_IRQ, rman_get_rid(psc->irq),
	    psc->irq);
	pci_release_msi(dev);

	bus_release_resource(dev, SYS_RES_MEMORY, rman_get_rid(psc->mem),
	    psc->mem);

	return 0;
}
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
struct gt_pci_softc {int sc_imask; int sc_elcr; } ;
struct gt_pci_intr_cookie {int irq; struct gt_pci_softc* sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  gt_pci_set_icus (struct gt_pci_softc*) ; 

__attribute__((used)) static void
gt_pci_unmask_irq(void *source)
{
	struct gt_pci_intr_cookie *cookie = source;
	struct gt_pci_softc *sc = cookie->sc;
	int irq = cookie->irq;

	/* Enable it, set trigger mode. */
	sc->sc_imask &= ~(1 << irq);
	sc->sc_elcr &= ~(1 << irq);

	gt_pci_set_icus(sc);
}
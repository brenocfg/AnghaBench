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
struct pci_xhci_softc {int /*<<< orphan*/  xsc_pi; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_lintr_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_msi_enabled (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pci_xhci_deassert_interrupt(struct pci_xhci_softc *sc)
{

	if (!pci_msi_enabled(sc->xsc_pi))
		pci_lintr_assert(sc->xsc_pi);
}
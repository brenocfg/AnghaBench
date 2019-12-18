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
struct vtpci_interrupt {int dummy; } ;
struct vtpci_softc {int vtpci_nmsix_resources; int vtpci_flags; int /*<<< orphan*/  vtpci_dev; struct vtpci_interrupt* vtpci_msix_vq_interrupts; struct vtpci_interrupt vtpci_device_interrupt; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int VTPCI_FLAG_ITYPE_MASK ; 
 int VTPCI_FLAG_MSI ; 
 int VTPCI_FLAG_MSIX ; 
 int /*<<< orphan*/  free (struct vtpci_interrupt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_msi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtpci_free_interrupt (struct vtpci_softc*,struct vtpci_interrupt*) ; 

__attribute__((used)) static void
vtpci_free_interrupts(struct vtpci_softc *sc)
{
	struct vtpci_interrupt *intr;
	int i, nvq_intrs;

	vtpci_free_interrupt(sc, &sc->vtpci_device_interrupt);

	if (sc->vtpci_nmsix_resources != 0) {
		nvq_intrs = sc->vtpci_nmsix_resources - 1;
		sc->vtpci_nmsix_resources = 0;

		intr = sc->vtpci_msix_vq_interrupts;
		if (intr != NULL) {
			for (i = 0; i < nvq_intrs; i++, intr++)
				vtpci_free_interrupt(sc, intr);

			free(sc->vtpci_msix_vq_interrupts, M_DEVBUF);
			sc->vtpci_msix_vq_interrupts = NULL;
		}
	}

	if (sc->vtpci_flags & (VTPCI_FLAG_MSI | VTPCI_FLAG_MSIX))
		pci_release_msi(sc->vtpci_dev);

	sc->vtpci_flags &= ~VTPCI_FLAG_ITYPE_MASK;
}
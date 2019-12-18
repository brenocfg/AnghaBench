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
struct mps_softc {int mps_flags; int /*<<< orphan*/ * mps_regs_resource; int /*<<< orphan*/  mps_regs_rid; int /*<<< orphan*/  mps_dev; int /*<<< orphan*/ * mps_parent_dmat; } ;

/* Variables and functions */
 int MPS_FLAGS_MSI ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mps_pci_free_interrupts (struct mps_softc*) ; 
 int /*<<< orphan*/  pci_release_msi (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mps_pci_free(struct mps_softc *sc)
{

	if (sc->mps_parent_dmat != NULL) {
		bus_dma_tag_destroy(sc->mps_parent_dmat);
	}

	mps_pci_free_interrupts(sc);

	if (sc->mps_flags & MPS_FLAGS_MSI)
		pci_release_msi(sc->mps_dev);

	if (sc->mps_regs_resource != NULL) {
		bus_release_resource(sc->mps_dev, SYS_RES_MEMORY,
		    sc->mps_regs_rid, sc->mps_regs_resource);
	}

	return;
}
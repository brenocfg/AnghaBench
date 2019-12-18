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
struct mpr_softc {int mpr_flags; int /*<<< orphan*/ * mpr_regs_resource; int /*<<< orphan*/  mpr_regs_rid; int /*<<< orphan*/  mpr_dev; int /*<<< orphan*/ * mpr_parent_dmat; } ;

/* Variables and functions */
 int MPR_FLAGS_MSI ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpr_pci_free_interrupts (struct mpr_softc*) ; 
 int /*<<< orphan*/  pci_release_msi (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mpr_pci_free(struct mpr_softc *sc)
{

	if (sc->mpr_parent_dmat != NULL) {
		bus_dma_tag_destroy(sc->mpr_parent_dmat);
	}

	mpr_pci_free_interrupts(sc);

	if (sc->mpr_flags & MPR_FLAGS_MSI)
		pci_release_msi(sc->mpr_dev);

	if (sc->mpr_regs_resource != NULL) {
		bus_release_resource(sc->mpr_dev, SYS_RES_MEMORY,
		    sc->mpr_regs_rid, sc->mpr_regs_resource);
	}

	return;
}
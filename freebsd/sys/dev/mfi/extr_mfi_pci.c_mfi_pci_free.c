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
struct mfi_softc {scalar_t__ mfi_irq_rid; int /*<<< orphan*/  mfi_dev; int /*<<< orphan*/ * mfi_regs_resource; int /*<<< orphan*/  mfi_regs_rid; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_release_msi (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mfi_pci_free(struct mfi_softc *sc)
{

	if (sc->mfi_regs_resource != NULL) {
		bus_release_resource(sc->mfi_dev, SYS_RES_MEMORY,
		    sc->mfi_regs_rid, sc->mfi_regs_resource);
	}
	if (sc->mfi_irq_rid != 0)
		pci_release_msi(sc->mfi_dev);

	return;
}
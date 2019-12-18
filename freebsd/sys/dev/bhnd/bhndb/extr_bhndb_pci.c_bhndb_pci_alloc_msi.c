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
struct bhndb_pci_softc {int /*<<< orphan*/  parent; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BHNDB_PCI_MSI_COUNT ; 
 int ENXIO ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int pci_alloc_msi (int /*<<< orphan*/ ,int*) ; 
 int pci_msi_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_msi (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bhndb_pci_alloc_msi(struct bhndb_pci_softc *sc, int *msi_count)
{
	int error, count;

	/* Is MSI available? */
	if (pci_msi_count(sc->parent) < BHNDB_PCI_MSI_COUNT)
		return (ENXIO);

	/* Allocate expected message count */
	count = BHNDB_PCI_MSI_COUNT;
	if ((error = pci_alloc_msi(sc->parent, &count))) {
		device_printf(sc->dev, "failed to allocate MSI interrupts: "
		    "%d\n", error);

		return (error);
	}

	if (count < BHNDB_PCI_MSI_COUNT) {
		pci_release_msi(sc->parent);
		return (ENXIO);
	}

	*msi_count = count;
	return (0);
}
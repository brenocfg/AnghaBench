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
struct bhndb_pci_softc {scalar_t__ msi_count; int /*<<< orphan*/  parent; int /*<<< orphan*/  isrc; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BHNDB_PCI_LOCK_DESTROY (struct bhndb_pci_softc*) ; 
 int bhndb_disable_pci_clocks (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bhndb_free_intr_isrc (int /*<<< orphan*/ ) ; 
 int bhndb_generic_detach (int /*<<< orphan*/ ) ; 
 int bus_generic_detach (int /*<<< orphan*/ ) ; 
 struct bhndb_pci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_busmaster (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_msi (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bhndb_pci_detach(device_t dev)
{
	struct bhndb_pci_softc	*sc;
	int			 error;

	sc = device_get_softc(dev);

	/* Attempt to detach our children */
	if ((error = bus_generic_detach(dev)))
		return (error);

	/* Perform generic bridge detach */
	if ((error = bhndb_generic_detach(dev)))
		return (error);

	/* Disable clocks (if required by this hardware) */
	if ((error = bhndb_disable_pci_clocks(sc->dev)))
		return (error);

	/* Free our interrupt resources */
	bhndb_free_intr_isrc(sc->isrc);

	/* Release MSI interrupts */
	if (sc->msi_count > 0)
		pci_release_msi(sc->parent);

	/* Disable PCI bus mastering */
	pci_disable_busmaster(sc->parent);

	BHNDB_PCI_LOCK_DESTROY(sc);

	return (0);
}
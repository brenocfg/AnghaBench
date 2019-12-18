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
struct bce_softc {int bce_flags; int /*<<< orphan*/  bce_mtx; int /*<<< orphan*/ * bce_ifp; int /*<<< orphan*/ * bce_res_mem; int /*<<< orphan*/ * bce_res_irq; int /*<<< orphan*/ * bce_intrhand; int /*<<< orphan*/  bce_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BCE_INFO_RESET ; 
 int /*<<< orphan*/  BCE_LOCK_DESTROY (struct bce_softc*) ; 
 int BCE_USING_MSIX_FLAG ; 
 int BCE_USING_MSI_FLAG ; 
 int /*<<< orphan*/  BCE_VERBOSE_RESET ; 
 int /*<<< orphan*/  DBENTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBEXIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBPRINT (struct bce_softc*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PCIR_BAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bce_dma_free (struct bce_softc*) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  if_free (int /*<<< orphan*/ *) ; 
 scalar_t__ mtx_initialized (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_release_msi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_rid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bce_release_resources(struct bce_softc *sc)
{
	device_t dev;

	DBENTER(BCE_VERBOSE_RESET);

	dev = sc->bce_dev;

	bce_dma_free(sc);

	if (sc->bce_intrhand != NULL) {
		DBPRINT(sc, BCE_INFO_RESET, "Removing interrupt handler.\n");
		bus_teardown_intr(dev, sc->bce_res_irq, sc->bce_intrhand);
	}

	if (sc->bce_res_irq != NULL) {
		DBPRINT(sc, BCE_INFO_RESET, "Releasing IRQ.\n");
		bus_release_resource(dev, SYS_RES_IRQ,
		    rman_get_rid(sc->bce_res_irq), sc->bce_res_irq);
	}

	if (sc->bce_flags & (BCE_USING_MSI_FLAG | BCE_USING_MSIX_FLAG)) {
		DBPRINT(sc, BCE_INFO_RESET, "Releasing MSI/MSI-X vector.\n");
		pci_release_msi(dev);
	}

	if (sc->bce_res_mem != NULL) {
		DBPRINT(sc, BCE_INFO_RESET, "Releasing PCI memory.\n");
		    bus_release_resource(dev, SYS_RES_MEMORY, PCIR_BAR(0),
		    sc->bce_res_mem);
	}

	if (sc->bce_ifp != NULL) {
		DBPRINT(sc, BCE_INFO_RESET, "Releasing IF.\n");
		if_free(sc->bce_ifp);
	}

	if (mtx_initialized(&sc->bce_mtx))
		BCE_LOCK_DESTROY(sc);

	DBEXIT(BCE_VERBOSE_RESET);
}
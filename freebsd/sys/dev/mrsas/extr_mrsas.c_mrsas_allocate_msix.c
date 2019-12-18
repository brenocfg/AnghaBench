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
struct mrsas_softc {int /*<<< orphan*/  mrsas_dev; int /*<<< orphan*/  msix_vectors; } ;

/* Variables and functions */
 int FAIL ; 
 int SUCCESS ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mrsas_teardown_intr (struct mrsas_softc*) ; 
 scalar_t__ pci_alloc_msix (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mrsas_allocate_msix(struct mrsas_softc *sc)
{
	if (pci_alloc_msix(sc->mrsas_dev, &sc->msix_vectors) == 0) {
		device_printf(sc->mrsas_dev, "Using MSI-X with %d number"
		    " of vectors\n", sc->msix_vectors);
	} else {
		device_printf(sc->mrsas_dev, "MSI-x setup failed\n");
		goto irq_alloc_failed;
	}
	return SUCCESS;

irq_alloc_failed:
	mrsas_teardown_intr(sc);
	return (FAIL);
}
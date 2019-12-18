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
struct mpr_softc {scalar_t__ disable_msix; int max_msix; scalar_t__ disable_msi; int msi_msgs; int /*<<< orphan*/  mpr_flags; int /*<<< orphan*/  mpr_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  MPR_FLAGS_INTX ; 
 int /*<<< orphan*/  MPR_FLAGS_MSI ; 
 int /*<<< orphan*/  MPR_INIT ; 
 int MPR_MSIX_MAX ; 
 int MPR_MSI_MAX ; 
 int min (int,int) ; 
 int mpr_alloc_msi (struct mpr_softc*,int) ; 
 int mpr_alloc_msix (struct mpr_softc*,int) ; 
 int /*<<< orphan*/  mpr_dprint (struct mpr_softc*,int /*<<< orphan*/ ,char*,...) ; 
 int pci_msi_count (int /*<<< orphan*/ ) ; 
 int pci_msix_count (int /*<<< orphan*/ ) ; 

int
mpr_pci_alloc_interrupts(struct mpr_softc *sc)
{
	device_t dev;
	int error, msgs;

	dev = sc->mpr_dev;
	error = 0;
	msgs = 0;

	if (sc->disable_msix == 0) {
		msgs = pci_msix_count(dev);
		mpr_dprint(sc, MPR_INIT, "Counted %d MSI-X messages\n", msgs);
		msgs = min(msgs, sc->max_msix);
		msgs = min(msgs, MPR_MSIX_MAX);
		msgs = min(msgs, 1);	/* XXX */
		if (msgs != 0) {
			mpr_dprint(sc, MPR_INIT, "Attempting to allocate %d "
			    "MSI-X messages\n", msgs);
			error = mpr_alloc_msix(sc, msgs);
		}
	}
	if (((error != 0) || (msgs == 0)) && (sc->disable_msi == 0)) {
		msgs = pci_msi_count(dev);
		mpr_dprint(sc, MPR_INIT, "Counted %d MSI messages\n", msgs);
		msgs = min(msgs, MPR_MSI_MAX);
		if (msgs != 0) {
			mpr_dprint(sc, MPR_INIT, "Attempting to allocated %d "
			    "MSI messages\n", MPR_MSI_MAX);
			error = mpr_alloc_msi(sc, MPR_MSI_MAX);
		}
	}
	if ((error != 0) || (msgs == 0)) {
		/*
		 * If neither MSI or MSI-X are available, assume legacy INTx.
		 * This also implies that there will be only 1 queue.
		 */
		mpr_dprint(sc, MPR_INIT, "Falling back to legacy INTx\n");
		sc->mpr_flags |= MPR_FLAGS_INTX;
		msgs = 1;
	} else
		sc->mpr_flags |= MPR_FLAGS_MSI;

	sc->msi_msgs = msgs;
	mpr_dprint(sc, MPR_INIT, "Allocated %d interrupts\n", msgs);

	return (error);
}
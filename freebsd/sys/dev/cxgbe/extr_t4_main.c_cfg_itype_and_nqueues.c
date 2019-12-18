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
struct intrs_and_queues {int nirq; } ;
struct adapter {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENXIO ; 
 int INTR_MSI ; 
 int INTR_MSIX ; 
 int /*<<< orphan*/  calculate_iaq (struct adapter*,struct intrs_and_queues*,int,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,int,int,...) ; 
 int pci_alloc_msi (int /*<<< orphan*/ ,int*) ; 
 int pci_alloc_msix (int /*<<< orphan*/ ,int*) ; 
 int pci_msi_count (int /*<<< orphan*/ ) ; 
 int pci_msix_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_msi (int /*<<< orphan*/ ) ; 
 int t4_intr_types ; 

__attribute__((used)) static int
cfg_itype_and_nqueues(struct adapter *sc, struct intrs_and_queues *iaq)
{
	int rc, itype, navail, nalloc;

	for (itype = INTR_MSIX; itype; itype >>= 1) {

		if ((itype & t4_intr_types) == 0)
			continue;	/* not allowed */

		if (itype == INTR_MSIX)
			navail = pci_msix_count(sc->dev);
		else if (itype == INTR_MSI)
			navail = pci_msi_count(sc->dev);
		else
			navail = 1;
restart:
		if (navail == 0)
			continue;

		calculate_iaq(sc, iaq, itype, navail);
		nalloc = iaq->nirq;
		rc = 0;
		if (itype == INTR_MSIX)
			rc = pci_alloc_msix(sc->dev, &nalloc);
		else if (itype == INTR_MSI)
			rc = pci_alloc_msi(sc->dev, &nalloc);

		if (rc == 0 && nalloc > 0) {
			if (nalloc == iaq->nirq)
				return (0);

			/*
			 * Didn't get the number requested.  Use whatever number
			 * the kernel is willing to allocate.
			 */
			device_printf(sc->dev, "fewer vectors than requested, "
			    "type=%d, req=%d, rcvd=%d; will downshift req.\n",
			    itype, iaq->nirq, nalloc);
			pci_release_msi(sc->dev);
			navail = nalloc;
			goto restart;
		}

		device_printf(sc->dev,
		    "failed to allocate vectors:%d, type=%d, req=%d, rcvd=%d\n",
		    itype, rc, iaq->nirq, nalloc);
	}

	device_printf(sc->dev,
	    "failed to find a usable interrupt type.  "
	    "allowed=%d, msi-x=%d, msi=%d, intx=1", t4_intr_types,
	    pci_msix_count(sc->dev), pci_msi_count(sc->dev));

	return (ENXIO);
}
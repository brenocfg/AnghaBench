#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vf_resources {int niqflint; int nethctrl; int neq; } ;
struct intrs_and_queues {int intr_type; int nirq; int ntxq; int nrxq; } ;
struct TYPE_2__ {int nports; struct vf_resources vfres; } ;
struct adapter {int /*<<< orphan*/  dev; TYPE_1__ params; } ;

/* Variables and functions */
 int ENXIO ; 
 int INTR_INTX ; 
 int INTR_MSI ; 
 int INTR_MSIX ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int T4VF_EXTRA_INTR ; 
 int /*<<< orphan*/  bzero (struct intrs_and_queues*,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,int,...) ; 
 int pci_alloc_msi (int /*<<< orphan*/ ,int*) ; 
 int pci_alloc_msix (int /*<<< orphan*/ ,int*) ; 
 int pci_msi_count (int /*<<< orphan*/ ) ; 
 int pci_msix_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_msi (int /*<<< orphan*/ ) ; 
 scalar_t__ powerof2 (int) ; 
 int /*<<< orphan*/  t4_intr_types ; 
 int t4_nrxq ; 
 int t4_ntxq ; 

__attribute__((used)) static int
cfg_itype_and_nqueues(struct adapter *sc, struct intrs_and_queues *iaq)
{
	struct vf_resources *vfres;
	int nrxq, ntxq, nports;
	int itype, iq_avail, navail, rc;

	/*
	 * Figure out the layout of queues across our VIs and ensure
	 * we can allocate enough interrupts for our layout.
	 */
	vfres = &sc->params.vfres;
	nports = sc->params.nports;
	bzero(iaq, sizeof(*iaq));

	for (itype = INTR_MSIX; itype != 0; itype >>= 1) {
		if (itype == INTR_INTX)
			continue;

		if (itype == INTR_MSIX)
			navail = pci_msix_count(sc->dev);
		else
			navail = pci_msi_count(sc->dev);

		if (navail == 0)
			continue;

		iaq->intr_type = itype;

		/*
		 * XXX: The Linux driver reserves an Ingress Queue for
		 * forwarded interrupts when using MSI (but not MSI-X).
		 * It seems it just always asks for 2 interrupts and
		 * forwards all rxqs to the forwarded interrupt.
		 *
		 * We must reserve one IRQ for the for the firmware
		 * event queue.
		 *
		 * Every rxq requires an ingress queue with a free
		 * list and interrupts and an egress queue.  Every txq
		 * requires an ETH egress queue.
		 */
		iaq->nirq = T4VF_EXTRA_INTR;

		/*
		 * First, determine how many queues we can allocate.
		 * Start by finding the upper bound on rxqs from the
		 * limit on ingress queues.
		 */
		iq_avail = vfres->niqflint - iaq->nirq;
		if (iq_avail < nports) {
			device_printf(sc->dev,
			    "Not enough ingress queues (%d) for %d ports\n",
			    vfres->niqflint, nports);
			return (ENXIO);
		}

		/*
		 * Try to honor the cap on interrupts.  If there aren't
		 * enough interrupts for at least one interrupt per
		 * port, then don't bother, we will just forward all
		 * interrupts to one interrupt in that case.
		 */
		if (iaq->nirq + nports <= navail) {
			if (iq_avail > navail - iaq->nirq)
				iq_avail = navail - iaq->nirq;
		}

		nrxq = nports * t4_nrxq;
		if (nrxq > iq_avail) {
			/*
			 * Too many ingress queues.  Use what we can.
			 */
			nrxq = (iq_avail / nports) * nports;
		}
		KASSERT(nrxq <= iq_avail, ("too many ingress queues"));

		/*
		 * Next, determine the upper bound on txqs from the limit
		 * on ETH queues.
		 */
		if (vfres->nethctrl < nports) {
			device_printf(sc->dev,
			    "Not enough ETH queues (%d) for %d ports\n",
			    vfres->nethctrl, nports);
			return (ENXIO);
		}

		ntxq = nports * t4_ntxq;
		if (ntxq > vfres->nethctrl) {
			/*
			 * Too many ETH queues.  Use what we can.
			 */
			ntxq = (vfres->nethctrl / nports) * nports;
		}
		KASSERT(ntxq <= vfres->nethctrl, ("too many ETH queues"));

		/*
		 * Finally, ensure we have enough egress queues.
		 */
		if (vfres->neq < nports * 2) {
			device_printf(sc->dev,
			    "Not enough egress queues (%d) for %d ports\n",
			    vfres->neq, nports);
			return (ENXIO);
		}
		if (nrxq + ntxq > vfres->neq) {
			/* Just punt and use 1 for everything. */
			nrxq = ntxq = nports;
		}
		KASSERT(nrxq <= iq_avail, ("too many ingress queues"));
		KASSERT(ntxq <= vfres->nethctrl, ("too many ETH queues"));
		KASSERT(nrxq + ntxq <= vfres->neq, ("too many egress queues"));

		/*
		 * Do we have enough interrupts?  For MSI the interrupts
		 * have to be a power of 2 as well.
		 */
		iaq->nirq += nrxq;
		iaq->ntxq = ntxq;
		iaq->nrxq = nrxq;
		if (iaq->nirq <= navail &&
		    (itype != INTR_MSI || powerof2(iaq->nirq))) {
			navail = iaq->nirq;
			if (itype == INTR_MSIX)
				rc = pci_alloc_msix(sc->dev, &navail);
			else
				rc = pci_alloc_msi(sc->dev, &navail);
			if (rc != 0) {
				device_printf(sc->dev,
		    "failed to allocate vectors:%d, type=%d, req=%d, rcvd=%d\n",
				    itype, rc, iaq->nirq, navail);
				return (rc);
			}
			if (navail == iaq->nirq) {
				return (0);
			}
			pci_release_msi(sc->dev);
		}

		/* Fall back to a single interrupt. */
		iaq->nirq = 1;
		navail = iaq->nirq;
		if (itype == INTR_MSIX)
			rc = pci_alloc_msix(sc->dev, &navail);
		else
			rc = pci_alloc_msi(sc->dev, &navail);
		if (rc != 0)
			device_printf(sc->dev,
		    "failed to allocate vectors:%d, type=%d, req=%d, rcvd=%d\n",
			    itype, rc, iaq->nirq, navail);
		return (rc);
	}

	device_printf(sc->dev,
	    "failed to find a usable interrupt type.  "
	    "allowed=%d, msi-x=%d, msi=%d, intx=1", t4_intr_types,
	    pci_msix_count(sc->dev), pci_msi_count(sc->dev));

	return (ENXIO);
}
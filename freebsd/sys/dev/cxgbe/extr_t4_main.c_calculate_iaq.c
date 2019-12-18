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
struct intrs_and_queues {int intr_type; int num_vis; int ntxq; scalar_t__ ntxq_vi; int nrxq; scalar_t__ nrxq_vi; int nofldtxq; int nofldrxq; int nirq; scalar_t__ nnmrxq_vi; scalar_t__ nofldrxq_vi; scalar_t__ nnmtxq_vi; scalar_t__ nofldtxq_vi; } ;
struct TYPE_2__ {int nports; } ;
struct adapter {int /*<<< orphan*/  dev; TYPE_1__ params; } ;

/* Variables and functions */
 int INTR_MSI ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  bzero (struct intrs_and_queues*,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,int,...) ; 
 scalar_t__ is_ethoffload (struct adapter*) ; 
 scalar_t__ is_offload (struct adapter*) ; 
 int powerof2 (int) ; 
 scalar_t__ t4_nnmrxq_vi ; 
 scalar_t__ t4_nnmtxq_vi ; 
 int t4_nofldrxq ; 
 scalar_t__ t4_nofldrxq_vi ; 
 int t4_nofldtxq ; 
 scalar_t__ t4_nofldtxq_vi ; 
 int t4_nrxq ; 
 scalar_t__ t4_nrxq_vi ; 
 int t4_ntxq ; 
 scalar_t__ t4_ntxq_vi ; 
 int t4_num_vis ; 
 int /*<<< orphan*/  update_nirq (struct intrs_and_queues*,int const) ; 

__attribute__((used)) static void
calculate_iaq(struct adapter *sc, struct intrs_and_queues *iaq, int itype,
    int navail)
{
	int old_nirq;
	const int nports = sc->params.nports;

	MPASS(nports > 0);
	MPASS(navail > 0);

	bzero(iaq, sizeof(*iaq));
	iaq->intr_type = itype;
	iaq->num_vis = t4_num_vis;
	iaq->ntxq = t4_ntxq;
	iaq->ntxq_vi = t4_ntxq_vi;
	iaq->nrxq = t4_nrxq;
	iaq->nrxq_vi = t4_nrxq_vi;
#if defined(TCP_OFFLOAD) || defined(RATELIMIT)
	if (is_offload(sc) || is_ethoffload(sc)) {
		iaq->nofldtxq = t4_nofldtxq;
		iaq->nofldtxq_vi = t4_nofldtxq_vi;
	}
#endif
#ifdef TCP_OFFLOAD
	if (is_offload(sc)) {
		iaq->nofldrxq = t4_nofldrxq;
		iaq->nofldrxq_vi = t4_nofldrxq_vi;
	}
#endif
#ifdef DEV_NETMAP
	iaq->nnmtxq_vi = t4_nnmtxq_vi;
	iaq->nnmrxq_vi = t4_nnmrxq_vi;
#endif

	update_nirq(iaq, nports);
	if (iaq->nirq <= navail &&
	    (itype != INTR_MSI || powerof2(iaq->nirq))) {
		/*
		 * This is the normal case -- there are enough interrupts for
		 * everything.
		 */
		goto done;
	}

	/*
	 * If extra VIs have been configured try reducing their count and see if
	 * that works.
	 */
	while (iaq->num_vis > 1) {
		iaq->num_vis--;
		update_nirq(iaq, nports);
		if (iaq->nirq <= navail &&
		    (itype != INTR_MSI || powerof2(iaq->nirq))) {
			device_printf(sc->dev, "virtual interfaces per port "
			    "reduced to %d from %d.  nrxq=%u, nofldrxq=%u, "
			    "nrxq_vi=%u nofldrxq_vi=%u, nnmrxq_vi=%u.  "
			    "itype %d, navail %u, nirq %d.\n",
			    iaq->num_vis, t4_num_vis, iaq->nrxq, iaq->nofldrxq,
			    iaq->nrxq_vi, iaq->nofldrxq_vi, iaq->nnmrxq_vi,
			    itype, navail, iaq->nirq);
			goto done;
		}
	}

	/*
	 * Extra VIs will not be created.  Log a message if they were requested.
	 */
	MPASS(iaq->num_vis == 1);
	iaq->ntxq_vi = iaq->nrxq_vi = 0;
	iaq->nofldtxq_vi = iaq->nofldrxq_vi = 0;
	iaq->nnmtxq_vi = iaq->nnmrxq_vi = 0;
	if (iaq->num_vis != t4_num_vis) {
		device_printf(sc->dev, "extra virtual interfaces disabled.  "
		    "nrxq=%u, nofldrxq=%u, nrxq_vi=%u nofldrxq_vi=%u, "
		    "nnmrxq_vi=%u.  itype %d, navail %u, nirq %d.\n",
		    iaq->nrxq, iaq->nofldrxq, iaq->nrxq_vi, iaq->nofldrxq_vi,
		    iaq->nnmrxq_vi, itype, navail, iaq->nirq);
	}

	/*
	 * Keep reducing the number of NIC rx queues to the next lower power of
	 * 2 (for even RSS distribution) and halving the TOE rx queues and see
	 * if that works.
	 */
	do {
		if (iaq->nrxq > 1) {
			do {
				iaq->nrxq--;
			} while (!powerof2(iaq->nrxq));
		}
		if (iaq->nofldrxq > 1)
			iaq->nofldrxq >>= 1;

		old_nirq = iaq->nirq;
		update_nirq(iaq, nports);
		if (iaq->nirq <= navail &&
		    (itype != INTR_MSI || powerof2(iaq->nirq))) {
			device_printf(sc->dev, "running with reduced number of "
			    "rx queues because of shortage of interrupts.  "
			    "nrxq=%u, nofldrxq=%u.  "
			    "itype %d, navail %u, nirq %d.\n", iaq->nrxq,
			    iaq->nofldrxq, itype, navail, iaq->nirq);
			goto done;
		}
	} while (old_nirq != iaq->nirq);

	/* One interrupt for everything.  Ugh. */
	device_printf(sc->dev, "running with minimal number of queues.  "
	    "itype %d, navail %u.\n", itype, navail);
	iaq->nirq = 1;
	MPASS(iaq->nrxq == 1);
	iaq->ntxq = 1;
	if (iaq->nofldrxq > 1)
		iaq->nofldtxq = 1;
done:
	MPASS(iaq->num_vis > 0);
	if (iaq->num_vis > 1) {
		MPASS(iaq->nrxq_vi > 0);
		MPASS(iaq->ntxq_vi > 0);
	}
	MPASS(iaq->nirq > 0);
	MPASS(iaq->nrxq > 0);
	MPASS(iaq->ntxq > 0);
	if (itype == INTR_MSI) {
		MPASS(powerof2(iaq->nirq));
	}
}
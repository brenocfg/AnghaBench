#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32_t ;
struct ubsec_softc {int volatile sc_statmask; int sc_nqchip; int sc_flags; int sc_needwakeup; int /*<<< orphan*/  sc_cid; int /*<<< orphan*/  sc_freeqlock; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_mcr1lock; int /*<<< orphan*/  sc_mcr2lock; int /*<<< orphan*/  sc_qchip2; int /*<<< orphan*/  sc_qchip; } ;
struct TYPE_8__ {scalar_t__ dma_vaddr; } ;
struct ubsec_q2 {TYPE_4__ q_mcr; } ;
struct ubsec_q {int q_nstacked_mcrs; struct ubsec_q** q_stacked_mcr; struct ubsec_dma* q_dma; } ;
struct ubsec_mcr {int mcr_flags; } ;
struct ubsec_dma {TYPE_2__* d_dma; } ;
struct TYPE_7__ {int /*<<< orphan*/  hst_dmaerr; } ;
struct TYPE_5__ {int mcr_flags; } ;
struct TYPE_6__ {TYPE_1__ d_mcr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BS_ERR ; 
 int volatile BS_ERR_ADDR ; 
 int volatile BS_ERR_READ ; 
 int /*<<< orphan*/  BS_STAT ; 
 int volatile BS_STAT_DMAERR ; 
 int volatile BS_STAT_MCR1_DONE ; 
 int volatile BS_STAT_MCR2_DONE ; 
 int BUS_DMASYNC_POSTREAD ; 
 int BUS_DMASYNC_POSTWRITE ; 
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int CRYPTO_ASYMQ ; 
 int CRYPTO_SYMQ ; 
 int READ_REG (struct ubsec_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIMPLEQ_EMPTY (int /*<<< orphan*/ *) ; 
 void* SIMPLEQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SIMPLEQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int UBS_FLAGS_KEY ; 
 int UBS_FLAGS_RNG ; 
 int /*<<< orphan*/  UBS_MCR_DONE ; 
 int /*<<< orphan*/  WRITE_REG (struct ubsec_softc*,int /*<<< orphan*/ ,int volatile) ; 
 int /*<<< orphan*/  crypto_unblock (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int htole16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*,int volatile) ; 
 int /*<<< orphan*/  q_next ; 
 int /*<<< orphan*/  ubsec_callback (struct ubsec_softc*,struct ubsec_q*) ; 
 int /*<<< orphan*/  ubsec_callback2 (struct ubsec_softc*,struct ubsec_q2*) ; 
 scalar_t__ ubsec_debug ; 
 int /*<<< orphan*/  ubsec_dma_sync (TYPE_4__*,int) ; 
 int /*<<< orphan*/  ubsec_feed (struct ubsec_softc*) ; 
 int /*<<< orphan*/  ubsec_feed2 (struct ubsec_softc*) ; 
 int /*<<< orphan*/  ubsec_totalreset (struct ubsec_softc*) ; 
 TYPE_3__ ubsecstats ; 

__attribute__((used)) static void
ubsec_intr(void *arg)
{
	struct ubsec_softc *sc = arg;
	volatile u_int32_t stat;
	struct ubsec_q *q;
	struct ubsec_dma *dmap;
	int npkts = 0, i;

	stat = READ_REG(sc, BS_STAT);
	stat &= sc->sc_statmask;
	if (stat == 0)
		return;

	WRITE_REG(sc, BS_STAT, stat);		/* IACK */

	/*
	 * Check to see if we have any packets waiting for us
	 */
	if ((stat & BS_STAT_MCR1_DONE)) {
		mtx_lock(&sc->sc_mcr1lock);
		while (!SIMPLEQ_EMPTY(&sc->sc_qchip)) {
			q = SIMPLEQ_FIRST(&sc->sc_qchip);
			dmap = q->q_dma;

			if ((dmap->d_dma->d_mcr.mcr_flags & htole16(UBS_MCR_DONE)) == 0)
				break;

			SIMPLEQ_REMOVE_HEAD(&sc->sc_qchip, q_next);

			npkts = q->q_nstacked_mcrs;
			sc->sc_nqchip -= 1+npkts;
			/*
			 * search for further sc_qchip ubsec_q's that share
			 * the same MCR, and complete them too, they must be
			 * at the top.
			 */
			for (i = 0; i < npkts; i++) {
				if(q->q_stacked_mcr[i]) {
					ubsec_callback(sc, q->q_stacked_mcr[i]);
				} else {
					break;
				}
			}
			ubsec_callback(sc, q);
		}
		/*
		 * Don't send any more packet to chip if there has been
		 * a DMAERR.
		 */
		if (!(stat & BS_STAT_DMAERR))
			ubsec_feed(sc);
		mtx_unlock(&sc->sc_mcr1lock);
	}

	/*
	 * Check to see if we have any key setups/rng's waiting for us
	 */
	if ((sc->sc_flags & (UBS_FLAGS_KEY|UBS_FLAGS_RNG)) &&
	    (stat & BS_STAT_MCR2_DONE)) {
		struct ubsec_q2 *q2;
		struct ubsec_mcr *mcr;

		mtx_lock(&sc->sc_mcr2lock);
		while (!SIMPLEQ_EMPTY(&sc->sc_qchip2)) {
			q2 = SIMPLEQ_FIRST(&sc->sc_qchip2);

			ubsec_dma_sync(&q2->q_mcr,
			    BUS_DMASYNC_POSTREAD|BUS_DMASYNC_POSTWRITE);

			mcr = (struct ubsec_mcr *)q2->q_mcr.dma_vaddr;
			if ((mcr->mcr_flags & htole16(UBS_MCR_DONE)) == 0) {
				ubsec_dma_sync(&q2->q_mcr,
				    BUS_DMASYNC_PREREAD|BUS_DMASYNC_PREWRITE);
				break;
			}
			SIMPLEQ_REMOVE_HEAD(&sc->sc_qchip2, q_next);
			ubsec_callback2(sc, q2);
			/*
			 * Don't send any more packet to chip if there has been
			 * a DMAERR.
			 */
			if (!(stat & BS_STAT_DMAERR))
				ubsec_feed2(sc);
		}
		mtx_unlock(&sc->sc_mcr2lock);
	}

	/*
	 * Check to see if we got any DMA Error
	 */
	if (stat & BS_STAT_DMAERR) {
#ifdef UBSEC_DEBUG
		if (ubsec_debug) {
			volatile u_int32_t a = READ_REG(sc, BS_ERR);

			printf("dmaerr %s@%08x\n",
			    (a & BS_ERR_READ) ? "read" : "write",
			    a & BS_ERR_ADDR);
		}
#endif /* UBSEC_DEBUG */
		ubsecstats.hst_dmaerr++;
		mtx_lock(&sc->sc_mcr1lock);
		ubsec_totalreset(sc);
		ubsec_feed(sc);
		mtx_unlock(&sc->sc_mcr1lock);
	}

	if (sc->sc_needwakeup) {		/* XXX check high watermark */
		int wakeup;

		mtx_lock(&sc->sc_freeqlock);
		wakeup = sc->sc_needwakeup & (CRYPTO_SYMQ|CRYPTO_ASYMQ);
#ifdef UBSEC_DEBUG
		if (ubsec_debug)
			device_printf(sc->sc_dev, "wakeup crypto (%x)\n",
				sc->sc_needwakeup);
#endif /* UBSEC_DEBUG */
		sc->sc_needwakeup &= ~wakeup;
		mtx_unlock(&sc->sc_freeqlock);
		crypto_unblock(sc->sc_cid, wakeup);
	}
}
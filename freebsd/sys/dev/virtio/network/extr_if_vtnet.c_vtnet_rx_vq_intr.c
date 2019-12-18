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
struct vtnet_softc {scalar_t__ vtnet_act_vq_pairs; struct ifnet* vtnet_ifp; } ;
struct TYPE_2__ {int /*<<< orphan*/  vrxs_rescheduled; } ;
struct vtnet_rxq {scalar_t__ vtnrx_id; int /*<<< orphan*/  vtnrx_intrtask; int /*<<< orphan*/  vtnrx_tq; TYPE_1__ vtnrx_stats; struct vtnet_softc* vtnrx_sc; } ;
struct ifnet {int if_drv_flags; } ;

/* Variables and functions */
 int IFF_DRV_RUNNING ; 
 scalar_t__ NM_IRQ_PASS ; 
 int /*<<< orphan*/  VTNET_INTR_DISABLE_RETRIES ; 
 int /*<<< orphan*/  VTNET_RXQ_LOCK (struct vtnet_rxq*) ; 
 int /*<<< orphan*/  VTNET_RXQ_UNLOCK (struct vtnet_rxq*) ; 
 scalar_t__ __predict_false (int) ; 
 scalar_t__ netmap_rx_irq (struct ifnet*,scalar_t__,int*) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vtnet_rxq_disable_intr (struct vtnet_rxq*) ; 
 scalar_t__ vtnet_rxq_enable_intr (struct vtnet_rxq*) ; 
 int vtnet_rxq_eof (struct vtnet_rxq*) ; 

__attribute__((used)) static void
vtnet_rx_vq_intr(void *xrxq)
{
	struct vtnet_softc *sc;
	struct vtnet_rxq *rxq;
	struct ifnet *ifp;
	int tries, more;

	rxq = xrxq;
	sc = rxq->vtnrx_sc;
	ifp = sc->vtnet_ifp;
	tries = 0;

	if (__predict_false(rxq->vtnrx_id >= sc->vtnet_act_vq_pairs)) {
		/*
		 * Ignore this interrupt. Either this is a spurious interrupt
		 * or multiqueue without per-VQ MSIX so every queue needs to
		 * be polled (a brain dead configuration we could try harder
		 * to avoid).
		 */
		vtnet_rxq_disable_intr(rxq);
		return;
	}

#ifdef DEV_NETMAP
	if (netmap_rx_irq(ifp, rxq->vtnrx_id, &more) != NM_IRQ_PASS)
		return;
#endif /* DEV_NETMAP */

	VTNET_RXQ_LOCK(rxq);

again:
	if ((ifp->if_drv_flags & IFF_DRV_RUNNING) == 0) {
		VTNET_RXQ_UNLOCK(rxq);
		return;
	}

	more = vtnet_rxq_eof(rxq);
	if (more || vtnet_rxq_enable_intr(rxq) != 0) {
		if (!more)
			vtnet_rxq_disable_intr(rxq);
		/*
		 * This is an occasional condition or race (when !more),
		 * so retry a few times before scheduling the taskqueue.
		 */
		if (tries++ < VTNET_INTR_DISABLE_RETRIES)
			goto again;

		VTNET_RXQ_UNLOCK(rxq);
		rxq->vtnrx_stats.vrxs_rescheduled++;
		taskqueue_enqueue(rxq->vtnrx_tq, &rxq->vtnrx_intrtask);
	} else
		VTNET_RXQ_UNLOCK(rxq);
}
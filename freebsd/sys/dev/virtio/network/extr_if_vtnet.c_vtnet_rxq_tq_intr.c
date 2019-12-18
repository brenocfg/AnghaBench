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
struct vtnet_softc {struct ifnet* vtnet_ifp; } ;
struct TYPE_2__ {int /*<<< orphan*/  vrxs_rescheduled; } ;
struct vtnet_rxq {int /*<<< orphan*/  vtnrx_intrtask; int /*<<< orphan*/  vtnrx_tq; TYPE_1__ vtnrx_stats; struct vtnet_softc* vtnrx_sc; } ;
struct ifnet {int if_drv_flags; } ;

/* Variables and functions */
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  VTNET_RXQ_LOCK (struct vtnet_rxq*) ; 
 int /*<<< orphan*/  VTNET_RXQ_UNLOCK (struct vtnet_rxq*) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vtnet_rxq_disable_intr (struct vtnet_rxq*) ; 
 scalar_t__ vtnet_rxq_enable_intr (struct vtnet_rxq*) ; 
 int vtnet_rxq_eof (struct vtnet_rxq*) ; 

__attribute__((used)) static void
vtnet_rxq_tq_intr(void *xrxq, int pending)
{
	struct vtnet_softc *sc;
	struct vtnet_rxq *rxq;
	struct ifnet *ifp;
	int more;

	rxq = xrxq;
	sc = rxq->vtnrx_sc;
	ifp = sc->vtnet_ifp;

	VTNET_RXQ_LOCK(rxq);

	if ((ifp->if_drv_flags & IFF_DRV_RUNNING) == 0) {
		VTNET_RXQ_UNLOCK(rxq);
		return;
	}

	more = vtnet_rxq_eof(rxq);
	if (more || vtnet_rxq_enable_intr(rxq) != 0) {
		if (!more)
			vtnet_rxq_disable_intr(rxq);
		rxq->vtnrx_stats.vrxs_rescheduled++;
		taskqueue_enqueue(rxq->vtnrx_tq, &rxq->vtnrx_intrtask);
	}

	VTNET_RXQ_UNLOCK(rxq);
}
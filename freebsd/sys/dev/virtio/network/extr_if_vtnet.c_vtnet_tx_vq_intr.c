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
struct vtnet_txq {scalar_t__ vtntx_id; struct vtnet_softc* vtntx_sc; } ;
struct vtnet_softc {scalar_t__ vtnet_act_vq_pairs; struct ifnet* vtnet_ifp; } ;
struct ifnet {int if_drv_flags; } ;

/* Variables and functions */
 int IFF_DRV_RUNNING ; 
 scalar_t__ NM_IRQ_PASS ; 
 int /*<<< orphan*/  VTNET_TXQ_LOCK (struct vtnet_txq*) ; 
 int /*<<< orphan*/  VTNET_TXQ_UNLOCK (struct vtnet_txq*) ; 
 scalar_t__ __predict_false (int) ; 
 scalar_t__ netmap_tx_irq (struct ifnet*,scalar_t__) ; 
 int /*<<< orphan*/  vtnet_txq_disable_intr (struct vtnet_txq*) ; 
 int /*<<< orphan*/  vtnet_txq_eof (struct vtnet_txq*) ; 
 int /*<<< orphan*/  vtnet_txq_start (struct vtnet_txq*) ; 

__attribute__((used)) static void
vtnet_tx_vq_intr(void *xtxq)
{
	struct vtnet_softc *sc;
	struct vtnet_txq *txq;
	struct ifnet *ifp;

	txq = xtxq;
	sc = txq->vtntx_sc;
	ifp = sc->vtnet_ifp;

	if (__predict_false(txq->vtntx_id >= sc->vtnet_act_vq_pairs)) {
		/*
		 * Ignore this interrupt. Either this is a spurious interrupt
		 * or multiqueue without per-VQ MSIX so every queue needs to
		 * be polled (a brain dead configuration we could try harder
		 * to avoid).
		 */
		vtnet_txq_disable_intr(txq);
		return;
	}

#ifdef DEV_NETMAP
	if (netmap_tx_irq(ifp, txq->vtntx_id) != NM_IRQ_PASS)
		return;
#endif /* DEV_NETMAP */

	VTNET_TXQ_LOCK(txq);

	if ((ifp->if_drv_flags & IFF_DRV_RUNNING) == 0) {
		VTNET_TXQ_UNLOCK(txq);
		return;
	}

	vtnet_txq_eof(txq);
	vtnet_txq_start(txq);

	VTNET_TXQ_UNLOCK(txq);
}
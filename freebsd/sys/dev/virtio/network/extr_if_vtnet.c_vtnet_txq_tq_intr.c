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
struct vtnet_txq {struct vtnet_softc* vtntx_sc; } ;
struct vtnet_softc {struct ifnet* vtnet_ifp; } ;
struct ifnet {int if_drv_flags; } ;

/* Variables and functions */
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  VTNET_TXQ_LOCK (struct vtnet_txq*) ; 
 int /*<<< orphan*/  VTNET_TXQ_UNLOCK (struct vtnet_txq*) ; 
 int /*<<< orphan*/  vtnet_txq_eof (struct vtnet_txq*) ; 
 int /*<<< orphan*/  vtnet_txq_start (struct vtnet_txq*) ; 

__attribute__((used)) static void
vtnet_txq_tq_intr(void *xtxq, int pending)
{
	struct vtnet_softc *sc;
	struct vtnet_txq *txq;
	struct ifnet *ifp;

	txq = xtxq;
	sc = txq->vtntx_sc;
	ifp = sc->vtnet_ifp;

	VTNET_TXQ_LOCK(txq);

	if ((ifp->if_drv_flags & IFF_DRV_RUNNING) == 0) {
		VTNET_TXQ_UNLOCK(txq);
		return;
	}

	vtnet_txq_eof(txq);
	vtnet_txq_start(txq);

	VTNET_TXQ_UNLOCK(txq);
}
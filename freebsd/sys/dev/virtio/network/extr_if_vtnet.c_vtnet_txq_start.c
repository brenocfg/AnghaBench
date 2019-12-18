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
struct vtnet_txq {int /*<<< orphan*/  vtntx_br; struct vtnet_softc* vtntx_sc; } ;
struct vtnet_softc {struct ifnet* vtnet_ifp; } ;
struct ifnet {int /*<<< orphan*/  if_snd; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFQ_DRV_IS_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drbr_empty (struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtnet_start_locked (struct vtnet_txq*,struct ifnet*) ; 
 int /*<<< orphan*/  vtnet_txq_mq_start_locked (struct vtnet_txq*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
vtnet_txq_start(struct vtnet_txq *txq)
{
	struct vtnet_softc *sc;
	struct ifnet *ifp;

	sc = txq->vtntx_sc;
	ifp = sc->vtnet_ifp;

#ifdef VTNET_LEGACY_TX
	if (!IFQ_DRV_IS_EMPTY(&ifp->if_snd))
		vtnet_start_locked(txq, ifp);
#else
	if (!drbr_empty(ifp, txq->vtntx_br))
		vtnet_txq_mq_start_locked(txq, NULL);
#endif
}
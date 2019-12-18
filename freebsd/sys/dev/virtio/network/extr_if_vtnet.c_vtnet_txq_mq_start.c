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
struct vtnet_txq {int /*<<< orphan*/  vtntx_defrtask; int /*<<< orphan*/  vtntx_tq; int /*<<< orphan*/  vtntx_br; } ;
struct vtnet_softc {int vtnet_act_vq_pairs; struct vtnet_txq* vtnet_txqs; } ;
struct TYPE_2__ {int flowid; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;
struct ifnet {struct vtnet_softc* if_softc; } ;

/* Variables and functions */
 scalar_t__ M_HASHTYPE_GET (struct mbuf*) ; 
 scalar_t__ M_HASHTYPE_NONE ; 
 scalar_t__ VTNET_TXQ_TRYLOCK (struct vtnet_txq*) ; 
 int /*<<< orphan*/  VTNET_TXQ_UNLOCK (struct vtnet_txq*) ; 
 int curcpu ; 
 int drbr_enqueue (struct ifnet*,int /*<<< orphan*/ ,struct mbuf*) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int vtnet_txq_mq_start_locked (struct vtnet_txq*,struct mbuf*) ; 

__attribute__((used)) static int
vtnet_txq_mq_start(struct ifnet *ifp, struct mbuf *m)
{
	struct vtnet_softc *sc;
	struct vtnet_txq *txq;
	int i, npairs, error;

	sc = ifp->if_softc;
	npairs = sc->vtnet_act_vq_pairs;

	/* check if flowid is set */
	if (M_HASHTYPE_GET(m) != M_HASHTYPE_NONE)
		i = m->m_pkthdr.flowid % npairs;
	else
		i = curcpu % npairs;

	txq = &sc->vtnet_txqs[i];

	if (VTNET_TXQ_TRYLOCK(txq) != 0) {
		error = vtnet_txq_mq_start_locked(txq, m);
		VTNET_TXQ_UNLOCK(txq);
	} else {
		error = drbr_enqueue(ifp, txq->vtntx_br, m);
		taskqueue_enqueue(txq->vtntx_tq, &txq->vtntx_defrtask);
	}

	return (error);
}
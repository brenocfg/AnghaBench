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
struct vtnet_txq {int /*<<< orphan*/  vtntx_br; } ;
struct vtnet_softc {int vtnet_act_vq_pairs; struct vtnet_txq* vtnet_txqs; } ;
struct mbuf {int dummy; } ;
struct ifnet {struct vtnet_softc* if_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  VTNET_TXQ_LOCK (struct vtnet_txq*) ; 
 int /*<<< orphan*/  VTNET_TXQ_UNLOCK (struct vtnet_txq*) ; 
 struct mbuf* buf_ring_dequeue_sc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_qflush (struct ifnet*) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 

__attribute__((used)) static void
vtnet_qflush(struct ifnet *ifp)
{
	struct vtnet_softc *sc;
	struct vtnet_txq *txq;
	struct mbuf *m;
	int i;

	sc = ifp->if_softc;

	for (i = 0; i < sc->vtnet_act_vq_pairs; i++) {
		txq = &sc->vtnet_txqs[i];

		VTNET_TXQ_LOCK(txq);
		while ((m = buf_ring_dequeue_sc(txq->vtntx_br)) != NULL)
			m_freem(m);
		VTNET_TXQ_UNLOCK(txq);
	}

	if_qflush(ifp);
}
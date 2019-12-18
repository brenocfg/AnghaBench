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
struct netfront_txq {int /*<<< orphan*/  br; } ;
struct netfront_info {int num_queues; struct netfront_txq* txq; } ;
struct mbuf {int dummy; } ;
struct ifnet {struct netfront_info* if_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  XN_TX_LOCK (struct netfront_txq*) ; 
 int /*<<< orphan*/  XN_TX_UNLOCK (struct netfront_txq*) ; 
 struct mbuf* buf_ring_dequeue_sc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_qflush (struct ifnet*) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 

__attribute__((used)) static void
xn_qflush(struct ifnet *ifp)
{
	struct netfront_info *np;
	struct netfront_txq *txq;
	struct mbuf *m;
	int i;

	np = ifp->if_softc;

	for (i = 0; i < np->num_queues; i++) {
		txq = &np->txq[i];

		XN_TX_LOCK(txq);
		while ((m = buf_ring_dequeue_sc(txq->br)) != NULL)
			m_freem(m);
		XN_TX_UNLOCK(txq);
	}

	if_qflush(ifp);
}
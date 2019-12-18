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
struct netfront_txq {int /*<<< orphan*/  defrtask; int /*<<< orphan*/  tq; int /*<<< orphan*/  br; } ;
struct netfront_info {int num_queues; struct netfront_txq* txq; } ;
struct TYPE_2__ {int flowid; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;
struct ifnet {struct netfront_info* if_softc; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ M_HASHTYPE_GET (struct mbuf*) ; 
 scalar_t__ M_HASHTYPE_NONE ; 
 scalar_t__ XN_TX_TRYLOCK (struct netfront_txq*) ; 
 int /*<<< orphan*/  XN_TX_UNLOCK (struct netfront_txq*) ; 
 int curcpu ; 
 int drbr_enqueue (struct ifnet*,int /*<<< orphan*/ ,struct mbuf*) ; 
 int /*<<< orphan*/  netfront_carrier_ok (struct netfront_info*) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int xn_txq_mq_start_locked (struct netfront_txq*,struct mbuf*) ; 

__attribute__((used)) static int
xn_txq_mq_start(struct ifnet *ifp, struct mbuf *m)
{
	struct netfront_info *np;
	struct netfront_txq *txq;
	int i, npairs, error;

	np = ifp->if_softc;
	npairs = np->num_queues;

	if (!netfront_carrier_ok(np))
		return (ENOBUFS);

	KASSERT(npairs != 0, ("called with 0 available queues"));

	/* check if flowid is set */
	if (M_HASHTYPE_GET(m) != M_HASHTYPE_NONE)
		i = m->m_pkthdr.flowid % npairs;
	else
		i = curcpu % npairs;

	txq = &np->txq[i];

	if (XN_TX_TRYLOCK(txq) != 0) {
		error = xn_txq_mq_start_locked(txq, m);
		XN_TX_UNLOCK(txq);
	} else {
		error = drbr_enqueue(ifp, txq->br, m);
		taskqueue_enqueue(txq->tq, &txq->defrtask);
	}

	return (error);
}
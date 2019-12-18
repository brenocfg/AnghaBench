#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sge_qset {TYPE_5__* txq; } ;
struct TYPE_6__ {int /*<<< orphan*/  link_ok; } ;
struct port_info {int first_qset; int nqsets; TYPE_4__* adapter; TYPE_1__ link_config; } ;
struct TYPE_7__ {int flowid; } ;
struct mbuf {TYPE_2__ m_pkthdr; } ;
struct ifnet {int if_drv_flags; struct port_info* if_softc; } ;
struct TYPE_10__ {int /*<<< orphan*/  txq_mr; } ;
struct TYPE_8__ {struct sge_qset* qs; } ;
struct TYPE_9__ {TYPE_3__ sge; } ;

/* Variables and functions */
 int IFF_DRV_RUNNING ; 
 scalar_t__ M_HASHTYPE_GET (struct mbuf*) ; 
 scalar_t__ M_HASHTYPE_NONE ; 
 size_t TXQ_ETH ; 
 scalar_t__ TXQ_TRYLOCK (struct sge_qset*) ; 
 int /*<<< orphan*/  TXQ_UNLOCK (struct sge_qset*) ; 
 int cxgb_transmit_locked (struct ifnet*,struct sge_qset*,struct mbuf*) ; 
 int drbr_enqueue (struct ifnet*,int /*<<< orphan*/ ,struct mbuf*) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 

int
cxgb_transmit(struct ifnet *ifp, struct mbuf *m)
{
	struct sge_qset *qs;
	struct port_info *pi = ifp->if_softc;
	int error, qidx = pi->first_qset;

	if ((ifp->if_drv_flags & IFF_DRV_RUNNING) == 0
	    ||(!pi->link_config.link_ok)) {
		m_freem(m);
		return (0);
	}

	/* check if flowid is set */
	if (M_HASHTYPE_GET(m) != M_HASHTYPE_NONE)	
		qidx = (m->m_pkthdr.flowid % pi->nqsets) + pi->first_qset;

	qs = &pi->adapter->sge.qs[qidx];
	
	if (TXQ_TRYLOCK(qs)) {
		/* XXX running */
		error = cxgb_transmit_locked(ifp, qs, m);
		TXQ_UNLOCK(qs);
	} else
		error = drbr_enqueue(ifp, qs->txq[TXQ_ETH].txq_mr, m);
	return (error);
}
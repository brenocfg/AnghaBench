#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  c_cpu; } ;
struct sge_txq {scalar_t__ size; scalar_t__ in_use; TYPE_2__ txq_timer; scalar_t__ db_pending; } ;
struct sge_qset {int qs_flags; struct port_info* port; struct sge_txq* txq; } ;
struct TYPE_4__ {scalar_t__ link_ok; } ;
struct port_info {TYPE_1__ link_config; int /*<<< orphan*/  adapter; struct ifnet* ifp; } ;
struct mbuf {int dummy; } ;
struct ifnet {int if_drv_flags; } ;

/* Variables and functions */
 int IFF_DRV_RUNNING ; 
 int QS_FLUSHING ; 
 int QS_TIMEOUT ; 
 size_t TXQ_ETH ; 
 int /*<<< orphan*/  TXQ_LOCK_ASSERT (struct sge_qset*) ; 
 int /*<<< orphan*/  TXQ_RING_EMPTY (struct sge_qset*) ; 
 int /*<<< orphan*/  TXQ_RING_FLUSH (struct sge_qset*) ; 
 scalar_t__ TX_MAX_DESC ; 
 scalar_t__ callout_pending (TYPE_2__*) ; 
 int /*<<< orphan*/  callout_reset_on (TYPE_2__*,int,int /*<<< orphan*/ ,struct sge_qset*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_ring_tx_db (int /*<<< orphan*/ ,struct sge_txq*,int) ; 
 struct mbuf* cxgb_dequeue (struct sge_qset*) ; 
 int /*<<< orphan*/  cxgb_tx_reclaim_threshold ; 
 int /*<<< orphan*/  cxgb_tx_timeout ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  reclaim_completed_tx (struct sge_qset*,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ t3_encap (struct sge_qset*,struct mbuf**) ; 

__attribute__((used)) static void
cxgb_start_locked(struct sge_qset *qs)
{
	struct mbuf *m_head = NULL;
	struct sge_txq *txq = &qs->txq[TXQ_ETH];
	struct port_info *pi = qs->port;
	struct ifnet *ifp = pi->ifp;

	if (qs->qs_flags & (QS_FLUSHING|QS_TIMEOUT))
		reclaim_completed_tx(qs, 0, TXQ_ETH);

	if (!pi->link_config.link_ok) {
		TXQ_RING_FLUSH(qs);
		return;
	}
	TXQ_LOCK_ASSERT(qs);
	while (!TXQ_RING_EMPTY(qs) && (ifp->if_drv_flags & IFF_DRV_RUNNING) &&
	    pi->link_config.link_ok) {
		reclaim_completed_tx(qs, cxgb_tx_reclaim_threshold, TXQ_ETH);

		if (txq->size - txq->in_use <= TX_MAX_DESC)
			break;

		if ((m_head = cxgb_dequeue(qs)) == NULL)
			break;
		/*
		 *  Encapsulation can modify our pointer, and or make it
		 *  NULL on failure.  In that event, we can't requeue.
		 */
		if (t3_encap(qs, &m_head) || m_head == NULL)
			break;

		m_head = NULL;
	}

	if (txq->db_pending)
		check_ring_tx_db(pi->adapter, txq, 1);

	if (!TXQ_RING_EMPTY(qs) && callout_pending(&txq->txq_timer) == 0 &&
	    pi->link_config.link_ok)
		callout_reset_on(&txq->txq_timer, 1, cxgb_tx_timeout,
		    qs, txq->txq_timer.c_cpu);
	if (m_head != NULL)
		m_freem(m_head);
}
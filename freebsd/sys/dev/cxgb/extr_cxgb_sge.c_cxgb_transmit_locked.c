#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  c_cpu; } ;
struct sge_txq {int size; int in_use; TYPE_3__ txq_timer; int /*<<< orphan*/  txq_direct_bytes; int /*<<< orphan*/  txq_direct_packets; scalar_t__ db_pending; struct buf_ring* txq_mr; } ;
struct sge_qset {struct sge_txq* txq; struct port_info* port; } ;
struct TYPE_6__ {scalar_t__ link_ok; } ;
struct port_info {TYPE_2__ link_config; int /*<<< orphan*/  adapter; } ;
struct TYPE_5__ {scalar_t__ len; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;
struct ifnet {int dummy; } ;
struct buf_ring {int dummy; } ;

/* Variables and functions */
 size_t TXQ_ETH ; 
 int /*<<< orphan*/  TXQ_LOCK_ASSERT (struct sge_qset*) ; 
 int /*<<< orphan*/  TXQ_RING_EMPTY (struct sge_qset*) ; 
 int /*<<< orphan*/  TXQ_RING_NEEDS_ENQUEUE (struct sge_qset*) ; 
 int TX_MAX_DESC ; 
 int /*<<< orphan*/  callout_pending (TYPE_3__*) ; 
 int /*<<< orphan*/  callout_reset_on (TYPE_3__*,int,int /*<<< orphan*/ ,struct sge_qset*,int /*<<< orphan*/ ) ; 
 scalar_t__ check_pkt_coalesce (struct sge_qset*) ; 
 int /*<<< orphan*/  check_ring_tx_db (int /*<<< orphan*/ ,struct sge_txq*,int) ; 
 int /*<<< orphan*/  cxgb_start_locked (struct sge_qset*) ; 
 int /*<<< orphan*/  cxgb_tx_reclaim_threshold ; 
 int /*<<< orphan*/  cxgb_tx_timeout ; 
 int drbr_enqueue (struct ifnet*,struct buf_ring*,struct mbuf*) ; 
 int drbr_inuse (struct ifnet*,struct buf_ring*) ; 
 int /*<<< orphan*/  reclaim_completed_tx (struct sge_qset*,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ t3_encap (struct sge_qset*,struct mbuf**) ; 

__attribute__((used)) static int
cxgb_transmit_locked(struct ifnet *ifp, struct sge_qset *qs, struct mbuf *m)
{
	struct port_info *pi = qs->port;
	struct sge_txq *txq = &qs->txq[TXQ_ETH];
	struct buf_ring *br = txq->txq_mr;
	int error, avail;

	avail = txq->size - txq->in_use;
	TXQ_LOCK_ASSERT(qs);

	/*
	 * We can only do a direct transmit if the following are true:
	 * - we aren't coalescing (ring < 3/4 full)
	 * - the link is up -- checked in caller
	 * - there are no packets enqueued already
	 * - there is space in hardware transmit queue 
	 */
	if (check_pkt_coalesce(qs) == 0 &&
	    !TXQ_RING_NEEDS_ENQUEUE(qs) && avail > TX_MAX_DESC) {
		if (t3_encap(qs, &m)) {
			if (m != NULL &&
			    (error = drbr_enqueue(ifp, br, m)) != 0) 
				return (error);
		} else {
			if (txq->db_pending)
				check_ring_tx_db(pi->adapter, txq, 1);

			/*
			 * We've bypassed the buf ring so we need to update
			 * the stats directly
			 */
			txq->txq_direct_packets++;
			txq->txq_direct_bytes += m->m_pkthdr.len;
		}
	} else if ((error = drbr_enqueue(ifp, br, m)) != 0)
		return (error);

	reclaim_completed_tx(qs, cxgb_tx_reclaim_threshold, TXQ_ETH);
	if (!TXQ_RING_EMPTY(qs) && pi->link_config.link_ok &&
	    (!check_pkt_coalesce(qs) || (drbr_inuse(ifp, br) >= 7)))
		cxgb_start_locked(qs);
	else if (!TXQ_RING_EMPTY(qs) && !callout_pending(&txq->txq_timer))
		callout_reset_on(&txq->txq_timer, 1, cxgb_tx_timeout,
		    qs, txq->txq_timer.c_cpu);
	return (0);
}
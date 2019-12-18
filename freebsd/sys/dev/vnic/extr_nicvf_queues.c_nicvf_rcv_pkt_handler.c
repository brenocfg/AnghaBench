#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ lro_cnt; } ;
struct rcv_queue {TYPE_3__ lro; scalar_t__ lro_enabled; } ;
struct nicvf {int /*<<< orphan*/  dev; TYPE_1__* qs; } ;
struct TYPE_5__ {int csum_flags; } ;
struct mbuf {TYPE_2__ m_pkthdr; } ;
struct cqe_rx_t {int rq_idx; scalar_t__ l3_type; scalar_t__ l4_type; int /*<<< orphan*/  rb_cnt; } ;
struct cmp_queue {int /*<<< orphan*/  rx_br; } ;
struct TYPE_4__ {struct rcv_queue* rq; } ;

/* Variables and functions */
 int CSUM_DATA_VALID ; 
 int CSUM_PSEUDO_HDR ; 
 scalar_t__ L3TYPE_IPV4 ; 
 scalar_t__ L4TYPE_TCP ; 
 int buf_ring_enqueue (int /*<<< orphan*/ ,struct mbuf*) ; 
 int /*<<< orphan*/  dprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int nicvf_check_cqe_rx_errs (struct nicvf*,struct cmp_queue*,struct cqe_rx_t*) ; 
 struct mbuf* nicvf_get_rcv_mbuf (struct nicvf*,struct cqe_rx_t*) ; 
 scalar_t__ tcp_lro_rx (TYPE_3__*,struct mbuf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nicvf_rcv_pkt_handler(struct nicvf *nic, struct cmp_queue *cq,
    struct cqe_rx_t *cqe_rx, int cqe_type)
{
	struct mbuf *mbuf;
	struct rcv_queue *rq;
	int rq_idx;
	int err = 0;

	rq_idx = cqe_rx->rq_idx;
	rq = &nic->qs->rq[rq_idx];

	/* Check for errors */
	err = nicvf_check_cqe_rx_errs(nic, cq, cqe_rx);
	if (err && !cqe_rx->rb_cnt)
		return (0);

	mbuf = nicvf_get_rcv_mbuf(nic, cqe_rx);
	if (mbuf == NULL) {
		dprintf(nic->dev, "Packet not received\n");
		return (0);
	}

	/* If error packet */
	if (err != 0) {
		m_freem(mbuf);
		return (0);
	}

	if (rq->lro_enabled &&
	    ((cqe_rx->l3_type == L3TYPE_IPV4) && (cqe_rx->l4_type == L4TYPE_TCP)) &&
	    (mbuf->m_pkthdr.csum_flags & (CSUM_DATA_VALID | CSUM_PSEUDO_HDR)) ==
            (CSUM_DATA_VALID | CSUM_PSEUDO_HDR)) {
		/*
		 * At this point it is known that there are no errors in the
		 * packet. Attempt to LRO enqueue. Send to stack if no resources
		 * or enqueue error.
		 */
		if ((rq->lro.lro_cnt != 0) &&
		    (tcp_lro_rx(&rq->lro, mbuf, 0) == 0))
			return (0);
	}
	/*
	 * Push this packet to the stack later to avoid
	 * unlocking completion task in the middle of work.
	 */
	err = buf_ring_enqueue(cq->rx_br, mbuf);
	if (err != 0) {
		/*
		 * Failed to enqueue this mbuf.
		 * We don't drop it, just schedule another task.
		 */
		return (err);
	}

	return (0);
}
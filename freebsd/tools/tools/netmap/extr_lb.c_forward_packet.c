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
typedef  size_t uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  drop_bytes; int /*<<< orphan*/  drop; int /*<<< orphan*/  pkts; int /*<<< orphan*/  bytes; } ;
struct port_des {TYPE_1__ ctr; struct overflow_queue* oq; struct netmap_ring* ring; } ;
struct overflow_queue {size_t n; } ;
struct netmap_slot {size_t ptr; size_t buf_idx; scalar_t__ len; int /*<<< orphan*/  flags; } ;
struct netmap_ring {size_t head; size_t tail; struct netmap_slot* slot; } ;
struct group_des {size_t nports; struct port_des* ports; } ;
struct TYPE_6__ {size_t output_rings; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 size_t BUF_REVOKE ; 
 int /*<<< orphan*/  ND (int,char*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NS_BUF_CHANGED ; 
 int /*<<< orphan*/  dropped ; 
 int /*<<< orphan*/  forwarded ; 
 struct overflow_queue* freeq ; 
 TYPE_3__ glob_arg ; 
 TYPE_2__* lq ; 
 size_t nm_ring_next (struct netmap_ring*,size_t) ; 
 struct netmap_slot oq_deq (struct overflow_queue*) ; 
 scalar_t__ oq_empty (struct overflow_queue*) ; 
 int /*<<< orphan*/  oq_enq (struct overflow_queue*,struct netmap_slot*) ; 
 scalar_t__ oq_full (struct overflow_queue*) ; 
 struct port_des* ports ; 

uint32_t forward_packet(struct group_des *g, struct netmap_slot *rs)
{
	uint32_t hash = rs->ptr;
	uint32_t output_port = hash % g->nports;
	struct port_des *port = &g->ports[output_port];
	struct netmap_ring *ring = port->ring;
	struct overflow_queue *q = port->oq;

	/* Move the packet to the output pipe, unless there is
	 * either no space left on the ring, or there is some
	 * packet still in the overflow queue (since those must
	 * take precedence over the new one)
	*/
	if (ring->head != ring->tail && (q == NULL || oq_empty(q))) {
		struct netmap_slot *ts = &ring->slot[ring->head];
		struct netmap_slot old_slot = *ts;

		ts->buf_idx = rs->buf_idx;
		ts->len = rs->len;
		ts->flags |= NS_BUF_CHANGED;
		ts->ptr = rs->ptr;
		ring->head = nm_ring_next(ring, ring->head);
		port->ctr.bytes += rs->len;
		port->ctr.pkts++;
		forwarded++;
		return old_slot.buf_idx;
	}

	/* use the overflow queue, if available */
	if (q == NULL || oq_full(q)) {
		/* no space left on the ring and no overflow queue
		 * available: we are forced to drop the packet
		 */
		dropped++;
		port->ctr.drop++;
		port->ctr.drop_bytes += rs->len;
		return rs->buf_idx;
	}

	oq_enq(q, rs);

	/*
	 * we cannot continue down the chain and we need to
	 * return a free buffer now. We take it from the free queue.
	 */
	if (oq_empty(freeq)) {
		/* the free queue is empty. Revoke some buffers
		 * from the longest overflow queue
		 */
		uint32_t j;
		struct port_des *lp = &ports[0];
		uint32_t max = lp->oq->n;

		/* let lp point to the port with the longest queue */
		for (j = 1; j < glob_arg.output_rings; j++) {
			struct port_des *cp = &ports[j];
			if (cp->oq->n > max) {
				lp = cp;
				max = cp->oq->n;
			}
		}

		/* move the oldest BUF_REVOKE buffers from the
		 * lp queue to the free queue
		 */
		// XXX optimize this cycle
		for (j = 0; lp->oq->n && j < BUF_REVOKE; j++) {
			struct netmap_slot tmp = oq_deq(lp->oq);

			dropped++;
			lp->ctr.drop++;
			lp->ctr.drop_bytes += tmp.len;

			oq_enq(freeq, &tmp);
		}

		ND(1, "revoked %d buffers from %s", j, lq->name);
	}

	return oq_deq(freeq).buf_idx;
}
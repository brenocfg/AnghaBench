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
typedef  size_t u_int ;
struct netmap_slot {int flags; int /*<<< orphan*/  len; int /*<<< orphan*/  buf_idx; } ;
struct netmap_ring {size_t head; size_t cur; struct netmap_slot* slot; } ;
struct netmap_kring {size_t nr_hwcur; size_t rhead; size_t nkr_num_slots; struct netmap_ring* ring; } ;
struct netmap_adapter {size_t num_rx_rings; size_t num_tx_rings; struct netmap_kring** tx_rings; struct netmap_kring** rx_rings; } ;

/* Variables and functions */
 void* NS_BUF_CHANGED ; 
 int NS_FORWARD ; 
 int /*<<< orphan*/  netmap_fwd ; 
 void* nm_next (size_t,size_t const) ; 
 int /*<<< orphan*/  nm_ring_empty (struct netmap_ring*) ; 

__attribute__((used)) static u_int
netmap_sw_to_nic(struct netmap_adapter *na)
{
	struct netmap_kring *kring = na->rx_rings[na->num_rx_rings];
	struct netmap_slot *rxslot = kring->ring->slot;
	u_int i, rxcur = kring->nr_hwcur;
	u_int const head = kring->rhead;
	u_int const src_lim = kring->nkr_num_slots - 1;
	u_int sent = 0;

	/* scan rings to find space, then fill as much as possible */
	for (i = 0; i < na->num_tx_rings; i++) {
		struct netmap_kring *kdst = na->tx_rings[i];
		struct netmap_ring *rdst = kdst->ring;
		u_int const dst_lim = kdst->nkr_num_slots - 1;

		/* XXX do we trust ring or kring->rcur,rtail ? */
		for (; rxcur != head && !nm_ring_empty(rdst);
		     rxcur = nm_next(rxcur, src_lim) ) {
			struct netmap_slot *src, *dst, tmp;
			u_int dst_head = rdst->head;

			src = &rxslot[rxcur];
			if ((src->flags & NS_FORWARD) == 0 && !netmap_fwd)
				continue;

			sent++;

			dst = &rdst->slot[dst_head];

			tmp = *src;

			src->buf_idx = dst->buf_idx;
			src->flags = NS_BUF_CHANGED;

			dst->buf_idx = tmp.buf_idx;
			dst->len = tmp.len;
			dst->flags = NS_BUF_CHANGED;

			rdst->head = rdst->cur = nm_next(dst_head, dst_lim);
		}
		/* if (sent) XXX txsync ? it would be just an optimization */
	}
	return sent;
}
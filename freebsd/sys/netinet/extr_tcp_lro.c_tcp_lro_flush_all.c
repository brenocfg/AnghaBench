#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long long uint64_t ;
struct mbuf {int dummy; } ;
struct lro_ctrl {unsigned int lro_mbuf_count; int /*<<< orphan*/  lro_flushed; int /*<<< orphan*/  lro_queued; TYPE_2__* ifp; TYPE_1__* lro_mbuf_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* if_input ) (TYPE_2__*,struct mbuf*) ;} ;
struct TYPE_3__ {unsigned long long seq; struct mbuf* mb; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_2__*,struct mbuf*) ; 
 scalar_t__ tcp_lro_rx2 (struct lro_ctrl*,struct mbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_lro_rx_done (struct lro_ctrl*) ; 
 int /*<<< orphan*/  tcp_lro_sort (TYPE_1__*,unsigned int) ; 

void
tcp_lro_flush_all(struct lro_ctrl *lc)
{
	uint64_t seq;
	uint64_t nseq;
	unsigned x;

	/* check if no mbufs to flush */
	if (lc->lro_mbuf_count == 0)
		goto done;

	/* sort all mbufs according to stream */
	tcp_lro_sort(lc->lro_mbuf_data, lc->lro_mbuf_count);

	/* input data into LRO engine, stream by stream */
	seq = 0;
	for (x = 0; x != lc->lro_mbuf_count; x++) {
		struct mbuf *mb;

		/* get mbuf */
		mb = lc->lro_mbuf_data[x].mb;

		/* get sequence number, masking away the packet index */
		nseq = lc->lro_mbuf_data[x].seq & (-1ULL << 24);

		/* check for new stream */
		if (seq != nseq) {
			seq = nseq;

			/* flush active streams */
			tcp_lro_rx_done(lc);
		}

		/* add packet to LRO engine */
		if (tcp_lro_rx2(lc, mb, 0, 0) != 0) {
			/* input packet to network layer */
			(*lc->ifp->if_input)(lc->ifp, mb);
			lc->lro_queued++;
			lc->lro_flushed++;
		}
	}
done:
	/* flush active streams */
	tcp_lro_rx_done(lc);

	lc->lro_mbuf_count = 0;
}
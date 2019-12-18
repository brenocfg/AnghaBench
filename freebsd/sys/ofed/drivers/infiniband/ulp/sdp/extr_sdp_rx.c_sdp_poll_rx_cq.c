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
struct TYPE_2__ {struct ib_cq* cq; } ;
struct sdp_sock {TYPE_1__ rx_ring; } ;
struct mbuf {int dummy; } ;
struct ib_wc {int wr_id; } ;
struct ib_cq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int SDP_NUM_WC ; 
 int SDP_OP_RECV ; 
 int ib_poll_cq (struct ib_cq*,int,struct ib_wc*) ; 
 int /*<<< orphan*/  sdp_bzcopy_write_space (struct sdp_sock*) ; 
 int /*<<< orphan*/  sdp_process_rx_mb (struct sdp_sock*,struct mbuf*) ; 
 struct mbuf* sdp_process_rx_wc (struct sdp_sock*,struct ib_wc*) ; 

__attribute__((used)) static int
sdp_poll_rx_cq(struct sdp_sock *ssk)
{
	struct ib_cq *cq = ssk->rx_ring.cq;
	struct ib_wc ibwc[SDP_NUM_WC];
	int n, i;
	int wc_processed = 0;
	struct mbuf *mb;

	do {
		n = ib_poll_cq(cq, SDP_NUM_WC, ibwc);
		for (i = 0; i < n; ++i) {
			struct ib_wc *wc = &ibwc[i];

			BUG_ON(!(wc->wr_id & SDP_OP_RECV));
			mb = sdp_process_rx_wc(ssk, wc);
			if (!mb)
				continue;

			sdp_process_rx_mb(ssk, mb);
			wc_processed++;
		}
	} while (n == SDP_NUM_WC);

	if (wc_processed)
		sdp_bzcopy_write_space(ssk);

	return wc_processed;
}
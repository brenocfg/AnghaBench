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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  cq; } ;
struct sdp_sock {int /*<<< orphan*/  socket; TYPE_1__ tx_ring; } ;
struct ib_wc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_NOWAIT ; 
 int SDP_NUM_WC ; 
 int /*<<< orphan*/  SDP_WLOCK_ASSERT (struct sdp_sock*) ; 
 int ib_poll_cq (int /*<<< orphan*/ ,int,struct ib_wc*) ; 
 int /*<<< orphan*/  sdp_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sdp_post_sends (struct sdp_sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdp_prf1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdp_process_tx_wc (struct sdp_sock*,struct ib_wc*) ; 
 int /*<<< orphan*/  sk ; 
 int /*<<< orphan*/  sowwakeup (int /*<<< orphan*/ ) ; 
 scalar_t__ tx_ring_posted (struct sdp_sock*) ; 

__attribute__((used)) static int
sdp_process_tx_cq(struct sdp_sock *ssk)
{
	struct ib_wc ibwc[SDP_NUM_WC];
	int n, i;
	int wc_processed = 0;

	SDP_WLOCK_ASSERT(ssk);

	if (!ssk->tx_ring.cq) {
		sdp_dbg(ssk->socket, "tx irq on destroyed tx_cq\n");
		return 0;
	}

	do {
		n = ib_poll_cq(ssk->tx_ring.cq, SDP_NUM_WC, ibwc);
		for (i = 0; i < n; ++i) {
			sdp_process_tx_wc(ssk, ibwc + i);
			wc_processed++;
		}
	} while (n == SDP_NUM_WC);

	if (wc_processed) {
		sdp_post_sends(ssk, M_NOWAIT);
		sdp_prf1(sk, NULL, "Waking sendmsg. inflight=%d", 
				(u32) tx_ring_posted(ssk));
		sowwakeup(ssk->socket);
	}

	return wc_processed;
}
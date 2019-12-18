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
typedef  scalar_t__ u32 ;
struct socket {int dummy; } ;
struct TYPE_5__ {TYPE_1__* rdma_inflight; int /*<<< orphan*/  timer; } ;
struct sdp_sock {scalar_t__ state; TYPE_2__ tx_ring; struct socket* socket; } ;
struct TYPE_4__ {scalar_t__ busy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDPSTATS_COUNTER_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDP_TX_POLL_TIMEOUT ; 
 scalar_t__ TCPS_CLOSED ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sdp_sock*) ; 
 int /*<<< orphan*/  ring_head (TYPE_2__) ; 
 int /*<<< orphan*/  ring_tail (TYPE_2__) ; 
 int /*<<< orphan*/  sdp_arm_tx_cq (struct sdp_sock*) ; 
 int /*<<< orphan*/  sdp_poll_tx_timeout ; 
 int /*<<< orphan*/  sdp_prf1 (struct socket*,int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ sdp_process_tx_cq (struct sdp_sock*) ; 
 int /*<<< orphan*/  sdp_warn (struct socket*,char*) ; 
 int /*<<< orphan*/  tx_poll_hit ; 
 int /*<<< orphan*/  tx_poll_miss ; 
 scalar_t__ tx_ring_posted (struct sdp_sock*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void
sdp_poll_tx(struct sdp_sock *ssk)
{
	struct socket *sk = ssk->socket;
	u32 inflight, wc_processed;

	sdp_prf1(ssk->socket, NULL, "TX timeout: inflight=%d, head=%d tail=%d", 
		(u32) tx_ring_posted(ssk),
		ring_head(ssk->tx_ring), ring_tail(ssk->tx_ring));

	if (unlikely(ssk->state == TCPS_CLOSED)) {
		sdp_warn(sk, "Socket is closed\n");
		goto out;
	}

	wc_processed = sdp_process_tx_cq(ssk);
	if (!wc_processed)
		SDPSTATS_COUNTER_INC(tx_poll_miss);
	else
		SDPSTATS_COUNTER_INC(tx_poll_hit);

	inflight = (u32) tx_ring_posted(ssk);
	sdp_prf1(ssk->socket, NULL, "finished tx processing. inflight = %d",
	    inflight);

	/* If there are still packets in flight and the timer has not already
	 * been scheduled by the Tx routine then schedule it here to guarantee
	 * completion processing of these packets */
	if (inflight)
		callout_reset(&ssk->tx_ring.timer, SDP_TX_POLL_TIMEOUT,
		    sdp_poll_tx_timeout, ssk);
out:
#ifdef SDP_ZCOPY
	if (ssk->tx_ring.rdma_inflight && ssk->tx_ring.rdma_inflight->busy) {
		sdp_prf1(sk, NULL, "RDMA is inflight - arming irq");
		sdp_arm_tx_cq(ssk);
	}
#endif
	return;
}
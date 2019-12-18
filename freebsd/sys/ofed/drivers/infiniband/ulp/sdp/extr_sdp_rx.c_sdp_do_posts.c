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
struct socket {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  cq; } ;
struct TYPE_3__ {int /*<<< orphan*/  cq; } ;
struct sdp_sock {scalar_t__ state; TYPE_2__ tx_ring; TYPE_1__ rx_ring; int /*<<< orphan*/  rxctlq; int /*<<< orphan*/  qp_active; struct socket* socket; } ;
struct mbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_NOWAIT ; 
 scalar_t__ SDP_MIN_TX_CREDITS ; 
 int /*<<< orphan*/  SDP_WLOCK_ASSERT (struct sdp_sock*) ; 
 scalar_t__ TCPS_TIME_WAIT ; 
 scalar_t__ credit_update_needed (struct sdp_sock*) ; 
 struct mbuf* mbufq_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdp_dbg (struct socket*,char*) ; 
 int /*<<< orphan*/  sdp_post_recvs (struct sdp_sock*) ; 
 int /*<<< orphan*/  sdp_post_sends (struct sdp_sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdp_prf (struct socket*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  sdp_process_rx_ctl_mb (struct sdp_sock*,struct mbuf*) ; 
 int /*<<< orphan*/  sdp_xmit_poll (struct sdp_sock*,int) ; 
 scalar_t__ tx_credits (struct sdp_sock*) ; 
 scalar_t__ tx_ring_posted (struct sdp_sock*) ; 

void
sdp_do_posts(struct sdp_sock *ssk)
{
	struct socket *sk = ssk->socket;
	int xmit_poll_force;
	struct mbuf *mb;

	SDP_WLOCK_ASSERT(ssk);
	if (!ssk->qp_active) {
		sdp_dbg(sk, "QP is deactivated\n");
		return;
	}

	while ((mb = mbufq_dequeue(&ssk->rxctlq)) != NULL)
		sdp_process_rx_ctl_mb(ssk, mb);

	if (ssk->state == TCPS_TIME_WAIT)
		return;

	if (!ssk->rx_ring.cq || !ssk->tx_ring.cq)
		return;

	sdp_post_recvs(ssk);

	if (tx_ring_posted(ssk))
		sdp_xmit_poll(ssk, 1);

	sdp_post_sends(ssk, M_NOWAIT);

	xmit_poll_force = tx_credits(ssk) < SDP_MIN_TX_CREDITS;

	if (credit_update_needed(ssk) || xmit_poll_force) {
		/* if has pending tx because run out of tx_credits - xmit it */
		sdp_prf(sk, NULL, "Processing to free pending sends");
		sdp_xmit_poll(ssk,  xmit_poll_force);
		sdp_prf(sk, NULL, "Sending credit update");
		sdp_post_sends(ssk, M_NOWAIT);
	}

}
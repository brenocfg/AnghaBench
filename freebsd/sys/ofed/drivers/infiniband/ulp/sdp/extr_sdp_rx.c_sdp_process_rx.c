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
struct sdp_sock {int /*<<< orphan*/  rx_ring; int /*<<< orphan*/  rx_comp_work; int /*<<< orphan*/  socket; } ;

/* Variables and functions */
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rx_comp_wq ; 
 int /*<<< orphan*/  rx_ring_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rx_ring_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdp_arm_rx_cq (struct sdp_sock*) ; 
 int /*<<< orphan*/  sdp_dbg (int /*<<< orphan*/ ,char*) ; 
 int sdp_poll_rx_cq (struct sdp_sock*) ; 
 int /*<<< orphan*/  sdp_prf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int,...) ; 
 int tx_credits (struct sdp_sock*) ; 

int
sdp_process_rx(struct sdp_sock *ssk)
{
	int wc_processed = 0;
	int credits_before;

	if (!rx_ring_trylock(&ssk->rx_ring)) {
		sdp_dbg(ssk->socket, "ring destroyed. not polling it\n");
		return 0;
	}

	credits_before = tx_credits(ssk);

	wc_processed = sdp_poll_rx_cq(ssk);
	sdp_prf(ssk->socket, NULL, "processed %d", wc_processed);

	if (wc_processed) {
		sdp_prf(ssk->socket, NULL, "credits:  %d -> %d",
				credits_before, tx_credits(ssk));
		queue_work(rx_comp_wq, &ssk->rx_comp_work);
	}
	sdp_arm_rx_cq(ssk);

	rx_ring_unlock(&ssk->rx_ring);

	return (wc_processed);
}
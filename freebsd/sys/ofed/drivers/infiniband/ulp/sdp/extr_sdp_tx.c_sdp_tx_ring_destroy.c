#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * cq; int /*<<< orphan*/ * buffer; int /*<<< orphan*/  timer; } ;
struct sdp_sock {TYPE_1__ tx_ring; int /*<<< orphan*/  socket; int /*<<< orphan*/  nagle_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_SDP ; 
 int /*<<< orphan*/  SDP_WLOCK (struct sdp_sock*) ; 
 int /*<<< orphan*/  SDP_WUNLOCK (struct sdp_sock*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ib_destroy_cq (int /*<<< orphan*/ *) ; 
 scalar_t__ ring_head (TYPE_1__) ; 
 scalar_t__ ring_tail (TYPE_1__) ; 
 int /*<<< orphan*/  sdp_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sdp_tx_ring_purge (struct sdp_sock*) ; 
 int /*<<< orphan*/  sdp_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

void
sdp_tx_ring_destroy(struct sdp_sock *ssk)
{

	sdp_dbg(ssk->socket, "tx ring destroy\n");
	SDP_WLOCK(ssk);
	callout_stop(&ssk->tx_ring.timer);
	callout_stop(&ssk->nagle_timer);
	SDP_WUNLOCK(ssk);
	callout_drain(&ssk->tx_ring.timer);
	callout_drain(&ssk->nagle_timer);

	if (ssk->tx_ring.buffer) {
		sdp_tx_ring_purge(ssk);
		free(ssk->tx_ring.buffer, M_SDP);
		ssk->tx_ring.buffer = NULL;
	}

	if (ssk->tx_ring.cq) {
		if (ib_destroy_cq(ssk->tx_ring.cq)) {
			sdp_warn(ssk->socket, "destroy cq(%p) failed\n",
					ssk->tx_ring.cq);
		} else {
			ssk->tx_ring.cq = NULL;
		}
	}

	WARN_ON(ring_head(ssk->tx_ring) != ring_tail(ssk->tx_ring));
}
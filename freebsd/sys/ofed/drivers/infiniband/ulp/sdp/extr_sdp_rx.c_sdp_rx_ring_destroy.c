#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * cq; int /*<<< orphan*/ * buffer; } ;
struct sdp_sock {TYPE_1__ rx_ring; int /*<<< orphan*/  socket; int /*<<< orphan*/  rx_comp_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_SDP ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ib_destroy_cq (int /*<<< orphan*/ *) ; 
 scalar_t__ ring_head (TYPE_1__) ; 
 scalar_t__ ring_tail (TYPE_1__) ; 
 int /*<<< orphan*/  rx_ring_destroy_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  sdp_rx_ring_purge (struct sdp_sock*) ; 
 int /*<<< orphan*/  sdp_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

void
sdp_rx_ring_destroy(struct sdp_sock *ssk)
{

	cancel_work_sync(&ssk->rx_comp_work);
	rx_ring_destroy_lock(&ssk->rx_ring);

	if (ssk->rx_ring.buffer) {
		sdp_rx_ring_purge(ssk);
		free(ssk->rx_ring.buffer, M_SDP);
		ssk->rx_ring.buffer = NULL;
	}

	if (ssk->rx_ring.cq) {
		if (ib_destroy_cq(ssk->rx_ring.cq)) {
			sdp_warn(ssk->socket, "destroy cq(%p) failed\n",
				ssk->rx_ring.cq);
		} else {
			ssk->rx_ring.cq = NULL;
		}
	}

	WARN_ON(ring_head(ssk->rx_ring) != ring_tail(ssk->rx_ring));
}
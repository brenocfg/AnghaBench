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
struct TYPE_2__ {int /*<<< orphan*/  destroyed_lock; } ;
struct sdp_sock {int flags; int /*<<< orphan*/  lock; TYPE_1__ rx_ring; int /*<<< orphan*/ * qp; scalar_t__ qp_active; int /*<<< orphan*/  cred; int /*<<< orphan*/ * socket; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct sdp_sock*,int /*<<< orphan*/ ) ; 
 int SDP_DESTROY ; 
 int /*<<< orphan*/  SDP_LIST_WLOCK () ; 
 int /*<<< orphan*/  SDP_LIST_WUNLOCK () ; 
 int /*<<< orphan*/  SDP_WLOCK_ASSERT (struct sdp_sock*) ; 
 int /*<<< orphan*/  SDP_WUNLOCK (struct sdp_sock*) ; 
 int /*<<< orphan*/  crfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_destroy_qp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list ; 
 int /*<<< orphan*/  rw_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdp_count ; 
 int /*<<< orphan*/  sdp_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  sdp_destroy_cma (struct sdp_sock*) ; 
 int /*<<< orphan*/  sdp_rx_ring_destroy (struct sdp_sock*) ; 
 int /*<<< orphan*/  sdp_tx_ring_destroy (struct sdp_sock*) ; 
 int /*<<< orphan*/  sdp_zone ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct sdp_sock*) ; 

__attribute__((used)) static void
sdp_pcbfree(struct sdp_sock *ssk)
{

	KASSERT(ssk->socket == NULL, ("ssk %p socket still attached", ssk));
	KASSERT((ssk->flags & SDP_DESTROY) == 0,
	    ("ssk %p already destroyed", ssk));

	sdp_dbg(ssk->socket, "Freeing pcb");
	SDP_WLOCK_ASSERT(ssk);
	ssk->flags |= SDP_DESTROY;
	SDP_WUNLOCK(ssk);
	SDP_LIST_WLOCK();
	sdp_count--;
	LIST_REMOVE(ssk, list);
	SDP_LIST_WUNLOCK();
	crfree(ssk->cred);
	ssk->qp_active = 0;
	if (ssk->qp) {
		ib_destroy_qp(ssk->qp);
		ssk->qp = NULL;
	}
	sdp_tx_ring_destroy(ssk);
	sdp_rx_ring_destroy(ssk);
	sdp_destroy_cma(ssk);
	rw_destroy(&ssk->rx_ring.destroyed_lock);
	rw_destroy(&ssk->lock);
	uma_zfree(sdp_zone, ssk);
}
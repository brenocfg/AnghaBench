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
struct sdp_sock {int /*<<< orphan*/  state; scalar_t__ qp_active; struct rdma_cm_id* id; } ;
struct rdma_cm_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDP_WLOCK (struct sdp_sock*) ; 
 int /*<<< orphan*/  SDP_WLOCK_ASSERT (struct sdp_sock*) ; 
 int /*<<< orphan*/  SDP_WUNLOCK (struct sdp_sock*) ; 
 int /*<<< orphan*/  TCPS_CLOSED ; 
 int /*<<< orphan*/  rdma_disconnect (struct rdma_cm_id*) ; 

__attribute__((used)) static void
sdp_output_reset(struct sdp_sock *ssk)
{
	struct rdma_cm_id *id;

	SDP_WLOCK_ASSERT(ssk);
	if (ssk->id) {
		id = ssk->id;
		ssk->qp_active = 0;
		SDP_WUNLOCK(ssk);
		rdma_disconnect(id);
		SDP_WLOCK(ssk);
	}
	ssk->state = TCPS_CLOSED;
}
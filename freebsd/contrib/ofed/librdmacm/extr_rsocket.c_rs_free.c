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
struct rsocket {scalar_t__ type; scalar_t__ index; int /*<<< orphan*/  slock; int /*<<< orphan*/  rlock; int /*<<< orphan*/  cq_lock; int /*<<< orphan*/  cq_wait_lock; int /*<<< orphan*/  map_lock; TYPE_1__* cm_id; int /*<<< orphan*/  unack_cqe; struct rsocket* target_buffer_list; scalar_t__ target_mr; struct rsocket* rbuf; scalar_t__ rmr; struct rsocket* sbuf; scalar_t__ smr; struct rsocket* rmsg; } ;
struct TYPE_3__ {int /*<<< orphan*/  recv_cq; scalar_t__ qp; } ;

/* Variables and functions */
 scalar_t__ SOCK_DGRAM ; 
 int /*<<< orphan*/  ds_free (struct rsocket*) ; 
 int /*<<< orphan*/  fastlock_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct rsocket*) ; 
 int /*<<< orphan*/  ibv_ack_cq_events (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_dereg_mr (scalar_t__) ; 
 int /*<<< orphan*/  rdma_destroy_id (TYPE_1__*) ; 
 int /*<<< orphan*/  rdma_destroy_qp (TYPE_1__*) ; 
 int /*<<< orphan*/  rs_free_iomappings (struct rsocket*) ; 
 int /*<<< orphan*/  rs_remove (struct rsocket*) ; 

__attribute__((used)) static void rs_free(struct rsocket *rs)
{
	if (rs->type == SOCK_DGRAM) {
		ds_free(rs);
		return;
	}

	if (rs->rmsg)
		free(rs->rmsg);

	if (rs->sbuf) {
		if (rs->smr)
			rdma_dereg_mr(rs->smr);
		free(rs->sbuf);
	}

	if (rs->rbuf) {
		if (rs->rmr)
			rdma_dereg_mr(rs->rmr);
		free(rs->rbuf);
	}

	if (rs->target_buffer_list) {
		if (rs->target_mr)
			rdma_dereg_mr(rs->target_mr);
		free(rs->target_buffer_list);
	}

	if (rs->cm_id) {
		rs_free_iomappings(rs);
		if (rs->cm_id->qp) {
			ibv_ack_cq_events(rs->cm_id->recv_cq, rs->unack_cqe);
			rdma_destroy_qp(rs->cm_id);
		}
		rdma_destroy_id(rs->cm_id);
	}

	if (rs->index >= 0)
		rs_remove(rs);

	fastlock_destroy(&rs->map_lock);
	fastlock_destroy(&rs->cq_wait_lock);
	fastlock_destroy(&rs->cq_lock);
	fastlock_destroy(&rs->rlock);
	fastlock_destroy(&rs->slock);
	free(rs);
}
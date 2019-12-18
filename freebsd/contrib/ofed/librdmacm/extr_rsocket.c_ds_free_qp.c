#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  addr; } ;
struct ds_qp {TYPE_4__* cm_id; TYPE_2__* rs; TYPE_1__ dest; struct ds_qp* rbuf; scalar_t__ rmr; scalar_t__ smr; } ;
struct TYPE_9__ {TYPE_3__* recv_cq_channel; scalar_t__ qp; } ;
struct TYPE_8__ {int /*<<< orphan*/  fd; } ;
struct TYPE_7__ {int /*<<< orphan*/  epfd; int /*<<< orphan*/  dest_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPOLL_CTL_DEL ; 
 int /*<<< orphan*/  ds_compare_addr ; 
 int /*<<< orphan*/  epoll_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct ds_qp*) ; 
 int /*<<< orphan*/  rdma_dereg_mr (scalar_t__) ; 
 int /*<<< orphan*/  rdma_destroy_id (TYPE_4__*) ; 
 int /*<<< orphan*/  rdma_destroy_qp (TYPE_4__*) ; 
 int /*<<< orphan*/  tdelete (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ds_free_qp(struct ds_qp *qp)
{
	if (qp->smr)
		rdma_dereg_mr(qp->smr);

	if (qp->rbuf) {
		if (qp->rmr)
			rdma_dereg_mr(qp->rmr);
		free(qp->rbuf);
	}

	if (qp->cm_id) {
		if (qp->cm_id->qp) {
			tdelete(&qp->dest.addr, &qp->rs->dest_map, ds_compare_addr);
			epoll_ctl(qp->rs->epfd, EPOLL_CTL_DEL,
				  qp->cm_id->recv_cq_channel->fd, NULL);
			rdma_destroy_qp(qp->cm_id);
		}
		rdma_destroy_id(qp->cm_id);
	}

	free(qp);
}
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
struct rsocket {int fd_flags; scalar_t__ rq_size; scalar_t__ sq_size; } ;
struct rdma_cm_id {TYPE_1__* recv_cq_channel; int /*<<< orphan*/ * recv_cq; int /*<<< orphan*/ * send_cq; TYPE_1__* send_cq_channel; int /*<<< orphan*/  verbs; } ;
struct TYPE_4__ {int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  F_SETFL ; 
 int O_NONBLOCK ; 
 scalar_t__ fcntl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* ibv_create_comp_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ibv_create_cq (int /*<<< orphan*/ ,scalar_t__,struct rdma_cm_id*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibv_destroy_comp_channel (TYPE_1__*) ; 
 int /*<<< orphan*/  ibv_destroy_cq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ibv_req_notify_cq (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rs_create_cq(struct rsocket *rs, struct rdma_cm_id *cm_id)
{
	cm_id->recv_cq_channel = ibv_create_comp_channel(cm_id->verbs);
	if (!cm_id->recv_cq_channel)
		return -1;

	cm_id->recv_cq = ibv_create_cq(cm_id->verbs, rs->sq_size + rs->rq_size,
				       cm_id, cm_id->recv_cq_channel, 0);
	if (!cm_id->recv_cq)
		goto err1;

	if (rs->fd_flags & O_NONBLOCK) {
		if (fcntl(cm_id->recv_cq_channel->fd, F_SETFL, O_NONBLOCK))
			goto err2;
	}

	ibv_req_notify_cq(cm_id->recv_cq, 0);
	cm_id->send_cq_channel = cm_id->recv_cq_channel;
	cm_id->send_cq = cm_id->recv_cq;
	return 0;

err2:
	ibv_destroy_cq(cm_id->recv_cq);
	cm_id->recv_cq = NULL;
err1:
	ibv_destroy_comp_channel(cm_id->recv_cq_channel);
	cm_id->recv_cq_channel = NULL;
	return -1;
}
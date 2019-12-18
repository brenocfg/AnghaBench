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
struct rsocket {int opts; int rq_size; scalar_t__ sq_inline; TYPE_4__* cm_id; int /*<<< orphan*/  sq_size; } ;
struct TYPE_8__ {int max_recv_wr; int max_send_sge; int max_recv_sge; scalar_t__ max_inline_data; int /*<<< orphan*/  max_send_wr; } ;
struct ibv_qp_init_attr {int sq_sig_all; TYPE_3__ cap; int /*<<< orphan*/  qp_type; int /*<<< orphan*/  recv_cq; int /*<<< orphan*/  send_cq; struct rsocket* qp_context; } ;
struct TYPE_9__ {int /*<<< orphan*/  recv_cq; int /*<<< orphan*/  send_cq; TYPE_2__* verbs; } ;
struct TYPE_7__ {TYPE_1__* device; } ;
struct TYPE_6__ {scalar_t__ transport_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOTSUP ; 
 int ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IBV_QPT_RC ; 
 scalar_t__ IBV_TRANSPORT_IWARP ; 
 scalar_t__ RS_MSG_SIZE ; 
 int RS_OPT_MSG_SEND ; 
 int /*<<< orphan*/  memset (struct ibv_qp_init_attr*,int /*<<< orphan*/ ,int) ; 
 int rdma_create_qp (TYPE_4__*,int /*<<< orphan*/ *,struct ibv_qp_init_attr*) ; 
 int rs_create_cq (struct rsocket*,TYPE_4__*) ; 
 int rs_init_bufs (struct rsocket*) ; 
 int rs_post_recv (struct rsocket*) ; 
 int /*<<< orphan*/  rs_set_qp_size (struct rsocket*) ; 

__attribute__((used)) static int rs_create_ep(struct rsocket *rs)
{
	struct ibv_qp_init_attr qp_attr;
	int i, ret;

	rs_set_qp_size(rs);
	if (rs->cm_id->verbs->device->transport_type == IBV_TRANSPORT_IWARP)
		rs->opts |= RS_OPT_MSG_SEND;
	ret = rs_create_cq(rs, rs->cm_id);
	if (ret)
		return ret;

	memset(&qp_attr, 0, sizeof qp_attr);
	qp_attr.qp_context = rs;
	qp_attr.send_cq = rs->cm_id->send_cq;
	qp_attr.recv_cq = rs->cm_id->recv_cq;
	qp_attr.qp_type = IBV_QPT_RC;
	qp_attr.sq_sig_all = 1;
	qp_attr.cap.max_send_wr = rs->sq_size;
	qp_attr.cap.max_recv_wr = rs->rq_size;
	qp_attr.cap.max_send_sge = 2;
	qp_attr.cap.max_recv_sge = 1;
	qp_attr.cap.max_inline_data = rs->sq_inline;

	ret = rdma_create_qp(rs->cm_id, NULL, &qp_attr);
	if (ret)
		return ret;

	rs->sq_inline = qp_attr.cap.max_inline_data;
	if ((rs->opts & RS_OPT_MSG_SEND) && (rs->sq_inline < RS_MSG_SIZE))
		return ERR(ENOTSUP);

	ret = rs_init_bufs(rs);
	if (ret)
		return ret;

	for (i = 0; i < rs->rq_size; i++) {
		ret = rs_post_recv(rs);
		if (ret)
			return ret;
	}
	return 0;
}
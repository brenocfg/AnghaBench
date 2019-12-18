#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
union socket_addr {int /*<<< orphan*/  sa; } ;
struct rsocket {int rq_size; int /*<<< orphan*/  epfd; int /*<<< orphan*/  sq_inline; int /*<<< orphan*/  sq_size; } ;
struct TYPE_8__ {int max_recv_wr; int max_send_sge; int max_recv_sge; int /*<<< orphan*/  max_inline_data; int /*<<< orphan*/  max_send_wr; } ;
struct ibv_qp_init_attr {int sq_sig_all; TYPE_1__ cap; int /*<<< orphan*/  qp_type; int /*<<< orphan*/  recv_cq; int /*<<< orphan*/  send_cq; struct ds_qp* qp_context; } ;
struct TYPE_9__ {struct ds_qp* ptr; } ;
struct epoll_event {TYPE_2__ data; int /*<<< orphan*/  events; } ;
struct ds_qp {TYPE_4__* cm_id; int /*<<< orphan*/  hdr; struct rsocket* rs; } ;
typedef  int /*<<< orphan*/  socklen_t ;
struct TYPE_11__ {TYPE_3__* recv_cq_channel; int /*<<< orphan*/  recv_cq; int /*<<< orphan*/  send_cq; } ;
struct TYPE_10__ {int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  EPOLLIN ; 
 int /*<<< orphan*/  EPOLL_CTL_ADD ; 
 int ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IBV_QPT_UD ; 
 int /*<<< orphan*/  RDMA_PS_UDP ; 
 int RS_SNDLOWAT ; 
 struct ds_qp* calloc (int,int) ; 
 int ds_add_qp_dest (struct ds_qp*,union socket_addr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ds_format_hdr (int /*<<< orphan*/ *,union socket_addr*) ; 
 int /*<<< orphan*/  ds_free_qp (struct ds_qp*) ; 
 int ds_init_bufs (struct ds_qp*) ; 
 int /*<<< orphan*/  ds_insert_qp (struct rsocket*,struct ds_qp*) ; 
 int ds_post_recv (struct rsocket*,struct ds_qp*,int) ; 
 int epoll_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct epoll_event*) ; 
 int /*<<< orphan*/  memset (struct ibv_qp_init_attr*,int /*<<< orphan*/ ,int) ; 
 int rdma_bind_addr (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int rdma_create_id (int /*<<< orphan*/ *,TYPE_4__**,struct ds_qp*,int /*<<< orphan*/ ) ; 
 int rdma_create_qp (TYPE_4__*,int /*<<< orphan*/ *,struct ibv_qp_init_attr*) ; 
 int rs_create_cq (struct rsocket*,TYPE_4__*) ; 

__attribute__((used)) static int ds_create_qp(struct rsocket *rs, union socket_addr *src_addr,
			socklen_t addrlen, struct ds_qp **new_qp)
{
	struct ds_qp *qp;
	struct ibv_qp_init_attr qp_attr;
	struct epoll_event event;
	int i, ret;

	qp = calloc(1, sizeof(*qp));
	if (!qp)
		return ERR(ENOMEM);

	qp->rs = rs;
	ret = rdma_create_id(NULL, &qp->cm_id, qp, RDMA_PS_UDP);
	if (ret)
		goto err;

	ds_format_hdr(&qp->hdr, src_addr);
	ret = rdma_bind_addr(qp->cm_id, &src_addr->sa);
	if (ret)
		goto err;

	ret = ds_init_bufs(qp);
	if (ret)
		goto err;

	ret = rs_create_cq(rs, qp->cm_id);
	if (ret)
		goto err;

	memset(&qp_attr, 0, sizeof qp_attr);
	qp_attr.qp_context = qp;
	qp_attr.send_cq = qp->cm_id->send_cq;
	qp_attr.recv_cq = qp->cm_id->recv_cq;
	qp_attr.qp_type = IBV_QPT_UD;
	qp_attr.sq_sig_all = 1;
	qp_attr.cap.max_send_wr = rs->sq_size;
	qp_attr.cap.max_recv_wr = rs->rq_size;
	qp_attr.cap.max_send_sge = 1;
	qp_attr.cap.max_recv_sge = 2;
	qp_attr.cap.max_inline_data = rs->sq_inline;
	ret = rdma_create_qp(qp->cm_id, NULL, &qp_attr);
	if (ret)
		goto err;

	rs->sq_inline = qp_attr.cap.max_inline_data;
	ret = ds_add_qp_dest(qp, src_addr, addrlen);
	if (ret)
		goto err;

	event.events = EPOLLIN;
	event.data.ptr = qp;
	ret = epoll_ctl(rs->epfd,  EPOLL_CTL_ADD,
			qp->cm_id->recv_cq_channel->fd, &event);
	if (ret)
		goto err;

	for (i = 0; i < rs->rq_size; i++) {
		ret = ds_post_recv(rs, qp, i * RS_SNDLOWAT);
		if (ret)
			goto err;
	}

	ds_insert_qp(rs, qp);
	*new_qp = qp;
	return 0;
err:
	ds_free_qp(qp);
	return ret;
}
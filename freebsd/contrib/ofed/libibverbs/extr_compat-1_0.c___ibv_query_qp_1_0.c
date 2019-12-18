#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ibv_qp_init_attr_1_0 {int /*<<< orphan*/  sq_sig_all; int /*<<< orphan*/  cap; int /*<<< orphan*/  qp_type; int /*<<< orphan*/  srq; int /*<<< orphan*/  recv_cq; int /*<<< orphan*/  send_cq; int /*<<< orphan*/  qp_context; } ;
struct ibv_qp_init_attr {int /*<<< orphan*/  sq_sig_all; int /*<<< orphan*/  cap; int /*<<< orphan*/  qp_type; TYPE_3__* srq; TYPE_2__* recv_cq; TYPE_1__* send_cq; } ;
struct ibv_qp_attr {int dummy; } ;
struct ibv_qp_1_0 {int /*<<< orphan*/  qp_context; int /*<<< orphan*/  real_qp; } ;
struct TYPE_6__ {int /*<<< orphan*/  srq_context; } ;
struct TYPE_5__ {int /*<<< orphan*/  cq_context; } ;
struct TYPE_4__ {int /*<<< orphan*/  cq_context; } ;

/* Variables and functions */
 int ibv_query_qp (int /*<<< orphan*/ ,struct ibv_qp_attr*,int,struct ibv_qp_init_attr*) ; 

int __ibv_query_qp_1_0(struct ibv_qp_1_0 *qp, struct ibv_qp_attr *attr,
		       int attr_mask,
		       struct ibv_qp_init_attr_1_0 *init_attr)
{
	struct ibv_qp_init_attr real_init_attr;
	int ret;

	ret = ibv_query_qp(qp->real_qp, attr, attr_mask, &real_init_attr);
	if (ret)
		return ret;

	init_attr->qp_context = qp->qp_context;
	init_attr->send_cq    = real_init_attr.send_cq->cq_context;
	init_attr->recv_cq    = real_init_attr.recv_cq->cq_context;
	init_attr->srq        = real_init_attr.srq->srq_context;
	init_attr->qp_type    = real_init_attr.qp_type;
	init_attr->cap        = real_init_attr.cap;
	init_attr->sq_sig_all = real_init_attr.sq_sig_all;

	return 0;
}
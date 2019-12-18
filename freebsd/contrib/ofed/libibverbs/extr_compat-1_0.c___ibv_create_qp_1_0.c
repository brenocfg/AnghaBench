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
struct ibv_qp_init_attr_1_0 {int /*<<< orphan*/  cap; int /*<<< orphan*/  qp_type; TYPE_3__* srq; TYPE_2__* recv_cq; TYPE_1__* send_cq; int /*<<< orphan*/  qp_context; int /*<<< orphan*/  sq_sig_all; } ;
struct ibv_qp_init_attr {int /*<<< orphan*/  cap; int /*<<< orphan*/  sq_sig_all; int /*<<< orphan*/  qp_type; int /*<<< orphan*/ * srq; int /*<<< orphan*/  recv_cq; int /*<<< orphan*/  send_cq; int /*<<< orphan*/  qp_context; } ;
struct ibv_qp_1_0 {struct ibv_qp* real_qp; int /*<<< orphan*/  qp_num; int /*<<< orphan*/  qp_type; TYPE_3__* srq; TYPE_2__* recv_cq; TYPE_1__* send_cq; struct ibv_pd_1_0* pd; int /*<<< orphan*/  qp_context; int /*<<< orphan*/  context; } ;
struct ibv_qp {struct ibv_qp_1_0* qp_context; int /*<<< orphan*/  qp_num; } ;
struct ibv_pd_1_0 {int /*<<< orphan*/  context; int /*<<< orphan*/  real_pd; } ;
struct TYPE_6__ {int /*<<< orphan*/ * real_srq; } ;
struct TYPE_5__ {int /*<<< orphan*/  real_cq; } ;
struct TYPE_4__ {int /*<<< orphan*/  real_cq; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct ibv_qp_1_0*) ; 
 struct ibv_qp* ibv_create_qp (int /*<<< orphan*/ ,struct ibv_qp_init_attr*) ; 
 struct ibv_qp_1_0* malloc (int) ; 

struct ibv_qp_1_0 *__ibv_create_qp_1_0(struct ibv_pd_1_0 *pd,
				       struct ibv_qp_init_attr_1_0 *qp_init_attr)
{
	struct ibv_qp *real_qp;
	struct ibv_qp_1_0 *qp;
	struct ibv_qp_init_attr real_init_attr;

	qp = malloc(sizeof *qp);
	if (!qp)
		return NULL;

	real_init_attr.qp_context = qp_init_attr->qp_context;
	real_init_attr.send_cq    = qp_init_attr->send_cq->real_cq;
	real_init_attr.recv_cq    = qp_init_attr->recv_cq->real_cq;
	real_init_attr.srq        = qp_init_attr->srq ?
		qp_init_attr->srq->real_srq : NULL;
	real_init_attr.cap        = qp_init_attr->cap;
	real_init_attr.qp_type    = qp_init_attr->qp_type;
	real_init_attr.sq_sig_all = qp_init_attr->sq_sig_all;

	real_qp = ibv_create_qp(pd->real_pd, &real_init_attr);
	if (!real_qp) {
		free(qp);
		return NULL;
	}

	qp->context    = pd->context;
	qp->qp_context = qp_init_attr->qp_context;
	qp->pd         = pd;
	qp->send_cq    = qp_init_attr->send_cq;
	qp->recv_cq    = qp_init_attr->recv_cq;
	qp->srq        = qp_init_attr->srq;
	qp->qp_type    = qp_init_attr->qp_type;
	qp->qp_num     = real_qp->qp_num;
	qp->real_qp    = real_qp;

	qp_init_attr->cap = real_init_attr.cap;

	real_qp->qp_context = qp;

	return qp;
}
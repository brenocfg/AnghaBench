#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ibv_qp_init_attr {int /*<<< orphan*/  qp_type; int /*<<< orphan*/  srq; int /*<<< orphan*/  recv_cq; int /*<<< orphan*/  send_cq; int /*<<< orphan*/  qp_context; } ;
struct ibv_qp {int /*<<< orphan*/  cond; int /*<<< orphan*/  mutex; scalar_t__ events_completed; int /*<<< orphan*/  state; int /*<<< orphan*/  qp_type; int /*<<< orphan*/  srq; int /*<<< orphan*/  recv_cq; int /*<<< orphan*/  send_cq; struct ibv_pd* pd; int /*<<< orphan*/  qp_context; TYPE_2__* context; } ;
struct ibv_pd {TYPE_2__* context; } ;
struct TYPE_3__ {struct ibv_qp* (* create_qp ) (struct ibv_pd*,struct ibv_qp_init_attr*) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  IBV_QPS_RESET ; 
 int /*<<< orphan*/  pthread_cond_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct ibv_qp* stub1 (struct ibv_pd*,struct ibv_qp_init_attr*) ; 

struct ibv_qp *__ibv_create_qp(struct ibv_pd *pd,
			       struct ibv_qp_init_attr *qp_init_attr)
{
	struct ibv_qp *qp = pd->context->ops.create_qp(pd, qp_init_attr);

	if (qp) {
		qp->context    	     = pd->context;
		qp->qp_context 	     = qp_init_attr->qp_context;
		qp->pd         	     = pd;
		qp->send_cq    	     = qp_init_attr->send_cq;
		qp->recv_cq    	     = qp_init_attr->recv_cq;
		qp->srq        	     = qp_init_attr->srq;
		qp->qp_type          = qp_init_attr->qp_type;
		qp->state	     = IBV_QPS_RESET;
		qp->events_completed = 0;
		pthread_mutex_init(&qp->mutex, NULL);
		pthread_cond_init(&qp->cond, NULL);
	}

	return qp;
}
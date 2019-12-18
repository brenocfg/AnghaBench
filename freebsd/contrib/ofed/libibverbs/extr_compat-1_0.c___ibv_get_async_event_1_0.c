#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ibv_context_1_0 {int /*<<< orphan*/  real_context; } ;
struct TYPE_7__ {TYPE_1__* srq; TYPE_4__* qp; TYPE_2__* cq; } ;
struct ibv_async_event {int event_type; TYPE_3__ element; } ;
struct TYPE_8__ {struct TYPE_8__* qp_context; } ;
struct TYPE_6__ {struct TYPE_6__* cq_context; } ;
struct TYPE_5__ {struct TYPE_5__* srq_context; } ;

/* Variables and functions */
#define  IBV_EVENT_COMM_EST 138 
#define  IBV_EVENT_CQ_ERR 137 
#define  IBV_EVENT_PATH_MIG 136 
#define  IBV_EVENT_PATH_MIG_ERR 135 
#define  IBV_EVENT_QP_ACCESS_ERR 134 
#define  IBV_EVENT_QP_FATAL 133 
#define  IBV_EVENT_QP_LAST_WQE_REACHED 132 
#define  IBV_EVENT_QP_REQ_ERR 131 
#define  IBV_EVENT_SQ_DRAINED 130 
#define  IBV_EVENT_SRQ_ERR 129 
#define  IBV_EVENT_SRQ_LIMIT_REACHED 128 
 int ibv_get_async_event (int /*<<< orphan*/ ,struct ibv_async_event*) ; 

int __ibv_get_async_event_1_0(struct ibv_context_1_0 *context,
			      struct ibv_async_event *event)
{
	int ret;

	ret = ibv_get_async_event(context->real_context, event);
	if (ret)
		return ret;

	switch (event->event_type) {
	case IBV_EVENT_CQ_ERR:
		event->element.cq = event->element.cq->cq_context;
		break;

	case IBV_EVENT_QP_FATAL:
	case IBV_EVENT_QP_REQ_ERR:
	case IBV_EVENT_QP_ACCESS_ERR:
	case IBV_EVENT_COMM_EST:
	case IBV_EVENT_SQ_DRAINED:
	case IBV_EVENT_PATH_MIG:
	case IBV_EVENT_PATH_MIG_ERR:
	case IBV_EVENT_QP_LAST_WQE_REACHED:
		event->element.qp = event->element.qp->qp_context;
		break;

	case IBV_EVENT_SRQ_ERR:
	case IBV_EVENT_SRQ_LIMIT_REACHED:
		event->element.srq = event->element.srq->srq_context;
		break;

	default:
		break;
	}

	return ret;
}
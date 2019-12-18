#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ibv_srq_1_0 {scalar_t__ real_srq; } ;
struct ibv_qp_1_0 {scalar_t__ real_qp; } ;
struct ibv_cq_1_0 {scalar_t__ real_cq; } ;
struct TYPE_2__ {scalar_t__ srq; scalar_t__ qp; scalar_t__ cq; } ;
struct ibv_async_event {int event_type; TYPE_1__ element; } ;

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
 int /*<<< orphan*/  ibv_ack_async_event (struct ibv_async_event*) ; 

void __ibv_ack_async_event_1_0(struct ibv_async_event *event)
{
	struct ibv_async_event real_event = *event;

	switch (event->event_type) {
	case IBV_EVENT_CQ_ERR:
		real_event.element.cq =
			((struct ibv_cq_1_0 *) event->element.cq)->real_cq;
		break;

	case IBV_EVENT_QP_FATAL:
	case IBV_EVENT_QP_REQ_ERR:
	case IBV_EVENT_QP_ACCESS_ERR:
	case IBV_EVENT_COMM_EST:
	case IBV_EVENT_SQ_DRAINED:
	case IBV_EVENT_PATH_MIG:
	case IBV_EVENT_PATH_MIG_ERR:
	case IBV_EVENT_QP_LAST_WQE_REACHED:
		real_event.element.qp =
			((struct ibv_qp_1_0 *) event->element.qp)->real_qp;
		break;

	case IBV_EVENT_SRQ_ERR:
	case IBV_EVENT_SRQ_LIMIT_REACHED:
		real_event.element.srq =
			((struct ibv_srq_1_0 *) event->element.srq)->real_srq;
		break;

	default:
		break;
	}

	ibv_ack_async_event(&real_event);
}
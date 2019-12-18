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
struct ibv_wq {int /*<<< orphan*/  mutex; int /*<<< orphan*/  cond; int /*<<< orphan*/  events_completed; } ;
struct ibv_srq {int /*<<< orphan*/  mutex; int /*<<< orphan*/  cond; int /*<<< orphan*/  events_completed; } ;
struct ibv_qp {int /*<<< orphan*/  mutex; int /*<<< orphan*/  cond; int /*<<< orphan*/  events_completed; } ;
struct ibv_cq {int /*<<< orphan*/  mutex; int /*<<< orphan*/  cond; int /*<<< orphan*/  async_events_completed; } ;
struct TYPE_2__ {struct ibv_wq* wq; struct ibv_srq* srq; struct ibv_qp* qp; struct ibv_cq* cq; } ;
struct ibv_async_event {int event_type; TYPE_1__ element; } ;

/* Variables and functions */
#define  IBV_EVENT_COMM_EST 139 
#define  IBV_EVENT_CQ_ERR 138 
#define  IBV_EVENT_PATH_MIG 137 
#define  IBV_EVENT_PATH_MIG_ERR 136 
#define  IBV_EVENT_QP_ACCESS_ERR 135 
#define  IBV_EVENT_QP_FATAL 134 
#define  IBV_EVENT_QP_LAST_WQE_REACHED 133 
#define  IBV_EVENT_QP_REQ_ERR 132 
#define  IBV_EVENT_SQ_DRAINED 131 
#define  IBV_EVENT_SRQ_ERR 130 
#define  IBV_EVENT_SRQ_LIMIT_REACHED 129 
#define  IBV_EVENT_WQ_FATAL 128 
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void __ibv_ack_async_event(struct ibv_async_event *event)
{
	switch (event->event_type) {
	case IBV_EVENT_CQ_ERR:
	{
		struct ibv_cq *cq = event->element.cq;

		pthread_mutex_lock(&cq->mutex);
		++cq->async_events_completed;
		pthread_cond_signal(&cq->cond);
		pthread_mutex_unlock(&cq->mutex);

		return;
	}

	case IBV_EVENT_QP_FATAL:
	case IBV_EVENT_QP_REQ_ERR:
	case IBV_EVENT_QP_ACCESS_ERR:
	case IBV_EVENT_COMM_EST:
	case IBV_EVENT_SQ_DRAINED:
	case IBV_EVENT_PATH_MIG:
	case IBV_EVENT_PATH_MIG_ERR:
	case IBV_EVENT_QP_LAST_WQE_REACHED:
	{
		struct ibv_qp *qp = event->element.qp;

		pthread_mutex_lock(&qp->mutex);
		++qp->events_completed;
		pthread_cond_signal(&qp->cond);
		pthread_mutex_unlock(&qp->mutex);

		return;
	}

	case IBV_EVENT_SRQ_ERR:
	case IBV_EVENT_SRQ_LIMIT_REACHED:
	{
		struct ibv_srq *srq = event->element.srq;

		pthread_mutex_lock(&srq->mutex);
		++srq->events_completed;
		pthread_cond_signal(&srq->cond);
		pthread_mutex_unlock(&srq->mutex);

		return;
	}

	case IBV_EVENT_WQ_FATAL:
	{
		struct ibv_wq *wq = event->element.wq;

		pthread_mutex_lock(&wq->mutex);
		++wq->events_completed;
		pthread_cond_signal(&wq->cond);
		pthread_mutex_unlock(&wq->mutex);

		return;
	}

	default:
		return;
	}
}
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
struct ibv_kern_async_event {int /*<<< orphan*/  element; int /*<<< orphan*/  event_type; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* async_event ) (struct ibv_async_event*) ;} ;
struct ibv_context {TYPE_2__ ops; int /*<<< orphan*/  async_fd; } ;
struct TYPE_3__ {int /*<<< orphan*/  port_num; void* wq; void* srq; void* qp; void* cq; } ;
struct ibv_async_event {TYPE_1__ element; int /*<<< orphan*/  event_type; } ;

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
 int read (int /*<<< orphan*/ ,struct ibv_kern_async_event*,int) ; 
 int /*<<< orphan*/  stub1 (struct ibv_async_event*) ; 

int __ibv_get_async_event(struct ibv_context *context,
			  struct ibv_async_event *event)
{
	struct ibv_kern_async_event ev;

	if (read(context->async_fd, &ev, sizeof ev) != sizeof ev)
		return -1;

	event->event_type = ev.event_type;

	switch (event->event_type) {
	case IBV_EVENT_CQ_ERR:
		event->element.cq = (void *) (uintptr_t) ev.element;
		break;

	case IBV_EVENT_QP_FATAL:
	case IBV_EVENT_QP_REQ_ERR:
	case IBV_EVENT_QP_ACCESS_ERR:
	case IBV_EVENT_COMM_EST:
	case IBV_EVENT_SQ_DRAINED:
	case IBV_EVENT_PATH_MIG:
	case IBV_EVENT_PATH_MIG_ERR:
	case IBV_EVENT_QP_LAST_WQE_REACHED:
		event->element.qp = (void *) (uintptr_t) ev.element;
		break;

	case IBV_EVENT_SRQ_ERR:
	case IBV_EVENT_SRQ_LIMIT_REACHED:
		event->element.srq = (void *) (uintptr_t) ev.element;
		break;

	case IBV_EVENT_WQ_FATAL:
		event->element.wq = (void *) (uintptr_t) ev.element;
		break;
	default:
		event->element.port_num = ev.element;
		break;
	}

	if (context->ops.async_event)
		context->ops.async_event(event);

	return 0;
}
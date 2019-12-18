#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct bulk_waiter {scalar_t__ actual; int /*<<< orphan*/  event; } ;
typedef  scalar_t__ VCHIQ_STATUS_T ;
struct TYPE_17__ {scalar_t__ process; scalar_t__ remote_notify; scalar_t__ remove; TYPE_3__* bulks; } ;
struct TYPE_14__ {TYPE_4__ bulk_tx; TYPE_5__* state; int /*<<< orphan*/  bulk_remove_event; scalar_t__ instance; int /*<<< orphan*/  remoteport; int /*<<< orphan*/  localport; } ;
typedef  TYPE_1__ VCHIQ_SERVICE_T ;
typedef  int /*<<< orphan*/  VCHIQ_REASON_T ;
struct TYPE_15__ {scalar_t__* member_0; int member_1; } ;
typedef  TYPE_2__ VCHIQ_ELEMENT_T ;
struct TYPE_16__ {scalar_t__ dir; scalar_t__ actual; scalar_t__ mode; struct bulk_waiter* userdata; scalar_t__ data; scalar_t__ remote_data; } ;
typedef  TYPE_3__ VCHIQ_BULK_T ;
typedef  TYPE_4__ VCHIQ_BULK_QUEUE_T ;
struct TYPE_18__ {scalar_t__ is_master; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 size_t BULK_INDEX (scalar_t__) ; 
 scalar_t__ VCHIQ_BULK_ACTUAL_ABORTED ; 
 scalar_t__ VCHIQ_BULK_MODE_BLOCKING ; 
 scalar_t__ VCHIQ_BULK_MODE_CALLBACK ; 
 int /*<<< orphan*/  VCHIQ_BULK_RECEIVE_ABORTED ; 
 int /*<<< orphan*/  VCHIQ_BULK_RECEIVE_DONE ; 
 scalar_t__ VCHIQ_BULK_TRANSMIT ; 
 int /*<<< orphan*/  VCHIQ_BULK_TRANSMIT_ABORTED ; 
 int /*<<< orphan*/  VCHIQ_BULK_TRANSMIT_DONE ; 
 int VCHIQ_MAKE_MSG (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int VCHIQ_MSG_BULK_RX_DONE ; 
 int VCHIQ_MSG_BULK_TX_DONE ; 
 int /*<<< orphan*/  VCHIQ_POLL_RXNOTIFY ; 
 int /*<<< orphan*/  VCHIQ_POLL_TXNOTIFY ; 
 scalar_t__ VCHIQ_RETRY ; 
 int /*<<< orphan*/  VCHIQ_SERVICE_STATS_ADD (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  VCHIQ_SERVICE_STATS_INC (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ VCHIQ_SUCCESS ; 
 int /*<<< orphan*/  bulk_aborted_count ; 
 int /*<<< orphan*/  bulk_rx_bytes ; 
 int /*<<< orphan*/  bulk_rx_count ; 
 int /*<<< orphan*/  bulk_tx_bytes ; 
 int /*<<< orphan*/  bulk_tx_count ; 
 int /*<<< orphan*/  bulk_waiter_spinlock ; 
 scalar_t__ make_service_callback (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct bulk_waiter*) ; 
 scalar_t__ queue_message (TYPE_5__*,int /*<<< orphan*/ *,int,TYPE_2__*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  request_poll (TYPE_5__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vchiq_core_log_level ; 
 int /*<<< orphan*/  vchiq_log_trace (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static VCHIQ_STATUS_T
notify_bulks(VCHIQ_SERVICE_T *service, VCHIQ_BULK_QUEUE_T *queue,
	int retry_poll)
{
	VCHIQ_STATUS_T status = VCHIQ_SUCCESS;

	vchiq_log_trace(vchiq_core_log_level,
		"%d: nb:%d %cx - p=%x rn=%x r=%x",
		service->state->id, service->localport,
		(queue == &service->bulk_tx) ? 't' : 'r',
		queue->process, queue->remote_notify, queue->remove);

	if (service->state->is_master) {
		while (queue->remote_notify != queue->process) {
			VCHIQ_BULK_T *bulk =
				&queue->bulks[BULK_INDEX(queue->remote_notify)];
			int msgtype = (bulk->dir == VCHIQ_BULK_TRANSMIT) ?
				VCHIQ_MSG_BULK_RX_DONE : VCHIQ_MSG_BULK_TX_DONE;
			int msgid = VCHIQ_MAKE_MSG(msgtype, service->localport,
				service->remoteport);
			VCHIQ_ELEMENT_T element = { &bulk->actual, 4 };
			/* Only reply to non-dummy bulk requests */
			if (bulk->remote_data) {
				status = queue_message(service->state, NULL,
					msgid, &element, 1, 4, 0);
				if (status != VCHIQ_SUCCESS)
					break;
			}
			queue->remote_notify++;
		}
	} else {
		queue->remote_notify = queue->process;
	}

	if (status == VCHIQ_SUCCESS) {
		while (queue->remove != queue->remote_notify) {
			VCHIQ_BULK_T *bulk =
				&queue->bulks[BULK_INDEX(queue->remove)];

			/* Only generate callbacks for non-dummy bulk
			** requests, and non-terminated services */
			if (bulk->data && service->instance) {
				if (bulk->actual != VCHIQ_BULK_ACTUAL_ABORTED) {
					if (bulk->dir == VCHIQ_BULK_TRANSMIT) {
						VCHIQ_SERVICE_STATS_INC(service,
							bulk_tx_count);
						VCHIQ_SERVICE_STATS_ADD(service,
							bulk_tx_bytes,
							bulk->actual);
					} else {
						VCHIQ_SERVICE_STATS_INC(service,
							bulk_rx_count);
						VCHIQ_SERVICE_STATS_ADD(service,
							bulk_rx_bytes,
							bulk->actual);
					}
				} else {
					VCHIQ_SERVICE_STATS_INC(service,
						bulk_aborted_count);
				}
				if (bulk->mode == VCHIQ_BULK_MODE_BLOCKING) {
					struct bulk_waiter *waiter;
					spin_lock(&bulk_waiter_spinlock);
					waiter = bulk->userdata;
					if (waiter) {
						waiter->actual = bulk->actual;
						up(&waiter->event);
					}
					spin_unlock(&bulk_waiter_spinlock);
				} else if (bulk->mode ==
					VCHIQ_BULK_MODE_CALLBACK) {
					VCHIQ_REASON_T reason = (bulk->dir ==
						VCHIQ_BULK_TRANSMIT) ?
						((bulk->actual ==
						VCHIQ_BULK_ACTUAL_ABORTED) ?
						VCHIQ_BULK_TRANSMIT_ABORTED :
						VCHIQ_BULK_TRANSMIT_DONE) :
						((bulk->actual ==
						VCHIQ_BULK_ACTUAL_ABORTED) ?
						VCHIQ_BULK_RECEIVE_ABORTED :
						VCHIQ_BULK_RECEIVE_DONE);
					status = make_service_callback(service,
						reason,	NULL, bulk->userdata);
					if (status == VCHIQ_RETRY)
						break;
				}
			}

			queue->remove++;
			up(&service->bulk_remove_event);
		}
		if (!retry_poll)
			status = VCHIQ_SUCCESS;
	}

	if (status == VCHIQ_RETRY)
		request_poll(service->state, service,
			(queue == &service->bulk_tx) ?
			VCHIQ_POLL_TXNOTIFY : VCHIQ_POLL_RXNOTIFY);

	return status;
}
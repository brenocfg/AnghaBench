#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VCHIQ_STATUS_T ;
struct TYPE_11__ {int /*<<< orphan*/  is_master; int /*<<< orphan*/  sync_mutex; int /*<<< orphan*/  slot_mutex; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ VCHIQ_STATE_T ;
struct TYPE_12__ {scalar_t__ public_fourcc; size_t srvstate; int /*<<< orphan*/  sync; int /*<<< orphan*/  remoteport; int /*<<< orphan*/  localport; int /*<<< orphan*/  remove_event; int /*<<< orphan*/  client_id; TYPE_1__* state; } ;
typedef  TYPE_2__ VCHIQ_SERVICE_T ;

/* Variables and functions */
 int /*<<< orphan*/  QMFLAGS_NO_MUTEX_UNLOCK ; 
 int /*<<< orphan*/  VCHIQ_ERROR ; 
 scalar_t__ VCHIQ_FOURCC_INVALID ; 
 int /*<<< orphan*/  VCHIQ_MAKE_MSG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VCHIQ_MSG_CLOSE ; 
 int /*<<< orphan*/  VCHIQ_MSG_DSTPORT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VCHIQ_PORT_FREE ; 
 int /*<<< orphan*/  VCHIQ_RETRY ; 
#define  VCHIQ_SRVSTATE_CLOSED 136 
#define  VCHIQ_SRVSTATE_CLOSERECVD 135 
#define  VCHIQ_SRVSTATE_CLOSESENT 134 
#define  VCHIQ_SRVSTATE_CLOSEWAIT 133 
#define  VCHIQ_SRVSTATE_HIDDEN 132 
#define  VCHIQ_SRVSTATE_LISTENING 131 
#define  VCHIQ_SRVSTATE_OPEN 130 
#define  VCHIQ_SRVSTATE_OPENING 129 
#define  VCHIQ_SRVSTATE_OPENSYNC 128 
 int /*<<< orphan*/  VCHIQ_SUCCESS ; 
 int /*<<< orphan*/  close_service_complete (TYPE_2__*,int const) ; 
 int /*<<< orphan*/  do_abort_bulks (TYPE_2__*) ; 
 int /*<<< orphan*/  lmutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lmutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_message (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_service_messages (TYPE_2__*) ; 
 int /*<<< orphan*/ * srvstate_names ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vchiq_core_log_level ; 
 int /*<<< orphan*/  vchiq_free_service_internal (TYPE_2__*) ; 
 int /*<<< orphan*/  vchiq_log_error (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  vchiq_log_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vchiq_set_service_state (TYPE_2__*,int const) ; 

VCHIQ_STATUS_T
vchiq_close_service_internal(VCHIQ_SERVICE_T *service, int close_recvd)
{
	VCHIQ_STATE_T *state = service->state;
	VCHIQ_STATUS_T status = VCHIQ_SUCCESS;
	int is_server = (service->public_fourcc != VCHIQ_FOURCC_INVALID);

	vchiq_log_info(vchiq_core_log_level, "%d: csi:%d,%d (%s)",
		service->state->id, service->localport, close_recvd,
		srvstate_names[service->srvstate]);

	switch (service->srvstate) {
	case VCHIQ_SRVSTATE_CLOSED:
	case VCHIQ_SRVSTATE_HIDDEN:
	case VCHIQ_SRVSTATE_LISTENING:
	case VCHIQ_SRVSTATE_CLOSEWAIT:
		if (close_recvd)
			vchiq_log_error(vchiq_core_log_level,
				"vchiq_close_service_internal(1) called "
				"in state %s",
				srvstate_names[service->srvstate]);
		else if (is_server) {
			if (service->srvstate == VCHIQ_SRVSTATE_LISTENING) {
				status = VCHIQ_ERROR;
			} else {
				service->client_id = 0;
				service->remoteport = VCHIQ_PORT_FREE;
				if (service->srvstate ==
					VCHIQ_SRVSTATE_CLOSEWAIT)
					vchiq_set_service_state(service,
						VCHIQ_SRVSTATE_LISTENING);
			}
			up(&service->remove_event);
		} else
			vchiq_free_service_internal(service);
		break;
	case VCHIQ_SRVSTATE_OPENING:
		if (close_recvd) {
			/* The open was rejected - tell the user */
			vchiq_set_service_state(service,
				VCHIQ_SRVSTATE_CLOSEWAIT);
			up(&service->remove_event);
		} else {
			/* Shutdown mid-open - let the other side know */
			status = queue_message(state, service,
				VCHIQ_MAKE_MSG
				(VCHIQ_MSG_CLOSE,
				service->localport,
				VCHIQ_MSG_DSTPORT(service->remoteport)),
				NULL, 0, 0, 0);
		}
		break;

	case VCHIQ_SRVSTATE_OPENSYNC:
		lmutex_lock(&state->sync_mutex);
		/* Drop through */

	case VCHIQ_SRVSTATE_OPEN:
		if (state->is_master || close_recvd) {
			if (!do_abort_bulks(service))
				status = VCHIQ_RETRY;
		}

		release_service_messages(service);

		if (status == VCHIQ_SUCCESS)
			status = queue_message(state, service,
				VCHIQ_MAKE_MSG
				(VCHIQ_MSG_CLOSE,
				service->localport,
				VCHIQ_MSG_DSTPORT(service->remoteport)),
				NULL, 0, 0, QMFLAGS_NO_MUTEX_UNLOCK);

		if (status == VCHIQ_SUCCESS) {
			if (!close_recvd) {
				/* Change the state while the mutex is
				   still held */
				vchiq_set_service_state(service,
							VCHIQ_SRVSTATE_CLOSESENT);
				lmutex_unlock(&state->slot_mutex);
				if (service->sync)
					lmutex_unlock(&state->sync_mutex);
				break;
			}
		} else if (service->srvstate == VCHIQ_SRVSTATE_OPENSYNC) {
			lmutex_unlock(&state->sync_mutex);
			break;
		} else
			break;

		/* Change the state while the mutex is still held */
		vchiq_set_service_state(service, VCHIQ_SRVSTATE_CLOSERECVD);
		lmutex_unlock(&state->slot_mutex);
		if (service->sync)
			lmutex_unlock(&state->sync_mutex);

		status = close_service_complete(service,
				VCHIQ_SRVSTATE_CLOSERECVD);
		break;

	case VCHIQ_SRVSTATE_CLOSESENT:
		if (!close_recvd)
			/* This happens when a process is killed mid-close */
			break;

		if (!state->is_master) {
			if (!do_abort_bulks(service)) {
				status = VCHIQ_RETRY;
				break;
			}
		}

		if (status == VCHIQ_SUCCESS)
			status = close_service_complete(service,
				VCHIQ_SRVSTATE_CLOSERECVD);
		break;

	case VCHIQ_SRVSTATE_CLOSERECVD:
		if (!close_recvd && is_server)
			/* Force into LISTENING mode */
			vchiq_set_service_state(service,
				VCHIQ_SRVSTATE_LISTENING);
		status = close_service_complete(service,
			VCHIQ_SRVSTATE_CLOSERECVD);
		break;

	default:
		vchiq_log_error(vchiq_core_log_level,
			"vchiq_close_service_internal(%d) called in state %s",
			close_recvd, srvstate_names[service->srvstate]);
		break;
	}

	return status;
}
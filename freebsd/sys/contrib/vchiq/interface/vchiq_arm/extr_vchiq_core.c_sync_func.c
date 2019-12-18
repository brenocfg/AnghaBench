#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct vchiq_openack_payload {int /*<<< orphan*/  version; } ;
struct TYPE_18__ {int /*<<< orphan*/  id; TYPE_1__* remote; TYPE_4__* local; } ;
typedef  TYPE_3__ VCHIQ_STATE_T ;
struct TYPE_19__ {int /*<<< orphan*/  sync_trigger; } ;
typedef  TYPE_4__ VCHIQ_SHARED_STATE_T ;
struct TYPE_17__ {int fourcc; } ;
struct TYPE_20__ {unsigned int remoteport; int sync; int /*<<< orphan*/  srvstate; int /*<<< orphan*/  remove_event; int /*<<< orphan*/  peer_version; TYPE_2__ base; } ;
typedef  TYPE_5__ VCHIQ_SERVICE_T ;
struct TYPE_21__ {int msgid; int size; scalar_t__ data; } ;
typedef  TYPE_6__ VCHIQ_HEADER_T ;
struct TYPE_16__ {int /*<<< orphan*/  slot_sync; } ;

/* Variables and functions */
 scalar_t__ SLOT_DATA_FROM_INDEX (TYPE_3__*,int /*<<< orphan*/ ) ; 
 unsigned int VCHIQ_FOURCC_AS_4CHARS (int) ; 
 scalar_t__ VCHIQ_LOG_TRACE ; 
 int VCHIQ_MAKE_FOURCC (char,char,char,char) ; 
 int /*<<< orphan*/  VCHIQ_MESSAGE_AVAILABLE ; 
#define  VCHIQ_MSG_DATA 129 
 unsigned int VCHIQ_MSG_DSTPORT (int) ; 
#define  VCHIQ_MSG_OPENACK 128 
 unsigned int VCHIQ_MSG_SRCPORT (int) ; 
 int VCHIQ_MSG_TYPE (int) ; 
 int /*<<< orphan*/  VCHIQ_RETRY ; 
 int /*<<< orphan*/  VCHIQ_SRVSTATE_OPENING ; 
 int /*<<< orphan*/  VCHIQ_SRVSTATE_OPENSYNC ; 
 TYPE_5__* find_service_by_port (TYPE_3__*,unsigned int) ; 
 int /*<<< orphan*/  make_service_callback (TYPE_5__*,int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  min (int,int) ; 
 int /*<<< orphan*/  msg_type_str (int) ; 
 int /*<<< orphan*/  release_message_sync (TYPE_3__*,TYPE_6__*) ; 
 int /*<<< orphan*/  remote_event_wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rmb () ; 
 int /*<<< orphan*/  unlock_service (TYPE_5__*) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vchiq_log_dump_mem (char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vchiq_log_error (scalar_t__,char*,unsigned int,...) ; 
 int /*<<< orphan*/  vchiq_log_info (scalar_t__,char*,int /*<<< orphan*/ ,unsigned int,int,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vchiq_log_trace (scalar_t__,char*,int /*<<< orphan*/ ,unsigned int,int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  vchiq_set_service_state (TYPE_5__*,int /*<<< orphan*/ ) ; 
 scalar_t__ vchiq_sync_log_level ; 

int
sync_func(void *v)
{
	VCHIQ_STATE_T *state = (VCHIQ_STATE_T *) v;
	VCHIQ_SHARED_STATE_T *local = state->local;
	VCHIQ_HEADER_T *header = (VCHIQ_HEADER_T *)SLOT_DATA_FROM_INDEX(state,
		state->remote->slot_sync);

	while (1) {
		VCHIQ_SERVICE_T *service;
		int msgid, size;
		int type;
		unsigned int localport, remoteport;

		remote_event_wait(&local->sync_trigger);

		rmb();

		msgid = header->msgid;
		size = header->size;
		type = VCHIQ_MSG_TYPE(msgid);
		localport = VCHIQ_MSG_DSTPORT(msgid);
		remoteport = VCHIQ_MSG_SRCPORT(msgid);

		service = find_service_by_port(state, localport);

		if (!service) {
			vchiq_log_error(vchiq_sync_log_level,
				"%d: sf %s@%x (%d->%d) - "
				"invalid/closed service %d",
				state->id, msg_type_str(type),
				(unsigned int)header,
				remoteport, localport, localport);
			release_message_sync(state, header);
			continue;
		}

		if (vchiq_sync_log_level >= VCHIQ_LOG_TRACE) {
			int svc_fourcc;

			svc_fourcc = service
				? service->base.fourcc
				: VCHIQ_MAKE_FOURCC('?', '?', '?', '?');
			vchiq_log_trace(vchiq_sync_log_level,
				"Rcvd Msg %s from %c%c%c%c s:%d d:%d len:%d",
				msg_type_str(type),
				VCHIQ_FOURCC_AS_4CHARS(svc_fourcc),
				remoteport, localport, size);
			if (size > 0)
				vchiq_log_dump_mem("Rcvd", 0, header->data,
					min(16, size));
		}

		switch (type) {
		case VCHIQ_MSG_OPENACK:
			if (size >= sizeof(struct vchiq_openack_payload)) {
				const struct vchiq_openack_payload *payload =
					(struct vchiq_openack_payload *)
					header->data;
				service->peer_version = payload->version;
			}
			vchiq_log_info(vchiq_sync_log_level,
				"%d: sf OPENACK@%x,%x (%d->%d) v:%d",
				state->id, (unsigned int)header, size,
				remoteport, localport, service->peer_version);
			if (service->srvstate == VCHIQ_SRVSTATE_OPENING) {
				service->remoteport = remoteport;
				vchiq_set_service_state(service,
					VCHIQ_SRVSTATE_OPENSYNC);
				service->sync = 1;
				up(&service->remove_event);
			}
			release_message_sync(state, header);
			break;

		case VCHIQ_MSG_DATA:
			vchiq_log_trace(vchiq_sync_log_level,
				"%d: sf DATA@%x,%x (%d->%d)",
				state->id, (unsigned int)header, size,
				remoteport, localport);

			if ((service->remoteport == remoteport) &&
				(service->srvstate ==
				VCHIQ_SRVSTATE_OPENSYNC)) {
				if (make_service_callback(service,
					VCHIQ_MESSAGE_AVAILABLE, header,
					NULL) == VCHIQ_RETRY)
					vchiq_log_error(vchiq_sync_log_level,
						"synchronous callback to "
						"service %d returns "
						"VCHIQ_RETRY",
						localport);
			}
			break;

		default:
			vchiq_log_error(vchiq_sync_log_level,
				"%d: sf unexpected msgid %x@%x,%x",
				state->id, msgid, (unsigned int)header, size);
			release_message_sync(state, header);
			break;
		}

		unlock_service(service);
	}

	return 0;
}
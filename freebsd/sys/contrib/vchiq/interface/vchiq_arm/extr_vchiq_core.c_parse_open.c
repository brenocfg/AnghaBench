#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct vchiq_openack_payload {short member_0; } ;
struct vchiq_open_payload {unsigned int fourcc; short version; short version_min; } ;
typedef  int /*<<< orphan*/  ack_payload ;
struct TYPE_16__ {scalar_t__ version_common; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ VCHIQ_STATE_T ;
struct TYPE_17__ {short version; short version_min; short peer_version; scalar_t__ srvstate; unsigned int remoteport; int client_id; scalar_t__ sync; int /*<<< orphan*/  localport; } ;
typedef  TYPE_2__ VCHIQ_SERVICE_T ;
struct TYPE_18__ {int msgid; int size; scalar_t__ data; } ;
typedef  TYPE_3__ VCHIQ_HEADER_T ;
struct TYPE_19__ {int member_1; struct vchiq_openack_payload* member_0; } ;
typedef  TYPE_4__ VCHIQ_ELEMENT_T ;

/* Variables and functions */
 int /*<<< orphan*/  VCHIQ_FOURCC_AS_4CHARS (unsigned int) ; 
 int /*<<< orphan*/  VCHIQ_MAKE_MSG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  VCHIQ_MSG_CLOSE ; 
 unsigned int VCHIQ_MSG_DSTPORT (int) ; 
 int /*<<< orphan*/  VCHIQ_MSG_OPENACK ; 
 unsigned int VCHIQ_MSG_SRCPORT (int) ; 
 unsigned int VCHIQ_PORT_FREE ; 
 scalar_t__ VCHIQ_RETRY ; 
 int /*<<< orphan*/  VCHIQ_SERVICE_OPENED ; 
 scalar_t__ VCHIQ_SRVSTATE_LISTENING ; 
 int /*<<< orphan*/  VCHIQ_SRVSTATE_OPEN ; 
 int /*<<< orphan*/  VCHIQ_SRVSTATE_OPENSYNC ; 
 scalar_t__ VCHIQ_VERSION_SYNCHRONOUS_MODE ; 
 TYPE_2__* get_listening_service (TYPE_1__*,unsigned int) ; 
 scalar_t__ make_service_callback (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ queue_message (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__*,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ queue_message_sync (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_service (TYPE_2__*) ; 
 int /*<<< orphan*/  vchiq_core_log_level ; 
 int /*<<< orphan*/  vchiq_log_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vchiq_loud_error (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,short,short,short,short) ; 
 int /*<<< orphan*/  vchiq_loud_error_footer () ; 
 int /*<<< orphan*/  vchiq_loud_error_header () ; 
 int /*<<< orphan*/  vchiq_set_service_state (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
parse_open(VCHIQ_STATE_T *state, VCHIQ_HEADER_T *header)
{
	VCHIQ_SERVICE_T *service = NULL;
	int msgid, size;
	unsigned int localport, remoteport;

	msgid = header->msgid;
	size = header->size;
	//int type = VCHIQ_MSG_TYPE(msgid);
	localport = VCHIQ_MSG_DSTPORT(msgid);
	remoteport = VCHIQ_MSG_SRCPORT(msgid);
	if (size >= sizeof(struct vchiq_open_payload)) {
		const struct vchiq_open_payload *payload =
			(struct vchiq_open_payload *)header->data;
		unsigned int fourcc;

		fourcc = payload->fourcc;
		vchiq_log_info(vchiq_core_log_level,
			"%d: prs OPEN@%x (%d->'%c%c%c%c')",
			state->id, (unsigned int)header,
			localport,
			VCHIQ_FOURCC_AS_4CHARS(fourcc));

		service = get_listening_service(state, fourcc);

		if (service) {
			/* A matching service exists */
			short version = payload->version;
			short version_min = payload->version_min;
			if ((service->version < version_min) ||
				(version < service->version_min)) {
				/* Version mismatch */
				vchiq_loud_error_header();
				vchiq_loud_error("%d: service %d (%c%c%c%c) "
					"version mismatch - local (%d, min %d)"
					" vs. remote (%d, min %d)",
					state->id, service->localport,
					VCHIQ_FOURCC_AS_4CHARS(fourcc),
					service->version, service->version_min,
					version, version_min);
				vchiq_loud_error_footer();
				unlock_service(service);
				service = NULL;
				goto fail_open;
			}
			service->peer_version = version;

			if (service->srvstate == VCHIQ_SRVSTATE_LISTENING) {
				struct vchiq_openack_payload ack_payload = {
					service->version
				};
				VCHIQ_ELEMENT_T body = {
					&ack_payload,
					sizeof(ack_payload)
				};

				if (state->version_common <
				    VCHIQ_VERSION_SYNCHRONOUS_MODE)
					service->sync = 0;

				/* Acknowledge the OPEN */
				if (service->sync &&
				    (state->version_common >=
				     VCHIQ_VERSION_SYNCHRONOUS_MODE)) {
					if (queue_message_sync(state, NULL,
						VCHIQ_MAKE_MSG(
							VCHIQ_MSG_OPENACK,
							service->localport,
							remoteport),
						&body, 1, sizeof(ack_payload),
						0) == VCHIQ_RETRY)
						goto bail_not_ready;
				} else {
					if (queue_message(state, NULL,
						VCHIQ_MAKE_MSG(
							VCHIQ_MSG_OPENACK,
							service->localport,
							remoteport),
						&body, 1, sizeof(ack_payload),
						0) == VCHIQ_RETRY)
						goto bail_not_ready;
				}

				/* The service is now open */
				vchiq_set_service_state(service,
					service->sync ? VCHIQ_SRVSTATE_OPENSYNC
					: VCHIQ_SRVSTATE_OPEN);
			}

			service->remoteport = remoteport;
			service->client_id = ((int *)header->data)[1];
			if (make_service_callback(service, VCHIQ_SERVICE_OPENED,
				NULL, NULL) == VCHIQ_RETRY) {
				/* Bail out if not ready */
				service->remoteport = VCHIQ_PORT_FREE;
				goto bail_not_ready;
			}

			/* Success - the message has been dealt with */
			unlock_service(service);
			return 1;
		}
	}

fail_open:
	/* No available service, or an invalid request - send a CLOSE */
	if (queue_message(state, NULL,
		VCHIQ_MAKE_MSG(VCHIQ_MSG_CLOSE, 0, VCHIQ_MSG_SRCPORT(msgid)),
		NULL, 0, 0, 0) == VCHIQ_RETRY)
		goto bail_not_ready;

	return 1;

bail_not_ready:
	if (service)
		unlock_service(service);

	return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct vchiq_open_payload {int member_1; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  payload ;
typedef  scalar_t__ VCHIQ_STATUS_T ;
struct TYPE_10__ {int /*<<< orphan*/  fourcc; } ;
struct TYPE_11__ {int client_id; scalar_t__ srvstate; int /*<<< orphan*/  ref_count; TYPE_7__* state; int /*<<< orphan*/  remove_event; int /*<<< orphan*/  localport; int /*<<< orphan*/  version_min; int /*<<< orphan*/  version; TYPE_1__ base; } ;
typedef  TYPE_2__ VCHIQ_SERVICE_T ;
struct TYPE_12__ {int member_1; struct vchiq_open_payload* member_0; } ;
typedef  TYPE_3__ VCHIQ_ELEMENT_T ;
struct TYPE_13__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  QMFLAGS_IS_BLOCKING ; 
 scalar_t__ VCHIQ_ERROR ; 
 int /*<<< orphan*/  VCHIQ_MAKE_MSG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VCHIQ_MSG_OPEN ; 
 scalar_t__ VCHIQ_RETRY ; 
 int /*<<< orphan*/  VCHIQ_SERVICE_STATS_INC (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ VCHIQ_SRVSTATE_CLOSEWAIT ; 
 scalar_t__ VCHIQ_SRVSTATE_OPEN ; 
 scalar_t__ VCHIQ_SRVSTATE_OPENSYNC ; 
 scalar_t__ VCHIQ_SUCCESS ; 
 scalar_t__ down_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  error_count ; 
 scalar_t__ queue_message (TYPE_7__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * srvstate_names ; 
 int /*<<< orphan*/  vchiq_core_log_level ; 
 int /*<<< orphan*/  vchiq_log_error (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vchiq_release_service_internal (TYPE_2__*) ; 
 int /*<<< orphan*/  vchiq_use_service_internal (TYPE_2__*) ; 

VCHIQ_STATUS_T
vchiq_open_service_internal(VCHIQ_SERVICE_T *service, int client_id)
{
	struct vchiq_open_payload payload = {
		service->base.fourcc,
		client_id,
		service->version,
		service->version_min
	};
	VCHIQ_ELEMENT_T body = { &payload, sizeof(payload) };
	VCHIQ_STATUS_T status = VCHIQ_SUCCESS;

	service->client_id = client_id;
	vchiq_use_service_internal(service);
	status = queue_message(service->state, NULL,
		VCHIQ_MAKE_MSG(VCHIQ_MSG_OPEN, service->localport, 0),
		&body, 1, sizeof(payload), QMFLAGS_IS_BLOCKING);
	if (status == VCHIQ_SUCCESS) {
		/* Wait for the ACK/NAK */
		if (down_interruptible(&service->remove_event) != 0) {
			status = VCHIQ_RETRY;
			vchiq_release_service_internal(service);
		} else if ((service->srvstate != VCHIQ_SRVSTATE_OPEN) &&
			(service->srvstate != VCHIQ_SRVSTATE_OPENSYNC)) {
			if (service->srvstate != VCHIQ_SRVSTATE_CLOSEWAIT)
				vchiq_log_error(vchiq_core_log_level,
					"%d: osi - srvstate = %s (ref %d)",
					service->state->id,
					srvstate_names[service->srvstate],
					service->ref_count);
			status = VCHIQ_ERROR;
			VCHIQ_SERVICE_STATS_INC(service, error_count);
			vchiq_release_service_internal(service);
		}
	}
	return status;
}
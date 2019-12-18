#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VCHIQ_STATUS_T ;
struct TYPE_12__ {int srvstate; int /*<<< orphan*/  remoteport; int /*<<< orphan*/  localport; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ VCHIQ_SERVICE_T ;
typedef  int /*<<< orphan*/  VCHIQ_SERVICE_HANDLE_T ;
struct TYPE_13__ {scalar_t__ size; int /*<<< orphan*/ * data; } ;
typedef  TYPE_2__ VCHIQ_ELEMENT_T ;

/* Variables and functions */
 int /*<<< orphan*/  VCHIQ_ERROR ; 
 int /*<<< orphan*/  VCHIQ_MAKE_MSG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int VCHIQ_MAX_MSG_SIZE ; 
 int /*<<< orphan*/  VCHIQ_MSG_DATA ; 
 int /*<<< orphan*/  VCHIQ_SERVICE_STATS_INC (TYPE_1__*,int /*<<< orphan*/ ) ; 
#define  VCHIQ_SRVSTATE_OPEN 129 
#define  VCHIQ_SRVSTATE_OPENSYNC 128 
 scalar_t__ VCHIQ_SUCCESS ; 
 int /*<<< orphan*/  error_count ; 
 TYPE_1__* find_service_by_handle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_message (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,TYPE_2__ const*,unsigned int,unsigned int,int) ; 
 int /*<<< orphan*/  queue_message_sync (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,TYPE_2__ const*,unsigned int,unsigned int,int) ; 
 int /*<<< orphan*/  unlock_service (TYPE_1__*) ; 
 scalar_t__ vchiq_check_service (TYPE_1__*) ; 

VCHIQ_STATUS_T
vchiq_queue_message(VCHIQ_SERVICE_HANDLE_T handle,
	const VCHIQ_ELEMENT_T *elements, unsigned int count)
{
	VCHIQ_SERVICE_T *service = find_service_by_handle(handle);
	VCHIQ_STATUS_T status = VCHIQ_ERROR;

	unsigned int size = 0;
	unsigned int i;

	if (!service ||
		(vchiq_check_service(service) != VCHIQ_SUCCESS))
		goto error_exit;

	for (i = 0; i < (unsigned int)count; i++) {
		if (elements[i].size) {
			if (elements[i].data == NULL) {
				VCHIQ_SERVICE_STATS_INC(service, error_count);
				goto error_exit;
			}
			size += elements[i].size;
		}
	}

	if (size > VCHIQ_MAX_MSG_SIZE) {
		VCHIQ_SERVICE_STATS_INC(service, error_count);
		goto error_exit;
	}

	switch (service->srvstate) {
	case VCHIQ_SRVSTATE_OPEN:
		status = queue_message(service->state, service,
				VCHIQ_MAKE_MSG(VCHIQ_MSG_DATA,
					service->localport,
					service->remoteport),
				elements, count, size, 1);
		break;
	case VCHIQ_SRVSTATE_OPENSYNC:
		status = queue_message_sync(service->state, service,
				VCHIQ_MAKE_MSG(VCHIQ_MSG_DATA,
					service->localport,
					service->remoteport),
				elements, count, size, 1);
		break;
	default:
		status = VCHIQ_ERROR;
		break;
	}

error_exit:
	if (service)
		unlock_service(service);

	return status;
}
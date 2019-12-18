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
typedef  int /*<<< orphan*/  VCHIQ_STATUS_T ;
typedef  int /*<<< orphan*/  VCHIQ_SERVICE_HANDLE_T ;
typedef  int VCHIQ_REASON_T ;
typedef  int /*<<< orphan*/  VCHIQ_HEADER_T ;
struct TYPE_2__ {int /*<<< orphan*/  handle; int /*<<< orphan*/  callback_param; int /*<<< orphan*/  (* callback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ;int /*<<< orphan*/  queue; } ;
typedef  TYPE_1__ SHIM_SERVICE_T ;

/* Variables and functions */
#define  VCHIQ_BULK_RECEIVE_ABORTED 134 
#define  VCHIQ_BULK_RECEIVE_DONE 133 
#define  VCHIQ_BULK_TRANSMIT_ABORTED 132 
#define  VCHIQ_BULK_TRANSMIT_DONE 131 
 scalar_t__ VCHIQ_GET_SERVICE_USERDATA (int /*<<< orphan*/ ) ; 
#define  VCHIQ_MESSAGE_AVAILABLE 130 
#define  VCHIQ_SERVICE_CLOSED 129 
#define  VCHIQ_SERVICE_OPENED 128 
 int /*<<< orphan*/  VCHIQ_SUCCESS ; 
 int /*<<< orphan*/  VCHI_CALLBACK_BULK_RECEIVED ; 
 int /*<<< orphan*/  VCHI_CALLBACK_BULK_RECEIVE_ABORTED ; 
 int /*<<< orphan*/  VCHI_CALLBACK_BULK_SENT ; 
 int /*<<< orphan*/  VCHI_CALLBACK_BULK_TRANSMIT_ABORTED ; 
 int /*<<< orphan*/  VCHI_CALLBACK_MSG_AVAILABLE ; 
 int /*<<< orphan*/  VCHI_CALLBACK_SERVICE_CLOSED ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  vchiq_release_message (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vchiu_queue_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static VCHIQ_STATUS_T shim_callback(VCHIQ_REASON_T reason,
	VCHIQ_HEADER_T *header, VCHIQ_SERVICE_HANDLE_T handle, void *bulk_user)
{
	SHIM_SERVICE_T *service =
		(SHIM_SERVICE_T *)VCHIQ_GET_SERVICE_USERDATA(handle);

        if (!service->callback)
		goto release;

	switch (reason) {
	case VCHIQ_MESSAGE_AVAILABLE:
		vchiu_queue_push(&service->queue, header);

		service->callback(service->callback_param,
				  VCHI_CALLBACK_MSG_AVAILABLE, NULL);

		goto done;
		break;

	case VCHIQ_BULK_TRANSMIT_DONE:
		service->callback(service->callback_param,
				  VCHI_CALLBACK_BULK_SENT, bulk_user);
		break;

	case VCHIQ_BULK_RECEIVE_DONE:
		service->callback(service->callback_param,
				  VCHI_CALLBACK_BULK_RECEIVED, bulk_user);
		break;

	case VCHIQ_SERVICE_CLOSED:
		service->callback(service->callback_param,
				  VCHI_CALLBACK_SERVICE_CLOSED, NULL);
		break;

	case VCHIQ_SERVICE_OPENED:
		/* No equivalent VCHI reason */
		break;

	case VCHIQ_BULK_TRANSMIT_ABORTED:
		service->callback(service->callback_param,
				  VCHI_CALLBACK_BULK_TRANSMIT_ABORTED,
				  bulk_user);
		break;

	case VCHIQ_BULK_RECEIVE_ABORTED:
		service->callback(service->callback_param,
				  VCHI_CALLBACK_BULK_RECEIVE_ABORTED,
				  bulk_user);
		break;

	default:
		WARN(1, "not supported\n");
		break;
	}

release:
        vchiq_release_message(service->handle, header);
done:
	return VCHIQ_SUCCESS;
}
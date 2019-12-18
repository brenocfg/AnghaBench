#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  status; } ;
union ccb {TYPE_1__ ccb_h; } ;
struct TYPE_6__ {int /*<<< orphan*/  remote_device_handle; } ;
struct ISCI_TASK_REQUEST {int /*<<< orphan*/  sci_object; union ccb* ccb; TYPE_3__ parent; } ;
struct ISCI_REQUEST {int dummy; } ;
struct ISCI_REMOTE_DEVICE {scalar_t__ is_resetting; int /*<<< orphan*/  sci_object; int /*<<< orphan*/  index; TYPE_2__* domain; int /*<<< orphan*/  pending_device_reset_element; } ;
struct ISCI_CONTROLLER {int /*<<< orphan*/  scif_controller_handle; int /*<<< orphan*/  request_pool; int /*<<< orphan*/  index; int /*<<< orphan*/  pending_device_reset_list; } ;
struct TYPE_5__ {int /*<<< orphan*/  index; struct ISCI_CONTROLLER* controller; } ;
typedef  int /*<<< orphan*/  SCI_TASK_STATUS ;
typedef  scalar_t__ SCI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_REQUEUE_REQ ; 
 int /*<<< orphan*/  CAM_STATUS_MASK ; 
 int /*<<< orphan*/  SCI_CONTROLLER_INVALID_IO_TAG ; 
 scalar_t__ SCI_SUCCESS ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  isci_log_message (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isci_task_request_complete (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_fast_list_insert_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ sci_pool_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_pool_get (int /*<<< orphan*/ ,struct ISCI_REQUEST*) ; 
 scalar_t__ scif_controller_start_task (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ scif_task_request_construct (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xpt_done (union ccb*) ; 

void
isci_remote_device_reset(struct ISCI_REMOTE_DEVICE *remote_device,
    union ccb *ccb)
{
	struct ISCI_CONTROLLER *controller = remote_device->domain->controller;
	struct ISCI_REQUEST *request;
	struct ISCI_TASK_REQUEST *task_request;
	SCI_STATUS status;

	if (remote_device->is_resetting == TRUE) {
		/* device is already being reset, so return immediately */
		return;
	}

	if (sci_pool_empty(controller->request_pool)) {
		/* No requests are available in our request pool.  If this reset is tied
		 *  to a CCB, ask CAM to requeue it.  Otherwise, we need to put it on our
		 *  pending device reset list, so that the reset will occur when a request
		 *  frees up.
		 */
		if (ccb == NULL)
			sci_fast_list_insert_tail(
			    &controller->pending_device_reset_list,
			    &remote_device->pending_device_reset_element);
		else {
			ccb->ccb_h.status &= ~CAM_STATUS_MASK;
			ccb->ccb_h.status |= CAM_REQUEUE_REQ;
			xpt_done(ccb);
		}
		return;
	}

	isci_log_message(0, "ISCI",
	    "Sending reset to device on controller %d domain %d CAM index %d\n",
	    controller->index, remote_device->domain->index,
	    remote_device->index
	);

	sci_pool_get(controller->request_pool, request);
	task_request = (struct ISCI_TASK_REQUEST *)request;

	task_request->parent.remote_device_handle = remote_device->sci_object;
	task_request->ccb = ccb;

	remote_device->is_resetting = TRUE;

	status = (SCI_STATUS) scif_task_request_construct(
	    controller->scif_controller_handle, remote_device->sci_object,
	    SCI_CONTROLLER_INVALID_IO_TAG, (void *)task_request,
	    (void *)((char*)task_request + sizeof(struct ISCI_TASK_REQUEST)),
	    &task_request->sci_object);

	if (status != SCI_SUCCESS) {
		isci_task_request_complete(controller->scif_controller_handle,
		    remote_device->sci_object, task_request->sci_object,
		    (SCI_TASK_STATUS)status);
		return;
	}

	status = (SCI_STATUS)scif_controller_start_task(
	    controller->scif_controller_handle, remote_device->sci_object,
	    task_request->sci_object, SCI_CONTROLLER_INVALID_IO_TAG);

	if (status != SCI_SUCCESS) {
		isci_task_request_complete(
		    controller->scif_controller_handle,
		    remote_device->sci_object, task_request->sci_object,
		    (SCI_TASK_STATUS)status);
		return;
	}
}
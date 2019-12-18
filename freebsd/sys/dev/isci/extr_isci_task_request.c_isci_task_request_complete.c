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
struct TYPE_4__ {int /*<<< orphan*/  status; } ;
union ccb {TYPE_2__ ccb_h; } ;
struct ISCI_TASK_REQUEST {union ccb* ccb; } ;
struct ISCI_REQUEST {int dummy; } ;
struct ISCI_REMOTE_DEVICE {TYPE_1__* domain; scalar_t__ is_resetting; } ;
struct ISCI_CONTROLLER {scalar_t__ is_frozen; int /*<<< orphan*/  pending_device_reset_list; int /*<<< orphan*/  request_pool; int /*<<< orphan*/  sim; int /*<<< orphan*/  fail_on_task_timeout; } ;
struct TYPE_3__ {int /*<<< orphan*/  sci_object; } ;
typedef  scalar_t__ SCI_TASK_STATUS ;
typedef  int /*<<< orphan*/  SCI_TASK_REQUEST_HANDLE_T ;
typedef  int /*<<< orphan*/  SCI_REMOTE_DEVICE_HANDLE_T ;
typedef  int /*<<< orphan*/  SCI_CONTROLLER_HANDLE_T ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_REQ_CMP ; 
 int /*<<< orphan*/  CAM_STATUS_MASK ; 
 scalar_t__ FALSE ; 
#define  SCI_FAILURE_TIMEOUT 138 
#define  SCI_TASK_FAILURE 137 
#define  SCI_TASK_FAILURE_CONTROLLER_SPECIFIC_ERR 136 
#define  SCI_TASK_FAILURE_INSUFFICIENT_RESOURCES 135 
#define  SCI_TASK_FAILURE_INVALID_PARAMETER_VALUE 134 
#define  SCI_TASK_FAILURE_INVALID_STATE 133 
#define  SCI_TASK_FAILURE_INVALID_TAG 132 
#define  SCI_TASK_FAILURE_RESPONSE_VALID 131 
#define  SCI_TASK_FAILURE_TERMINATED 130 
#define  SCI_TASK_FAILURE_UNSUPPORTED_PROTOCOL 129 
#define  SCI_TASK_SUCCESS 128 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  isci_log_message (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  isci_remote_device_release_device_queue (struct ISCI_REMOTE_DEVICE*) ; 
 int /*<<< orphan*/  isci_remote_device_reset (struct ISCI_REMOTE_DEVICE*,union ccb*) ; 
 struct ISCI_REMOTE_DEVICE* sci_fast_list_remove_head (int /*<<< orphan*/ *) ; 
 scalar_t__ sci_object_get_association (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_pool_put (int /*<<< orphan*/ ,struct ISCI_REQUEST*) ; 
 int /*<<< orphan*/  scif_cb_domain_device_removed (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_done (union ccb*) ; 
 int /*<<< orphan*/  xpt_release_simq (int /*<<< orphan*/ ,scalar_t__) ; 

void
isci_task_request_complete(SCI_CONTROLLER_HANDLE_T scif_controller,
    SCI_REMOTE_DEVICE_HANDLE_T remote_device,
    SCI_TASK_REQUEST_HANDLE_T task_request, SCI_TASK_STATUS completion_status)
{
	struct ISCI_TASK_REQUEST *isci_task_request =
		(struct ISCI_TASK_REQUEST *)sci_object_get_association(task_request);
	struct ISCI_CONTROLLER *isci_controller =
		(struct ISCI_CONTROLLER *)sci_object_get_association(scif_controller);
	struct ISCI_REMOTE_DEVICE *isci_remote_device =
		(struct ISCI_REMOTE_DEVICE *)sci_object_get_association(remote_device);
	struct ISCI_REMOTE_DEVICE *pending_remote_device;
	BOOL retry_task = FALSE;
	union ccb *ccb = isci_task_request->ccb;

	isci_remote_device->is_resetting = FALSE;

	switch ((int)completion_status) {
	case SCI_TASK_SUCCESS:
	case SCI_TASK_FAILURE_RESPONSE_VALID:
		break;

	case SCI_TASK_FAILURE_INVALID_STATE:
		retry_task = TRUE;
		isci_log_message(0, "ISCI",
		    "task failure (invalid state) - retrying\n");
		break;

	case SCI_TASK_FAILURE_INSUFFICIENT_RESOURCES:
		retry_task = TRUE;
		isci_log_message(0, "ISCI",
		    "task failure (insufficient resources) - retrying\n");
		break;

	case SCI_FAILURE_TIMEOUT:
		if (isci_controller->fail_on_task_timeout) {
			retry_task = FALSE;
			isci_log_message(0, "ISCI",
			    "task timeout - not retrying\n");
			scif_cb_domain_device_removed(scif_controller,
			    isci_remote_device->domain->sci_object,
			    remote_device);
		} else {
			retry_task = TRUE;
			isci_log_message(0, "ISCI",
			    "task timeout - retrying\n");
		}
		break;

	case SCI_TASK_FAILURE:
	case SCI_TASK_FAILURE_UNSUPPORTED_PROTOCOL:
	case SCI_TASK_FAILURE_INVALID_TAG:
	case SCI_TASK_FAILURE_CONTROLLER_SPECIFIC_ERR:
	case SCI_TASK_FAILURE_TERMINATED:
	case SCI_TASK_FAILURE_INVALID_PARAMETER_VALUE:
		isci_log_message(0, "ISCI",
		    "unhandled task completion code 0x%x\n", completion_status);
		break;

	default:
		isci_log_message(0, "ISCI",
		    "unhandled task completion code 0x%x\n", completion_status);
		break;
	}

	if (isci_controller->is_frozen == TRUE) {
		isci_controller->is_frozen = FALSE;
		xpt_release_simq(isci_controller->sim, TRUE);
	}

	sci_pool_put(isci_controller->request_pool,
	    (struct ISCI_REQUEST *)isci_task_request);

	/* Make sure we release the device queue, since it may have been frozen
	 *  if someone tried to start an I/O while the task was in progress.
	 */
	isci_remote_device_release_device_queue(isci_remote_device);

	if (retry_task == TRUE)
		isci_remote_device_reset(isci_remote_device, ccb);
	else {
		pending_remote_device = sci_fast_list_remove_head(
		    &isci_controller->pending_device_reset_list);

		if (pending_remote_device != NULL) {
			/* Any resets that were triggered from an XPT_RESET_DEV
			 *  CCB are never put in the pending list if the request
			 *  pool is empty - they are given back to CAM to be
			 *  requeued.  So we will alawys pass NULL here,
			 *  denoting that there is no CCB associated with the
			 *  device reset.
			 */
			isci_remote_device_reset(pending_remote_device, NULL);
		} else if (ccb != NULL) {
			/* There was a CCB associated with this reset, so mark
			 *  it complete and return it to CAM.
			 */
			ccb->ccb_h.status &= ~CAM_STATUS_MASK;
			ccb->ccb_h.status |= CAM_REQ_CMP;
			xpt_done(ccb);
		}
	}
}
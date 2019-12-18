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
struct TYPE_4__ {size_t target_id; int /*<<< orphan*/  flags; int /*<<< orphan*/  status; } ;
union ccb {TYPE_2__ ccb_h; } ;
typedef  size_t target_id_t ;
struct ISCI_REQUEST {int dummy; } ;
struct ISCI_REMOTE_DEVICE {scalar_t__ is_resetting; int /*<<< orphan*/  sci_object; } ;
struct TYPE_3__ {int /*<<< orphan*/  dma_map; int /*<<< orphan*/  dma_tag; int /*<<< orphan*/  remote_device_handle; } ;
struct ISCI_IO_REQUEST {TYPE_1__ parent; scalar_t__ current_sge_index; union ccb* ccb; } ;
struct ISCI_CONTROLLER {int /*<<< orphan*/  sim; int /*<<< orphan*/  request_pool; int /*<<< orphan*/  is_frozen; struct ISCI_REMOTE_DEVICE** remote_device; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  CAM_DEV_NOT_THERE ; 
 int /*<<< orphan*/  CAM_RELEASE_SIMQ ; 
 int /*<<< orphan*/  CAM_REQUEUE_REQ ; 
 int /*<<< orphan*/  CAM_SIM_QUEUED ; 
 int /*<<< orphan*/  CAM_STATUS_MASK ; 
 int EINPROGRESS ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int bus_dmamap_load_ccb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union ccb*,int /*<<< orphan*/ ,struct ISCI_IO_REQUEST*,int) ; 
 int /*<<< orphan*/  isci_io_request_construct ; 
 scalar_t__ sci_pool_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_pool_get (int /*<<< orphan*/ ,struct ISCI_REQUEST*) ; 
 int /*<<< orphan*/  xpt_done (union ccb*) ; 
 int /*<<< orphan*/  xpt_freeze_simq (int /*<<< orphan*/ ,int) ; 

void
isci_io_request_execute_scsi_io(union ccb *ccb,
    struct ISCI_CONTROLLER *controller)
{
	target_id_t target_id = ccb->ccb_h.target_id;
	struct ISCI_REQUEST *request;
	struct ISCI_IO_REQUEST *io_request;
	struct ISCI_REMOTE_DEVICE *device =
	    controller->remote_device[target_id];
	int error;

	if (device == NULL) {
		ccb->ccb_h.status &= ~CAM_SIM_QUEUED;
		ccb->ccb_h.status &= ~CAM_STATUS_MASK;
		ccb->ccb_h.status |= CAM_DEV_NOT_THERE;
		xpt_done(ccb);
		return;
	}

	if (sci_pool_empty(controller->request_pool)) {
		ccb->ccb_h.status &= ~CAM_SIM_QUEUED;
		ccb->ccb_h.status &= ~CAM_STATUS_MASK;
		ccb->ccb_h.status |= CAM_REQUEUE_REQ;
		xpt_freeze_simq(controller->sim, 1);
		controller->is_frozen = TRUE;
		xpt_done(ccb);
		return;
	}

	ASSERT(device->is_resetting == FALSE);

	sci_pool_get(controller->request_pool, request);
	io_request = (struct ISCI_IO_REQUEST *)request;

	io_request->ccb = ccb;
	io_request->current_sge_index = 0;
	io_request->parent.remote_device_handle = device->sci_object;

	error = bus_dmamap_load_ccb(io_request->parent.dma_tag,
	    io_request->parent.dma_map, ccb,
	    isci_io_request_construct, io_request, 0x0);
	/* A resource shortage from BUSDMA will be automatically
	 * continued at a later point, pushing the CCB processing
	 * forward, which will in turn unfreeze the simq.
	 */
	if (error == EINPROGRESS) {
		xpt_freeze_simq(controller->sim, 1);
		ccb->ccb_h.flags |= CAM_RELEASE_SIMQ;
	}
}
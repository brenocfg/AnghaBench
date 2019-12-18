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
struct TYPE_4__ {int timeout; int /*<<< orphan*/  status; } ;
union ccb {TYPE_2__ ccb_h; } ;
struct TYPE_3__ {int /*<<< orphan*/  timer; int /*<<< orphan*/  controller_handle; int /*<<< orphan*/  dma_map; int /*<<< orphan*/  dma_tag; int /*<<< orphan*/ * remote_device_handle; } ;
struct ISCI_IO_REQUEST {int num_segments; TYPE_1__ parent; int /*<<< orphan*/  sci_object; union ccb* ccb; int /*<<< orphan*/ * sge; } ;
typedef  int /*<<< orphan*/  bus_dma_segment_t ;
typedef  scalar_t__ SCI_STATUS ;
typedef  int /*<<< orphan*/  SCI_REMOTE_DEVICE_HANDLE_T ;
typedef  int /*<<< orphan*/  SCI_IO_STATUS ;

/* Variables and functions */
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  CAM_REQ_INVALID ; 
 int CAM_TIME_INFINITY ; 
 int SBT_1MS ; 
 int /*<<< orphan*/  SCI_CONTROLLER_INVALID_IO_TAG ; 
 scalar_t__ SCI_SUCCESS ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  callout_reset_sbt (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ISCI_IO_REQUEST*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isci_io_request_complete (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ISCI_IO_REQUEST*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isci_io_request_timeout ; 
 int /*<<< orphan*/  sci_object_set_association (int /*<<< orphan*/ ,struct ISCI_IO_REQUEST*) ; 
 scalar_t__ scif_controller_start_io (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ scif_io_request_construct (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xpt_done (union ccb*) ; 

__attribute__((used)) static void
isci_io_request_construct(void *arg, bus_dma_segment_t *seg, int nseg,
    int error)
{
	union ccb *ccb;
	struct ISCI_IO_REQUEST *io_request = (struct ISCI_IO_REQUEST *)arg;
	SCI_REMOTE_DEVICE_HANDLE_T *device = io_request->parent.remote_device_handle;
	SCI_STATUS status;

	io_request->num_segments = nseg;
	io_request->sge = seg;
	ccb = io_request->ccb;

	if (error != 0) {
		ccb->ccb_h.status = CAM_REQ_INVALID;
		xpt_done(ccb);
		return;
	}

	status = scif_io_request_construct(
	    io_request->parent.controller_handle,
	    io_request->parent.remote_device_handle,
	    SCI_CONTROLLER_INVALID_IO_TAG, (void *)io_request,
	    (void *)((char*)io_request + sizeof(struct ISCI_IO_REQUEST)),
	    &io_request->sci_object);

	if (status != SCI_SUCCESS) {
		isci_io_request_complete(io_request->parent.controller_handle,
		    device, io_request, (SCI_IO_STATUS)status);
		return;
	}

	sci_object_set_association(io_request->sci_object, io_request);

	bus_dmamap_sync(io_request->parent.dma_tag, io_request->parent.dma_map,
	    BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);

	status = (SCI_STATUS)scif_controller_start_io(
	    io_request->parent.controller_handle, device,
	    io_request->sci_object, SCI_CONTROLLER_INVALID_IO_TAG);

	if (status != SCI_SUCCESS) {
		isci_io_request_complete(io_request->parent.controller_handle,
		    device, io_request, (SCI_IO_STATUS)status);
		return;
	}

	if (ccb->ccb_h.timeout != CAM_TIME_INFINITY)
		callout_reset_sbt(&io_request->parent.timer,
		    SBT_1MS * ccb->ccb_h.timeout, 0, isci_io_request_timeout,
		    io_request, 0);
}
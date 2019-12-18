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
struct TYPE_2__ {int /*<<< orphan*/  path; } ;
union ccb {TYPE_1__ ccb_h; } ;
typedef  size_t uint32_t ;
struct ISCI_REMOTE_DEVICE {size_t index; } ;
struct ISCI_CONTROLLER {int /*<<< orphan*/  sim; scalar_t__ has_been_scanned; struct ISCI_REMOTE_DEVICE** remote_device; } ;
typedef  int /*<<< orphan*/  SCI_REMOTE_DEVICE_HANDLE_T ;
typedef  int /*<<< orphan*/  SCI_DOMAIN_HANDLE_T ;
typedef  int /*<<< orphan*/  SCI_CONTROLLER_HANDLE_T ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_LUN_WILDCARD ; 
 int /*<<< orphan*/  cam_sim_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isci_remote_device_release_device_queue (struct ISCI_REMOTE_DEVICE*) ; 
 void* sci_object_get_association (int /*<<< orphan*/ ) ; 
 union ccb* xpt_alloc_ccb_nowait () ; 
 int /*<<< orphan*/  xpt_create_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_rescan (union ccb*) ; 

void
scif_cb_remote_device_ready(SCI_CONTROLLER_HANDLE_T controller,
    SCI_DOMAIN_HANDLE_T domain, SCI_REMOTE_DEVICE_HANDLE_T remote_device)
{
	struct ISCI_REMOTE_DEVICE *isci_remote_device =
	    sci_object_get_association(remote_device);
	struct ISCI_CONTROLLER *isci_controller =
	    sci_object_get_association(controller);
	uint32_t device_index = isci_remote_device->index;

	if (isci_controller->remote_device[device_index] == NULL) {
		/* This new device is now ready, so put it in the controller's
		 *  remote device list so it is visible to CAM.
		 */
		isci_controller->remote_device[device_index] =
		    isci_remote_device;

		if (isci_controller->has_been_scanned) {
			/* The sim object has been scanned at least once
			 *  already.  In that case, create a CCB to instruct
			 *  CAM to rescan this device.
			 * If the sim object has not been scanned, this device
			 *  will get scanned as part of the initial scan.
			 */
			union ccb *ccb = xpt_alloc_ccb_nowait();

			xpt_create_path(&ccb->ccb_h.path, NULL,
			    cam_sim_path(isci_controller->sim),
			    isci_remote_device->index, CAM_LUN_WILDCARD);

			xpt_rescan(ccb);
		}
	}

	isci_remote_device_release_device_queue(isci_remote_device);
}
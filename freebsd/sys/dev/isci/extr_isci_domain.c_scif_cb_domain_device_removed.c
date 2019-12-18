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
typedef  int /*<<< orphan*/  uint32_t ;
struct ISCI_REMOTE_DEVICE {size_t index; } ;
struct ISCI_DOMAIN {struct ISCI_REMOTE_DEVICE* da_remote_device; } ;
struct ISCI_CONTROLLER {int /*<<< orphan*/  remote_device_pool; int /*<<< orphan*/ ** remote_device; int /*<<< orphan*/  sim; } ;
typedef  int /*<<< orphan*/  SCI_REMOTE_DEVICE_HANDLE_T ;
typedef  int /*<<< orphan*/  SCI_DOMAIN_HANDLE_T ;
typedef  int /*<<< orphan*/  SCI_CONTROLLER_HANDLE_T ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_LUN_WILDCARD ; 
 int /*<<< orphan*/  cam_sim_path (int /*<<< orphan*/ ) ; 
 scalar_t__ sci_object_get_association (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_pool_put (int /*<<< orphan*/ ,struct ISCI_REMOTE_DEVICE*) ; 
 int /*<<< orphan*/  scif_remote_device_destruct (int /*<<< orphan*/ ) ; 
 union ccb* xpt_alloc_ccb_nowait () ; 
 int /*<<< orphan*/  xpt_create_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_rescan (union ccb*) ; 

void
scif_cb_domain_device_removed(SCI_CONTROLLER_HANDLE_T controller,
    SCI_DOMAIN_HANDLE_T domain, SCI_REMOTE_DEVICE_HANDLE_T remote_device)
{
	struct ISCI_REMOTE_DEVICE *isci_remote_device =
	    (struct ISCI_REMOTE_DEVICE *)sci_object_get_association(remote_device);
	struct ISCI_DOMAIN *isci_domain =
	    (struct ISCI_DOMAIN *)sci_object_get_association(domain);
	struct ISCI_CONTROLLER *isci_controller =
	    (struct ISCI_CONTROLLER *)sci_object_get_association(controller);
	uint32_t path = cam_sim_path(isci_controller->sim);
	union ccb *ccb = xpt_alloc_ccb_nowait();

	isci_controller->remote_device[isci_remote_device->index] = NULL;

	xpt_create_path(&ccb->ccb_h.path, NULL, path,
	    isci_remote_device->index, CAM_LUN_WILDCARD);

	xpt_rescan(ccb);

	scif_remote_device_destruct(remote_device);

	/*
	 * Only put the remote device back into the pool if it was an
	 *  expander-attached device.
	 */
	if (isci_remote_device != isci_domain->da_remote_device)
		sci_pool_put(isci_controller->remote_device_pool,
		    isci_remote_device);
}
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
typedef  int /*<<< orphan*/  target_id_t ;
struct cam_periph {int dummy; } ;
struct cam_path {struct cam_ed* device; struct cam_et* target; struct cam_eb* bus; struct cam_periph* periph; } ;
struct cam_et {int dummy; } ;
struct cam_ed {int dummy; } ;
struct cam_eb {int /*<<< orphan*/  eb_mtx; TYPE_2__* xport; } ;
typedef  int /*<<< orphan*/  path_id_t ;
typedef  int /*<<< orphan*/  lun_id_t ;
typedef  scalar_t__ cam_status ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {struct cam_ed* (* alloc_device ) (struct cam_eb*,struct cam_et*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DEBUG (struct cam_path*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CAM_DEBUG_TRACE ; 
 scalar_t__ CAM_PATH_INVALID ; 
 scalar_t__ CAM_REQ_CMP ; 
 scalar_t__ CAM_RESRC_UNAVAIL ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 struct cam_ed* stub1 (struct cam_eb*,struct cam_et*,int /*<<< orphan*/ ) ; 
 struct cam_et* xpt_alloc_target (struct cam_eb*,int /*<<< orphan*/ ) ; 
 struct cam_eb* xpt_find_bus (int /*<<< orphan*/ ) ; 
 struct cam_ed* xpt_find_device (struct cam_et*,int /*<<< orphan*/ ) ; 
 struct cam_et* xpt_find_target (struct cam_eb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_lock_buses () ; 
 int /*<<< orphan*/  xpt_release_bus (struct cam_eb*) ; 
 int /*<<< orphan*/  xpt_release_device (struct cam_ed*) ; 
 int /*<<< orphan*/  xpt_release_target (struct cam_et*) ; 
 int /*<<< orphan*/  xpt_unlock_buses () ; 

cam_status
xpt_compile_path(struct cam_path *new_path, struct cam_periph *perph,
		 path_id_t path_id, target_id_t target_id, lun_id_t lun_id)
{
	struct	     cam_eb *bus;
	struct	     cam_et *target;
	struct	     cam_ed *device;
	cam_status   status;

	status = CAM_REQ_CMP;	/* Completed without error */
	target = NULL;		/* Wildcarded */
	device = NULL;		/* Wildcarded */

	/*
	 * We will potentially modify the EDT, so block interrupts
	 * that may attempt to create cam paths.
	 */
	bus = xpt_find_bus(path_id);
	if (bus == NULL) {
		status = CAM_PATH_INVALID;
	} else {
		xpt_lock_buses();
		mtx_lock(&bus->eb_mtx);
		target = xpt_find_target(bus, target_id);
		if (target == NULL) {
			/* Create one */
			struct cam_et *new_target;

			new_target = xpt_alloc_target(bus, target_id);
			if (new_target == NULL) {
				status = CAM_RESRC_UNAVAIL;
			} else {
				target = new_target;
			}
		}
		xpt_unlock_buses();
		if (target != NULL) {
			device = xpt_find_device(target, lun_id);
			if (device == NULL) {
				/* Create one */
				struct cam_ed *new_device;

				new_device =
				    (*(bus->xport->ops->alloc_device))(bus,
								       target,
								       lun_id);
				if (new_device == NULL) {
					status = CAM_RESRC_UNAVAIL;
				} else {
					device = new_device;
				}
			}
		}
		mtx_unlock(&bus->eb_mtx);
	}

	/*
	 * Only touch the user's data if we are successful.
	 */
	if (status == CAM_REQ_CMP) {
		new_path->periph = perph;
		new_path->bus = bus;
		new_path->target = target;
		new_path->device = device;
		CAM_DEBUG(new_path, CAM_DEBUG_TRACE, ("xpt_compile_path\n"));
	} else {
		if (device != NULL)
			xpt_release_device(device);
		if (target != NULL)
			xpt_release_target(target);
		if (bus != NULL)
			xpt_release_bus(bus);
	}
	return (status);
}
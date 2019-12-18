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
struct TYPE_3__ {int /*<<< orphan*/ * device; struct cam_et* target; struct cam_eb* bus; } ;
struct TYPE_4__ {int position_type; scalar_t__* generations; TYPE_1__ cookie; } ;
struct ccb_dev_match {TYPE_2__ pos; int /*<<< orphan*/  status; } ;
struct cam_et {scalar_t__ generation; struct cam_eb* bus; } ;
struct cam_ed {int /*<<< orphan*/  refcount; } ;
struct cam_eb {int /*<<< orphan*/  eb_mtx; } ;

/* Variables and functions */
 size_t CAM_DEV_GENERATION ; 
 int /*<<< orphan*/  CAM_DEV_MATCH_LIST_CHANGED ; 
 int CAM_DEV_POS_BUS ; 
 int CAM_DEV_POS_DEVICE ; 
 int CAM_DEV_POS_TARGET ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int xptdevicetraverse (struct cam_et*,struct cam_ed*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  xptedtdevicefunc ; 

__attribute__((used)) static int
xptedttargetfunc(struct cam_et *target, void *arg)
{
	struct ccb_dev_match *cdm;
	struct cam_eb *bus;
	struct cam_ed *device;

	cdm = (struct ccb_dev_match *)arg;
	bus = target->bus;

	/*
	 * If there is a device list generation recorded, check it to
	 * make sure the device list hasn't changed.
	 */
	mtx_lock(&bus->eb_mtx);
	if ((cdm->pos.position_type & CAM_DEV_POS_BUS)
	 && (cdm->pos.cookie.bus == bus)
	 && (cdm->pos.position_type & CAM_DEV_POS_TARGET)
	 && (cdm->pos.cookie.target == target)
	 && (cdm->pos.position_type & CAM_DEV_POS_DEVICE)
	 && (cdm->pos.cookie.device != NULL)) {
		if (cdm->pos.generations[CAM_DEV_GENERATION] !=
		    target->generation) {
			mtx_unlock(&bus->eb_mtx);
			cdm->status = CAM_DEV_MATCH_LIST_CHANGED;
			return(0);
		}
		device = (struct cam_ed *)cdm->pos.cookie.device;
		device->refcount++;
	} else
		device = NULL;
	mtx_unlock(&bus->eb_mtx);

	return (xptdevicetraverse(target, device, xptedtdevicefunc, arg));
}
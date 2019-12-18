#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct cam_path {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  sim; scalar_t__ sim_registered; } ;
struct TYPE_9__ {TYPE_1__ os_specific; } ;
typedef  TYPE_2__ pqisrc_softstate_t ;
struct TYPE_10__ {int /*<<< orphan*/  lun; int /*<<< orphan*/  target; } ;
typedef  TYPE_3__ pqi_scsi_dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  AC_LOST_DEVICE ; 
 scalar_t__ CAM_REQ_CMP ; 
 int /*<<< orphan*/  DBG_ERR (char*) ; 
 int /*<<< orphan*/  DBG_FUNC (char*) ; 
 int /*<<< orphan*/  cam_sim_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pqisrc_free_device (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  xpt_async (int /*<<< orphan*/ ,struct cam_path*,int /*<<< orphan*/ *) ; 
 scalar_t__ xpt_create_path (struct cam_path**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_free_path (struct cam_path*) ; 

void os_remove_device(pqisrc_softstate_t *softs,
        pqi_scsi_dev_t *device) {
	struct cam_path *tmppath;

	DBG_FUNC("IN\n");
	
	if(softs->os_specific.sim_registered) {
		if (xpt_create_path(&tmppath, NULL, 
			cam_sim_path(softs->os_specific.sim),
			device->target, device->lun) != CAM_REQ_CMP) {
			DBG_ERR("unable to create path for async event");
			return;
		}
		xpt_async(AC_LOST_DEVICE, tmppath, NULL);
		xpt_free_path(tmppath);
		pqisrc_free_device(softs, device);
	}

	DBG_FUNC("OUT\n");

}
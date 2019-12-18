#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {size_t target_id; size_t target_lun; } ;
union ccb {TYPE_1__ ccb_h; } ;
typedef  size_t uint32_t ;
struct TYPE_10__ {size_t tag; int status; } ;
typedef  TYPE_2__ rcb_t ;
struct TYPE_11__ {int /*<<< orphan*/  taglist; TYPE_2__* rcb; TYPE_4__*** device_list; } ;
typedef  TYPE_3__ pqisrc_softstate_t ;
struct TYPE_12__ {int reset_in_progress; } ;
typedef  TYPE_4__ pqi_scsi_dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_ERR (char*,size_t) ; 
 int /*<<< orphan*/  DBG_FUNC (char*,...) ; 
 int PQI_STATUS_FAILURE ; 
 int PQI_STATUS_SUCCESS ; 
 int REQUEST_SUCCESS ; 
 int /*<<< orphan*/  SOP_TASK_MANAGEMENT_LUN_RESET ; 
 size_t pqisrc_get_tag (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pqisrc_put_tag (int /*<<< orphan*/ *,size_t) ; 
 int pqisrc_send_tmf (TYPE_3__*,TYPE_4__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pqisrc_target_reset( pqisrc_softstate_t *softs,  union ccb *ccb)
{
	pqi_scsi_dev_t *devp = softs->device_list[ccb->ccb_h.target_id][ccb->ccb_h.target_lun];
	rcb_t *rcb = NULL;
	uint32_t tag = 0;
	int rval = PQI_STATUS_SUCCESS;

	DBG_FUNC("IN\n");

	if (devp == NULL) {
		DBG_ERR("bad target t%d\n", ccb->ccb_h.target_id);
		return (-1);
	}

	tag = pqisrc_get_tag(&softs->taglist);
	rcb = &softs->rcb[tag];
	rcb->tag = tag;

	devp->reset_in_progress = true;
	rval = pqisrc_send_tmf(softs, devp, rcb, 0,
		SOP_TASK_MANAGEMENT_LUN_RESET);
	if (PQI_STATUS_SUCCESS == rval) {
		rval = rcb->status;
	}
	devp->reset_in_progress = false;
	pqisrc_put_tag(&softs->taglist,rcb->tag);

	DBG_FUNC("OUT rval = %d\n", rval);

	return ((rval == REQUEST_SUCCESS) ?
		PQI_STATUS_SUCCESS : PQI_STATUS_FAILURE);
}
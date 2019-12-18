#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* entries; } ;
struct TYPE_11__ {int /*<<< orphan*/  status; TYPE_2__ sim_priv; } ;
union ccb {TYPE_3__ ccb_h; } ;
typedef  size_t uint32_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_12__ {size_t tag; int status; int /*<<< orphan*/  dvp; scalar_t__ resp_qid; } ;
typedef  TYPE_4__ rcb_t ;
struct TYPE_13__ {int /*<<< orphan*/  taglist; TYPE_4__* rcb; } ;
typedef  TYPE_5__ pqisrc_softstate_t ;
struct TYPE_9__ {TYPE_4__* ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_REQ_ABORTED ; 
 int /*<<< orphan*/  DBG_FUNC (char*,...) ; 
 int PQI_STATUS_SUCCESS ; 
 int REQUEST_SUCCESS ; 
 int /*<<< orphan*/  SOP_TASK_MANAGEMENT_FUNCTION_ABORT_TASK ; 
 size_t pqisrc_get_tag (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pqisrc_put_tag (int /*<<< orphan*/ *,size_t) ; 
 int pqisrc_send_tmf (TYPE_5__*,int /*<<< orphan*/ ,TYPE_4__*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pqisrc_scsi_abort_task(pqisrc_softstate_t *softs,  union ccb *ccb)
{
	rcb_t *rcb = ccb->ccb_h.sim_priv.entries[0].ptr;
	uint32_t abort_tag = rcb->tag;
	uint32_t tag = 0;
	int rval = PQI_STATUS_SUCCESS;
	uint16_t qid;

    DBG_FUNC("IN\n");

	qid = (uint16_t)rcb->resp_qid;

	tag = pqisrc_get_tag(&softs->taglist);
	rcb = &softs->rcb[tag];
	rcb->tag = tag;
	rcb->resp_qid = qid;

	rval = pqisrc_send_tmf(softs, rcb->dvp, rcb, abort_tag,
		SOP_TASK_MANAGEMENT_FUNCTION_ABORT_TASK);

	if (PQI_STATUS_SUCCESS == rval) {
		rval = rcb->status;
		if (REQUEST_SUCCESS == rval) {
			ccb->ccb_h.status = CAM_REQ_ABORTED;
		}
	}
	pqisrc_put_tag(&softs->taglist, abort_tag);
	pqisrc_put_tag(&softs->taglist,rcb->tag);

	DBG_FUNC("OUT rval = %d\n", rval);

	return rval;
}
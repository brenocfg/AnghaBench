#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  union ccb {int dummy; } ccb ;
typedef  size_t uint32_t ;
struct TYPE_6__ {size_t tag; int status; int /*<<< orphan*/  dvp; } ;
typedef  TYPE_1__ rcb_t ;
struct TYPE_7__ {int /*<<< orphan*/  taglist; TYPE_1__* rcb; } ;
typedef  TYPE_2__ pqisrc_softstate_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_FUNC (char*,...) ; 
 int PQI_STATUS_SUCCESS ; 
 int /*<<< orphan*/  SOP_TASK_MANAGEMENT_FUNCTION_ABORT_TASK_SET ; 
 size_t pqisrc_get_tag (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pqisrc_put_tag (int /*<<< orphan*/ *,size_t) ; 
 int pqisrc_send_tmf (TYPE_2__*,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pqisrc_scsi_abort_task_set(pqisrc_softstate_t *softs, union ccb *ccb)
{
	rcb_t *rcb = NULL;
	uint32_t tag = 0;
	int rval = PQI_STATUS_SUCCESS;

	DBG_FUNC("IN\n");

	tag = pqisrc_get_tag(&softs->taglist);
	rcb = &softs->rcb[tag];
	rcb->tag = tag;

	rval = pqisrc_send_tmf(softs, rcb->dvp, rcb, 0,
			SOP_TASK_MANAGEMENT_FUNCTION_ABORT_TASK_SET);

	if (rval == PQI_STATUS_SUCCESS) {
		rval = rcb->status;
	}

	pqisrc_put_tag(&softs->taglist,rcb->tag);

	DBG_FUNC("OUT rval = %d\n", rval);

	return rval;
}
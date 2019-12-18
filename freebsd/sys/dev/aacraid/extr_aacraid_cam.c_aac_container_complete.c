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
struct TYPE_4__ {int /*<<< orphan*/  status; } ;
union ccb {TYPE_2__ ccb_h; } ;
typedef  scalar_t__ u_int32_t ;
struct aac_command {int cm_flags; TYPE_1__* cm_fib; union ccb* cm_ccb; int /*<<< orphan*/  cm_sc; } ;
struct TYPE_3__ {scalar_t__ data; } ;

/* Variables and functions */
 int AAC_CMD_RESET ; 
 int /*<<< orphan*/  CAM_BUSY ; 
 int /*<<< orphan*/  CAM_REQ_CMP ; 
 int /*<<< orphan*/  CAM_REQ_CMP_ERR ; 
 int /*<<< orphan*/  CAM_SCSI_BUS_RESET ; 
 char* HBA_FLAGS_DBG_FUNCTION_ENTRY_B ; 
 scalar_t__ ST_NOT_READY ; 
 scalar_t__ ST_OK ; 
 int /*<<< orphan*/  aacraid_release_command (struct aac_command*) ; 
 int /*<<< orphan*/  fwprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  xpt_done (union ccb*) ; 

__attribute__((used)) static void
aac_container_complete(struct aac_command *cm)
{
	union	ccb *ccb;
	u_int32_t status;

	fwprintf(cm->cm_sc, HBA_FLAGS_DBG_FUNCTION_ENTRY_B, "");
	ccb = cm->cm_ccb;
	status = ((u_int32_t *)cm->cm_fib->data)[0];

	if (cm->cm_flags & AAC_CMD_RESET) {
		ccb->ccb_h.status = CAM_SCSI_BUS_RESET;
	} else if (status == ST_OK) {
		ccb->ccb_h.status = CAM_REQ_CMP;
	} else if (status == ST_NOT_READY) {
		ccb->ccb_h.status = CAM_BUSY;
	} else {
		ccb->ccb_h.status = CAM_REQ_CMP_ERR;
	}

	aacraid_release_command(cm);
	xpt_done(ccb);
}
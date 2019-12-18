#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  status; } ;
struct TYPE_5__ {int /*<<< orphan*/  sense_data; scalar_t__ sense_len; int /*<<< orphan*/  scsi_status; } ;
union ccb {TYPE_3__ ccb_h; TYPE_2__ csio; } ;
typedef  int u_int8_t ;
struct SENSE_DATA {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  SenseData; } ;
struct CommandControlBlock {TYPE_1__ arcmsr_cdb; union ccb* pccb; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_AUTOSNS_VALID ; 
 int /*<<< orphan*/  CAM_SCSI_STATUS_ERROR ; 
 int /*<<< orphan*/  SCSI_STATUS_CHECK_COND ; 
 int /*<<< orphan*/  get_min (int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void arcmsr_report_sense_info(struct CommandControlBlock *srb)
{
	union ccb *pccb = srb->pccb;

	pccb->ccb_h.status |= CAM_SCSI_STATUS_ERROR;
	pccb->csio.scsi_status = SCSI_STATUS_CHECK_COND;
	if(pccb->csio.sense_len) {
		memset(&pccb->csio.sense_data, 0, sizeof(pccb->csio.sense_data));
		memcpy(&pccb->csio.sense_data, srb->arcmsr_cdb.SenseData, 
		get_min(sizeof(struct SENSE_DATA), sizeof(pccb->csio.sense_data)));
		((u_int8_t *)&pccb->csio.sense_data)[0] = (0x1 << 7 | 0x70); /* Valid,ErrorCode */
		pccb->ccb_h.status |= CAM_AUTOSNS_VALID;
	}
}
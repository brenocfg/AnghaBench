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
struct TYPE_4__ {int func_code; int /*<<< orphan*/  status; int /*<<< orphan*/  path; } ;
struct TYPE_3__ {int /*<<< orphan*/  status; } ;
struct ccb_pathinq {int version_num; TYPE_1__ ccb_h; int /*<<< orphan*/  transport_version; int /*<<< orphan*/  transport; int /*<<< orphan*/  protocol_version; int /*<<< orphan*/  protocol; int /*<<< orphan*/  base_transfer_speed; int /*<<< orphan*/  bus_id; int /*<<< orphan*/  unit_number; int /*<<< orphan*/  dev_name; int /*<<< orphan*/  hba_vid; int /*<<< orphan*/  sim_vid; int /*<<< orphan*/  initiator_id; int /*<<< orphan*/  max_lun; int /*<<< orphan*/  max_target; int /*<<< orphan*/  hba_eng_cnt; int /*<<< orphan*/  hba_misc; int /*<<< orphan*/  target_sprt; int /*<<< orphan*/  hba_inquiry; } ;
union ccb {TYPE_2__ ccb_h; struct ccb_pathinq cpi; } ;
struct cam_sim {char* sim_name; int /*<<< orphan*/  bus_id; int /*<<< orphan*/  unit_number; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DEBUG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CAM_DEBUG_TRACE ; 
 int /*<<< orphan*/  CAM_REQ_CMP ; 
 int /*<<< orphan*/  CAM_REQ_INVALID ; 
 int /*<<< orphan*/  DEV_IDLEN ; 
 int /*<<< orphan*/  HBA_IDLEN ; 
 int /*<<< orphan*/  PROTO_UNSPECIFIED ; 
 int /*<<< orphan*/  PROTO_VERSION_UNSPECIFIED ; 
 int /*<<< orphan*/  SIM_IDLEN ; 
 int /*<<< orphan*/  XPORT_UNSPECIFIED ; 
 int /*<<< orphan*/  XPORT_VERSION_UNSPECIFIED ; 
#define  XPT_PATH_INQ 128 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_done (union ccb*) ; 

__attribute__((used)) static void
xptaction(struct cam_sim *sim, union ccb *work_ccb)
{
	CAM_DEBUG(work_ccb->ccb_h.path, CAM_DEBUG_TRACE, ("xptaction\n"));

	switch (work_ccb->ccb_h.func_code) {
	/* Common cases first */
	case XPT_PATH_INQ:		/* Path routing inquiry */
	{
		struct ccb_pathinq *cpi;

		cpi = &work_ccb->cpi;
		cpi->version_num = 1; /* XXX??? */
		cpi->hba_inquiry = 0;
		cpi->target_sprt = 0;
		cpi->hba_misc = 0;
		cpi->hba_eng_cnt = 0;
		cpi->max_target = 0;
		cpi->max_lun = 0;
		cpi->initiator_id = 0;
		strlcpy(cpi->sim_vid, "FreeBSD", SIM_IDLEN);
		strlcpy(cpi->hba_vid, "", HBA_IDLEN);
		strlcpy(cpi->dev_name, sim->sim_name, DEV_IDLEN);
		cpi->unit_number = sim->unit_number;
		cpi->bus_id = sim->bus_id;
		cpi->base_transfer_speed = 0;
		cpi->protocol = PROTO_UNSPECIFIED;
		cpi->protocol_version = PROTO_VERSION_UNSPECIFIED;
		cpi->transport = XPORT_UNSPECIFIED;
		cpi->transport_version = XPORT_VERSION_UNSPECIFIED;
		cpi->ccb_h.status = CAM_REQ_CMP;
		xpt_done(work_ccb);
		break;
	}
	default:
		work_ccb->ccb_h.status = CAM_REQ_INVALID;
		xpt_done(work_ccb);
		break;
	}
}
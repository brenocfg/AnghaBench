#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int func_code; void* status; int /*<<< orphan*/  target_id; } ;
struct TYPE_8__ {void* status; } ;
struct ccb_pathinq {int version_num; int base_transfer_speed; int transport_version; TYPE_2__ ccb_h; int /*<<< orphan*/  protocol_version; int /*<<< orphan*/  protocol; int /*<<< orphan*/  transport; int /*<<< orphan*/  dev_name; int /*<<< orphan*/  hba_vid; int /*<<< orphan*/  sim_vid; void* initiator_id; int /*<<< orphan*/  bus_id; int /*<<< orphan*/  unit_number; int /*<<< orphan*/  max_lun; void* max_target; int /*<<< orphan*/  hba_eng_cnt; int /*<<< orphan*/  hba_misc; int /*<<< orphan*/  target_sprt; int /*<<< orphan*/  hba_inquiry; } ;
struct TYPE_7__ {int heads; int secs_per_track; int cylinders; int volume_size; } ;
union ccb {TYPE_3__ ccb_h; struct ccb_pathinq cpi; TYPE_1__ ccg; } ;
struct cam_sim {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  vbus; } ;
typedef  TYPE_4__* PVBUS_EXT ;
typedef  int /*<<< orphan*/  PVBUS ;

/* Variables and functions */
 void* CAM_FUNC_NOTAVAIL ; 
 void* CAM_REQ_CMP ; 
 void* CAM_REQ_INVALID ; 
 int /*<<< orphan*/  DEV_IDLEN ; 
 int /*<<< orphan*/  HBA_IDLEN ; 
 int /*<<< orphan*/  KdPrint (char*) ; 
 int /*<<< orphan*/  PIM_NOBUSRESET ; 
 int /*<<< orphan*/  PI_SDTR_ABLE ; 
 int /*<<< orphan*/  PROTO_SCSI ; 
 int /*<<< orphan*/  SCSI_REV_2 ; 
 int /*<<< orphan*/  SIM_IDLEN ; 
 int /*<<< orphan*/  XPORT_SPI ; 
#define  XPT_CALC_GEOMETRY 133 
#define  XPT_GET_TRAN_SETTINGS 132 
#define  XPT_PATH_INQ 131 
#define  XPT_RESET_BUS 130 
#define  XPT_SCSI_IO 129 
#define  XPT_SET_TRAN_SETTINGS 128 
 int /*<<< orphan*/  cam_sim_bus (struct cam_sim*) ; 
 char* cam_sim_name (struct cam_sim*) ; 
 int /*<<< orphan*/  cam_sim_softc (struct cam_sim*) ; 
 int /*<<< orphan*/  cam_sim_unit (struct cam_sim*) ; 
 int /*<<< orphan*/  hpt_assert_vbus_locked (TYPE_4__*) ; 
 int /*<<< orphan*/  hpt_scsi_io (TYPE_4__*,union ccb*) ; 
 int /*<<< orphan*/  ldm_reset_vbus (int /*<<< orphan*/ ) ; 
 void* osm_max_targets ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_done (union ccb*) ; 

__attribute__((used)) static void hpt_action(struct cam_sim *sim, union ccb *ccb)
{
	PVBUS_EXT vbus_ext = (PVBUS_EXT)cam_sim_softc(sim);

	KdPrint(("hpt_action(fn=%d, id=%d)", ccb->ccb_h.func_code, ccb->ccb_h.target_id));

	hpt_assert_vbus_locked(vbus_ext);
	switch (ccb->ccb_h.func_code) {
	
	case XPT_SCSI_IO:
		hpt_scsi_io(vbus_ext, ccb);
		return;

	case XPT_RESET_BUS:
		ldm_reset_vbus((PVBUS)vbus_ext->vbus);
		break;

	case XPT_GET_TRAN_SETTINGS:
	case XPT_SET_TRAN_SETTINGS:
		ccb->ccb_h.status = CAM_FUNC_NOTAVAIL;
		break;

	case XPT_CALC_GEOMETRY:
		ccb->ccg.heads = 255;
		ccb->ccg.secs_per_track = 63;
		ccb->ccg.cylinders = ccb->ccg.volume_size / (ccb->ccg.heads * ccb->ccg.secs_per_track);
		ccb->ccb_h.status = CAM_REQ_CMP;
		break;

	case XPT_PATH_INQ:
	{
		struct ccb_pathinq *cpi = &ccb->cpi;

		cpi->version_num = 1;
		cpi->hba_inquiry = PI_SDTR_ABLE;
		cpi->target_sprt = 0;
		cpi->hba_misc = PIM_NOBUSRESET;
		cpi->hba_eng_cnt = 0;
		cpi->max_target = osm_max_targets;
		cpi->max_lun = 0;
		cpi->unit_number = cam_sim_unit(sim);
		cpi->bus_id = cam_sim_bus(sim);
		cpi->initiator_id = osm_max_targets;
		cpi->base_transfer_speed = 3300;

		strlcpy(cpi->sim_vid, "FreeBSD", SIM_IDLEN);
		strlcpy(cpi->hba_vid, "HPT   ", HBA_IDLEN);
		strlcpy(cpi->dev_name, cam_sim_name(sim), DEV_IDLEN);
		cpi->transport = XPORT_SPI;
		cpi->transport_version = 2;
		cpi->protocol = PROTO_SCSI;
		cpi->protocol_version = SCSI_REV_2;
		cpi->ccb_h.status = CAM_REQ_CMP;
		break;
	}

	default:
		ccb->ccb_h.status = CAM_REQ_INVALID;
		break;
	}

	xpt_done(ccb);
	return;
}
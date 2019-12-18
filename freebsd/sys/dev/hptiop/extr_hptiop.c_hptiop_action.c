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
struct TYPE_4__ {int func_code; int flags; void* status; int /*<<< orphan*/  target_id; int /*<<< orphan*/  target_lun; } ;
struct TYPE_3__ {int /*<<< orphan*/  status; } ;
struct ccb_pathinq {int version_num; int base_transfer_speed; int transport_version; TYPE_1__ ccb_h; int /*<<< orphan*/  protocol_version; int /*<<< orphan*/  protocol; int /*<<< orphan*/  transport; int /*<<< orphan*/  dev_name; int /*<<< orphan*/  hba_vid; int /*<<< orphan*/  sim_vid; int /*<<< orphan*/  initiator_id; int /*<<< orphan*/  bus_id; int /*<<< orphan*/  unit_number; int /*<<< orphan*/  max_lun; int /*<<< orphan*/  max_target; int /*<<< orphan*/  hba_eng_cnt; int /*<<< orphan*/  hba_misc; int /*<<< orphan*/  target_sprt; int /*<<< orphan*/  hba_inquiry; } ;
union ccb {TYPE_2__ ccb_h; struct ccb_pathinq cpi; int /*<<< orphan*/  ccg; } ;
struct hpt_iop_srb {int /*<<< orphan*/  dma_map; union ccb* ccb; } ;
struct hpt_iop_hba {int /*<<< orphan*/  max_devices; int /*<<< orphan*/  msg_done; int /*<<< orphan*/  pcidev; int /*<<< orphan*/  sim; int /*<<< orphan*/  pciunit; int /*<<< orphan*/  io_dmat; } ;
struct cam_sim {int dummy; } ;

/* Variables and functions */
 int CAM_CDB_PHYS ; 
 void* CAM_FUNC_NOTAVAIL ; 
 int /*<<< orphan*/  CAM_REQ_CMP ; 
 void* CAM_REQ_CMP_ERR ; 
 void* CAM_REQ_INVALID ; 
 void* CAM_TID_INVALID ; 
 int /*<<< orphan*/  DEV_IDLEN ; 
 int EINPROGRESS ; 
 int /*<<< orphan*/  HBA_IDLEN ; 
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
 int bus_dmamap_load_ccb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union ccb*,int /*<<< orphan*/ ,struct hpt_iop_srb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_calc_geometry (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cam_sim_bus (struct cam_sim*) ; 
 char* cam_sim_name (struct cam_sim*) ; 
 scalar_t__ cam_sim_softc (struct cam_sim*) ; 
 int /*<<< orphan*/  cam_sim_unit (struct cam_sim*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  hptiop_free_srb (struct hpt_iop_hba*,struct hpt_iop_srb*) ; 
 struct hpt_iop_srb* hptiop_get_srb (struct hpt_iop_hba*) ; 
 int /*<<< orphan*/  hptiop_post_scsi_command ; 
 int /*<<< orphan*/  hptiop_reset_adapter (struct hpt_iop_hba*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_done (union ccb*) ; 
 int /*<<< orphan*/  xpt_freeze_simq (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hptiop_action(struct cam_sim *sim, union ccb *ccb)
{
	struct hpt_iop_hba * hba = (struct hpt_iop_hba *)cam_sim_softc(sim);
	struct hpt_iop_srb * srb;
	int error;

	switch (ccb->ccb_h.func_code) {

	case XPT_SCSI_IO:
		if (ccb->ccb_h.target_lun != 0 ||
			ccb->ccb_h.target_id >= hba->max_devices ||
			(ccb->ccb_h.flags & CAM_CDB_PHYS))
		{
			ccb->ccb_h.status = CAM_TID_INVALID;
			xpt_done(ccb);
			return;
		}

		if ((srb = hptiop_get_srb(hba)) == NULL) {
			device_printf(hba->pcidev, "srb allocated failed");
			ccb->ccb_h.status = CAM_REQ_CMP_ERR;
			xpt_done(ccb);
			return;
		}

		srb->ccb = ccb;
		error = bus_dmamap_load_ccb(hba->io_dmat,
					    srb->dma_map,
					    ccb,
					    hptiop_post_scsi_command,
					    srb,
					    0);

		if (error && error != EINPROGRESS) {
			device_printf(hba->pcidev,
				"%d bus_dmamap_load error %d",
				hba->pciunit, error);
			xpt_freeze_simq(hba->sim, 1);
			ccb->ccb_h.status = CAM_REQ_CMP_ERR;
			hptiop_free_srb(hba, srb);
			xpt_done(ccb);
			return;
		}

		return;

	case XPT_RESET_BUS:
		device_printf(hba->pcidev, "reset adapter");
		hba->msg_done = 0;
		hptiop_reset_adapter(hba);
		break;

	case XPT_GET_TRAN_SETTINGS:
	case XPT_SET_TRAN_SETTINGS:
		ccb->ccb_h.status = CAM_FUNC_NOTAVAIL;
		break;

	case XPT_CALC_GEOMETRY:
		cam_calc_geometry(&ccb->ccg, 1);
		break;

	case XPT_PATH_INQ:
	{
		struct ccb_pathinq *cpi = &ccb->cpi;

		cpi->version_num = 1;
		cpi->hba_inquiry = PI_SDTR_ABLE;
		cpi->target_sprt = 0;
		cpi->hba_misc = PIM_NOBUSRESET;
		cpi->hba_eng_cnt = 0;
		cpi->max_target = hba->max_devices;
		cpi->max_lun = 0;
		cpi->unit_number = cam_sim_unit(sim);
		cpi->bus_id = cam_sim_bus(sim);
		cpi->initiator_id = hba->max_devices;
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
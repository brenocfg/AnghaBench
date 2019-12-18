#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ccb_hdr {int func_code; void* status; struct mfip_softc* ccb_mfip_ptr; } ;
struct ccb_scsiio {int /*<<< orphan*/  cdb_len; } ;
struct ccb_trans_settings_sas {int bitrate; int /*<<< orphan*/  valid; } ;
struct TYPE_8__ {struct ccb_trans_settings_sas sas; } ;
struct ccb_trans_settings_scsi {int /*<<< orphan*/  flags; int /*<<< orphan*/  valid; } ;
struct TYPE_7__ {struct ccb_trans_settings_scsi scsi; } ;
struct TYPE_9__ {int /*<<< orphan*/  transport_version; void* transport; void* protocol_version; void* protocol; TYPE_3__ xport_specific; TYPE_2__ proto_specific; } ;
struct TYPE_6__ {void* status; } ;
struct ccb_pathinq {int version_num; int hba_misc; int base_transfer_speed; TYPE_1__ ccb_h; void* protocol_version; void* protocol; int /*<<< orphan*/  transport_version; void* transport; int /*<<< orphan*/  bus_id; int /*<<< orphan*/  unit_number; int /*<<< orphan*/  dev_name; int /*<<< orphan*/  hba_vid; int /*<<< orphan*/  sim_vid; int /*<<< orphan*/  initiator_id; int /*<<< orphan*/  max_lun; int /*<<< orphan*/  max_target; int /*<<< orphan*/  hba_eng_cnt; int /*<<< orphan*/  target_sprt; int /*<<< orphan*/  hba_inquiry; } ;
union ccb {struct ccb_hdr ccb_h; struct ccb_scsiio csio; TYPE_4__ cts; struct ccb_pathinq cpi; } ;
struct mfip_softc {struct mfi_softc* mfi_sc; } ;
struct mfi_softc {int /*<<< orphan*/  mfi_cam_ccbq; int /*<<< orphan*/  mfi_io_lock; } ;
struct cam_sim {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  tqe; } ;

/* Variables and functions */
 void* CAM_FUNC_NOTAVAIL ; 
 void* CAM_REQ_CMP ; 
 void* CAM_REQ_INPROG ; 
 void* CAM_REQ_INVALID ; 
 int /*<<< orphan*/  CTS_SAS_VALID_SPEED ; 
 int /*<<< orphan*/  CTS_SCSI_FLAGS_TAG_ENB ; 
 int /*<<< orphan*/  CTS_SCSI_VALID_TQ ; 
 int /*<<< orphan*/  DEV_IDLEN ; 
 int /*<<< orphan*/  HBA_IDLEN ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  MFI_SCSI_INITIATOR_ID ; 
 int /*<<< orphan*/  MFI_SCSI_MAX_CDB_LEN ; 
 int /*<<< orphan*/  MFI_SCSI_MAX_LUNS ; 
 int /*<<< orphan*/  MFI_SCSI_MAX_TARGETS ; 
 int PIM_NOBUSRESET ; 
 int PIM_SEQSCAN ; 
 int PIM_UNMAPPED ; 
 int /*<<< orphan*/  PI_TAG_ABLE ; 
 void* PROTO_SCSI ; 
 void* SCSI_REV_2 ; 
 int /*<<< orphan*/  SIM_IDLEN ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct ccb_hdr*,int /*<<< orphan*/ ) ; 
 void* XPORT_SAS ; 
#define  XPT_GET_TRAN_SETTINGS 133 
#define  XPT_PATH_INQ 132 
#define  XPT_RESET_BUS 131 
#define  XPT_RESET_DEV 130 
#define  XPT_SCSI_IO 129 
#define  XPT_SET_TRAN_SETTINGS 128 
 int /*<<< orphan*/  cam_sim_bus (struct cam_sim*) ; 
 char* cam_sim_name (struct cam_sim*) ; 
 struct mfip_softc* cam_sim_softc (struct cam_sim*) ; 
 int /*<<< orphan*/  cam_sim_unit (struct cam_sim*) ; 
 int /*<<< orphan*/  mfi_startio (struct mfi_softc*) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_5__ sim_links ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_done (union ccb*) ; 

__attribute__((used)) static void
mfip_cam_action(struct cam_sim *sim, union ccb *ccb)
{
	struct mfip_softc *sc = cam_sim_softc(sim);
	struct mfi_softc *mfisc = sc->mfi_sc;

	mtx_assert(&mfisc->mfi_io_lock, MA_OWNED);

	switch (ccb->ccb_h.func_code) {
	case XPT_PATH_INQ:
	{
		struct ccb_pathinq *cpi = &ccb->cpi;

		cpi->version_num = 1;
		cpi->hba_inquiry = PI_TAG_ABLE;
		cpi->target_sprt = 0;
		cpi->hba_misc = PIM_NOBUSRESET | PIM_SEQSCAN | PIM_UNMAPPED;
		cpi->hba_eng_cnt = 0;
		cpi->max_target = MFI_SCSI_MAX_TARGETS;
		cpi->max_lun = MFI_SCSI_MAX_LUNS;
		cpi->initiator_id = MFI_SCSI_INITIATOR_ID;
		strlcpy(cpi->sim_vid, "FreeBSD", SIM_IDLEN);
		strlcpy(cpi->hba_vid, "LSI", HBA_IDLEN);
		strlcpy(cpi->dev_name, cam_sim_name(sim), DEV_IDLEN);
		cpi->unit_number = cam_sim_unit(sim);
		cpi->bus_id = cam_sim_bus(sim);
		cpi->base_transfer_speed = 150000;
		cpi->transport = XPORT_SAS;
		cpi->transport_version = 0;
		cpi->protocol = PROTO_SCSI;
		cpi->protocol_version = SCSI_REV_2;
		cpi->ccb_h.status = CAM_REQ_CMP;
		break;
	}
	case XPT_RESET_BUS:
		ccb->ccb_h.status = CAM_REQ_CMP;
		break;
	case XPT_RESET_DEV:
		ccb->ccb_h.status = CAM_REQ_CMP;
		break;
	case XPT_GET_TRAN_SETTINGS:
	{
		struct ccb_trans_settings_scsi *scsi =
		    &ccb->cts.proto_specific.scsi;
		struct ccb_trans_settings_sas *sas =
		    &ccb->cts.xport_specific.sas;

		ccb->cts.protocol = PROTO_SCSI;
		ccb->cts.protocol_version = SCSI_REV_2;
		ccb->cts.transport = XPORT_SAS;
		ccb->cts.transport_version = 0;

		scsi->valid = CTS_SCSI_VALID_TQ;
		scsi->flags = CTS_SCSI_FLAGS_TAG_ENB;

		sas->valid &= ~CTS_SAS_VALID_SPEED;
		sas->bitrate = 150000;

		ccb->ccb_h.status = CAM_REQ_CMP;
		break;
	}
	case XPT_SET_TRAN_SETTINGS:
		ccb->ccb_h.status = CAM_FUNC_NOTAVAIL;
		break;
	case XPT_SCSI_IO:
	{
		struct ccb_hdr		*ccbh = &ccb->ccb_h;
		struct ccb_scsiio	*csio = &ccb->csio;

		ccbh->status = CAM_REQ_INPROG;
		if (csio->cdb_len > MFI_SCSI_MAX_CDB_LEN) {
			ccbh->status = CAM_REQ_INVALID;
			break;
		}
		ccbh->ccb_mfip_ptr = sc;
		TAILQ_INSERT_TAIL(&mfisc->mfi_cam_ccbq, ccbh, sim_links.tqe);
		mfi_startio(mfisc);
		return;
	}
	default:
		ccb->ccb_h.status = CAM_REQ_INVALID;
		break;
	}

	xpt_done(ccb);
	return;
}
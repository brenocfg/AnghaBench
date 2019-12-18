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
struct TYPE_10__ {int func_code; int target_id; void* status; int /*<<< orphan*/  recovery_type; int /*<<< orphan*/  path; } ;
struct TYPE_9__ {void* status; } ;
struct ccb_pathinq {int version_num; int hba_misc; int max_target; int base_transfer_speed; int maxio; TYPE_4__ ccb_h; int /*<<< orphan*/  hba_subdevice; int /*<<< orphan*/  hba_subvendor; int /*<<< orphan*/  hba_device; int /*<<< orphan*/  hba_vendor; void* protocol_version; int /*<<< orphan*/  protocol; void* transport_version; void* transport; int /*<<< orphan*/  unit_number; int /*<<< orphan*/  dev_name; int /*<<< orphan*/  hba_vid; int /*<<< orphan*/  sim_vid; int /*<<< orphan*/  bus_id; int /*<<< orphan*/  initiator_id; int /*<<< orphan*/  max_lun; int /*<<< orphan*/  hba_eng_cnt; int /*<<< orphan*/  target_sprt; int /*<<< orphan*/  hba_inquiry; } ;
struct TYPE_7__ {int valid; int revision; int bytecount; int tags; int caps; int /*<<< orphan*/  atapi; int /*<<< orphan*/  pm_present; int /*<<< orphan*/  mode; } ;
struct TYPE_8__ {TYPE_2__ sata; } ;
struct TYPE_6__ {int /*<<< orphan*/  valid; } ;
struct ccb_trans_settings {TYPE_3__ xport_specific; int /*<<< orphan*/  type; TYPE_1__ proto_specific; void* transport_version; void* transport; void* protocol_version; int /*<<< orphan*/  protocol; } ;
union ccb {TYPE_5__ ccb_h; struct ccb_pathinq cpi; struct ccb_trans_settings cts; } ;
typedef  int uint32_t ;
struct cam_sim {int dummy; } ;
struct ahci_device {int revision; int bytecount; int tags; int caps; int /*<<< orphan*/  atapi; int /*<<< orphan*/  mode; } ;
struct ahci_channel {int numslots; int caps; int caps2; int quirks; int /*<<< orphan*/  subdeviceid; int /*<<< orphan*/  subvendorid; int /*<<< orphan*/  deviceid; int /*<<< orphan*/  vendorid; int /*<<< orphan*/  pm_present; struct ahci_device* user; int /*<<< orphan*/  pm_level; int /*<<< orphan*/  r_mem; struct ahci_device* curr; int /*<<< orphan*/  sim; union ccb* frozen; int /*<<< orphan*/  devices; } ;

/* Variables and functions */
 int AHCI_CAP2_APST ; 
 int AHCI_CAP_PSC ; 
 int AHCI_CAP_SNCQ ; 
 int AHCI_CAP_SPM ; 
 int AHCI_CAP_SSC ; 
 int /*<<< orphan*/  AHCI_P_SSTS ; 
 int AHCI_Q_MAXIO_64K ; 
 int AHCI_Q_NOAA ; 
 int AHCI_Q_NOAUX ; 
 int ATA_INL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ATA_SS_SPD_MASK ; 
 int /*<<< orphan*/  CAM_DEBUG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CAM_DEBUG_TRACE ; 
 void* CAM_REQ_CMP ; 
 void* CAM_REQ_INVALID ; 
 void* CAM_SEL_TIMEOUT ; 
 int CTS_SATA_CAPS_D ; 
 int CTS_SATA_CAPS_H_AN ; 
 int CTS_SATA_CAPS_H_APST ; 
 int CTS_SATA_CAPS_H_DMAAA ; 
 int CTS_SATA_CAPS_H_PMREQ ; 
 int CTS_SATA_VALID_ATAPI ; 
 int CTS_SATA_VALID_BYTECOUNT ; 
 int CTS_SATA_VALID_CAPS ; 
 int CTS_SATA_VALID_MODE ; 
 int CTS_SATA_VALID_PM ; 
 int CTS_SATA_VALID_REVISION ; 
 int CTS_SATA_VALID_TAGS ; 
 int /*<<< orphan*/  CTS_TYPE_CURRENT_SETTINGS ; 
 int /*<<< orphan*/  DEV_IDLEN ; 
 int /*<<< orphan*/  HBA_IDLEN ; 
 int MAXPHYS ; 
 int PIM_ATA_EXT ; 
 int PIM_SEQSCAN ; 
 int PIM_UNMAPPED ; 
 int /*<<< orphan*/  PI_SATAPM ; 
 int /*<<< orphan*/  PI_SDTR_ABLE ; 
 int /*<<< orphan*/  PI_TAG_ABLE ; 
 int /*<<< orphan*/  PROTO_ATA ; 
 int /*<<< orphan*/  PROTO_UNSPECIFIED ; 
 void* PROTO_VERSION_UNSPECIFIED ; 
 int /*<<< orphan*/  RECOVERY_NONE ; 
 int /*<<< orphan*/  SIM_IDLEN ; 
 void* XPORT_SATA ; 
 void* XPORT_VERSION_UNSPECIFIED ; 
#define  XPT_ABORT 136 
#define  XPT_ATA_IO 135 
#define  XPT_GET_TRAN_SETTINGS 134 
#define  XPT_PATH_INQ 133 
#define  XPT_RESET_BUS 132 
#define  XPT_RESET_DEV 131 
#define  XPT_SCSI_IO 130 
#define  XPT_SET_TRAN_SETTINGS 129 
#define  XPT_TERM_IO 128 
 int /*<<< orphan*/  ahci_begin_transaction (struct ahci_channel*,union ccb*) ; 
 int /*<<< orphan*/  ahci_check_collision (struct ahci_channel*,union ccb*) ; 
 int /*<<< orphan*/  ahci_check_ids (struct ahci_channel*,union ccb*) ; 
 int /*<<< orphan*/  ahci_done (struct ahci_channel*,union ccb*) ; 
 int /*<<< orphan*/  ahci_reset (struct ahci_channel*) ; 
 int /*<<< orphan*/  cam_sim_bus (struct cam_sim*) ; 
 char* cam_sim_name (struct cam_sim*) ; 
 scalar_t__ cam_sim_softc (struct cam_sim*) ; 
 int /*<<< orphan*/  cam_sim_unit (struct cam_sim*) ; 
 void* min (int,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_freeze_simq (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ahciaction(struct cam_sim *sim, union ccb *ccb)
{
	struct ahci_channel *ch;

	CAM_DEBUG(ccb->ccb_h.path, CAM_DEBUG_TRACE, ("ahciaction func_code=%x\n",
	    ccb->ccb_h.func_code));

	ch = (struct ahci_channel *)cam_sim_softc(sim);
	switch (ccb->ccb_h.func_code) {
	/* Common cases first */
	case XPT_ATA_IO:	/* Execute the requested I/O operation */
	case XPT_SCSI_IO:
		if (ahci_check_ids(ch, ccb))
			return;
		if (ch->devices == 0 ||
		    (ch->pm_present == 0 &&
		     ccb->ccb_h.target_id > 0 && ccb->ccb_h.target_id < 15)) {
			ccb->ccb_h.status = CAM_SEL_TIMEOUT;
			break;
		}
		ccb->ccb_h.recovery_type = RECOVERY_NONE;
		/* Check for command collision. */
		if (ahci_check_collision(ch, ccb)) {
			/* Freeze command. */
			ch->frozen = ccb;
			/* We have only one frozen slot, so freeze simq also. */
			xpt_freeze_simq(ch->sim, 1);
			return;
		}
		ahci_begin_transaction(ch, ccb);
		return;
	case XPT_ABORT:			/* Abort the specified CCB */
		/* XXX Implement */
		ccb->ccb_h.status = CAM_REQ_INVALID;
		break;
	case XPT_SET_TRAN_SETTINGS:
	{
		struct	ccb_trans_settings *cts = &ccb->cts;
		struct	ahci_device *d; 

		if (ahci_check_ids(ch, ccb))
			return;
		if (cts->type == CTS_TYPE_CURRENT_SETTINGS)
			d = &ch->curr[ccb->ccb_h.target_id];
		else
			d = &ch->user[ccb->ccb_h.target_id];
		if (cts->xport_specific.sata.valid & CTS_SATA_VALID_REVISION)
			d->revision = cts->xport_specific.sata.revision;
		if (cts->xport_specific.sata.valid & CTS_SATA_VALID_MODE)
			d->mode = cts->xport_specific.sata.mode;
		if (cts->xport_specific.sata.valid & CTS_SATA_VALID_BYTECOUNT)
			d->bytecount = min(8192, cts->xport_specific.sata.bytecount);
		if (cts->xport_specific.sata.valid & CTS_SATA_VALID_TAGS)
			d->tags = min(ch->numslots, cts->xport_specific.sata.tags);
		if (cts->xport_specific.sata.valid & CTS_SATA_VALID_PM)
			ch->pm_present = cts->xport_specific.sata.pm_present;
		if (cts->xport_specific.sata.valid & CTS_SATA_VALID_ATAPI)
			d->atapi = cts->xport_specific.sata.atapi;
		if (cts->xport_specific.sata.valid & CTS_SATA_VALID_CAPS)
			d->caps = cts->xport_specific.sata.caps;
		ccb->ccb_h.status = CAM_REQ_CMP;
		break;
	}
	case XPT_GET_TRAN_SETTINGS:
	/* Get default/user set transfer settings for the target */
	{
		struct	ccb_trans_settings *cts = &ccb->cts;
		struct  ahci_device *d;
		uint32_t status;

		if (ahci_check_ids(ch, ccb))
			return;
		if (cts->type == CTS_TYPE_CURRENT_SETTINGS)
			d = &ch->curr[ccb->ccb_h.target_id];
		else
			d = &ch->user[ccb->ccb_h.target_id];
		cts->protocol = PROTO_UNSPECIFIED;
		cts->protocol_version = PROTO_VERSION_UNSPECIFIED;
		cts->transport = XPORT_SATA;
		cts->transport_version = XPORT_VERSION_UNSPECIFIED;
		cts->proto_specific.valid = 0;
		cts->xport_specific.sata.valid = 0;
		if (cts->type == CTS_TYPE_CURRENT_SETTINGS &&
		    (ccb->ccb_h.target_id == 15 ||
		    (ccb->ccb_h.target_id == 0 && !ch->pm_present))) {
			status = ATA_INL(ch->r_mem, AHCI_P_SSTS) & ATA_SS_SPD_MASK;
			if (status & 0x0f0) {
				cts->xport_specific.sata.revision =
				    (status & 0x0f0) >> 4;
				cts->xport_specific.sata.valid |=
				    CTS_SATA_VALID_REVISION;
			}
			cts->xport_specific.sata.caps = d->caps & CTS_SATA_CAPS_D;
			if (ch->pm_level) {
				if (ch->caps & (AHCI_CAP_PSC | AHCI_CAP_SSC))
					cts->xport_specific.sata.caps |= CTS_SATA_CAPS_H_PMREQ;
				if (ch->caps2 & AHCI_CAP2_APST)
					cts->xport_specific.sata.caps |= CTS_SATA_CAPS_H_APST;
			}
			if ((ch->caps & AHCI_CAP_SNCQ) &&
			    (ch->quirks & AHCI_Q_NOAA) == 0)
				cts->xport_specific.sata.caps |= CTS_SATA_CAPS_H_DMAAA;
			cts->xport_specific.sata.caps |= CTS_SATA_CAPS_H_AN;
			cts->xport_specific.sata.caps &=
			    ch->user[ccb->ccb_h.target_id].caps;
			cts->xport_specific.sata.valid |= CTS_SATA_VALID_CAPS;
		} else {
			cts->xport_specific.sata.revision = d->revision;
			cts->xport_specific.sata.valid |= CTS_SATA_VALID_REVISION;
			cts->xport_specific.sata.caps = d->caps;
			cts->xport_specific.sata.valid |= CTS_SATA_VALID_CAPS;
		}
		cts->xport_specific.sata.mode = d->mode;
		cts->xport_specific.sata.valid |= CTS_SATA_VALID_MODE;
		cts->xport_specific.sata.bytecount = d->bytecount;
		cts->xport_specific.sata.valid |= CTS_SATA_VALID_BYTECOUNT;
		cts->xport_specific.sata.pm_present = ch->pm_present;
		cts->xport_specific.sata.valid |= CTS_SATA_VALID_PM;
		cts->xport_specific.sata.tags = d->tags;
		cts->xport_specific.sata.valid |= CTS_SATA_VALID_TAGS;
		cts->xport_specific.sata.atapi = d->atapi;
		cts->xport_specific.sata.valid |= CTS_SATA_VALID_ATAPI;
		ccb->ccb_h.status = CAM_REQ_CMP;
		break;
	}
	case XPT_RESET_BUS:		/* Reset the specified SCSI bus */
	case XPT_RESET_DEV:	/* Bus Device Reset the specified SCSI device */
		ahci_reset(ch);
		ccb->ccb_h.status = CAM_REQ_CMP;
		break;
	case XPT_TERM_IO:		/* Terminate the I/O process */
		/* XXX Implement */
		ccb->ccb_h.status = CAM_REQ_INVALID;
		break;
	case XPT_PATH_INQ:		/* Path routing inquiry */
	{
		struct ccb_pathinq *cpi = &ccb->cpi;

		cpi->version_num = 1; /* XXX??? */
		cpi->hba_inquiry = PI_SDTR_ABLE;
		if (ch->caps & AHCI_CAP_SNCQ)
			cpi->hba_inquiry |= PI_TAG_ABLE;
		if (ch->caps & AHCI_CAP_SPM)
			cpi->hba_inquiry |= PI_SATAPM;
		cpi->target_sprt = 0;
		cpi->hba_misc = PIM_SEQSCAN | PIM_UNMAPPED;
		if ((ch->quirks & AHCI_Q_NOAUX) == 0)
			cpi->hba_misc |= PIM_ATA_EXT;
		cpi->hba_eng_cnt = 0;
		if (ch->caps & AHCI_CAP_SPM)
			cpi->max_target = 15;
		else
			cpi->max_target = 0;
		cpi->max_lun = 0;
		cpi->initiator_id = 0;
		cpi->bus_id = cam_sim_bus(sim);
		cpi->base_transfer_speed = 150000;
		strlcpy(cpi->sim_vid, "FreeBSD", SIM_IDLEN);
		strlcpy(cpi->hba_vid, "AHCI", HBA_IDLEN);
		strlcpy(cpi->dev_name, cam_sim_name(sim), DEV_IDLEN);
		cpi->unit_number = cam_sim_unit(sim);
		cpi->transport = XPORT_SATA;
		cpi->transport_version = XPORT_VERSION_UNSPECIFIED;
		cpi->protocol = PROTO_ATA;
		cpi->protocol_version = PROTO_VERSION_UNSPECIFIED;
		cpi->maxio = MAXPHYS;
		/* ATI SB600 can't handle 256 sectors with FPDMA (NCQ). */
		if (ch->quirks & AHCI_Q_MAXIO_64K)
			cpi->maxio = min(cpi->maxio, 128 * 512);
		cpi->hba_vendor = ch->vendorid;
		cpi->hba_device = ch->deviceid;
		cpi->hba_subvendor = ch->subvendorid;
		cpi->hba_subdevice = ch->subdeviceid;
		cpi->ccb_h.status = CAM_REQ_CMP;
		break;
	}
	default:
		ccb->ccb_h.status = CAM_REQ_INVALID;
		break;
	}
	ahci_done(ch, ccb);
}
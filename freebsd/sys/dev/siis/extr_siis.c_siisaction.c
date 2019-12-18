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
struct ccb_pathinq {int version_num; int hba_inquiry; int hba_misc; int max_target; int base_transfer_speed; TYPE_4__ ccb_h; int /*<<< orphan*/  hba_subdevice; int /*<<< orphan*/  hba_subvendor; int /*<<< orphan*/  hba_device; int /*<<< orphan*/  hba_vendor; int /*<<< orphan*/  maxio; void* protocol_version; int /*<<< orphan*/  protocol; void* transport_version; void* transport; int /*<<< orphan*/  unit_number; int /*<<< orphan*/  dev_name; int /*<<< orphan*/  hba_vid; int /*<<< orphan*/  sim_vid; int /*<<< orphan*/  bus_id; int /*<<< orphan*/  initiator_id; int /*<<< orphan*/  max_lun; int /*<<< orphan*/  hba_eng_cnt; int /*<<< orphan*/  target_sprt; } ;
struct TYPE_7__ {int valid; int revision; int caps; int /*<<< orphan*/  atapi; void* tags; int /*<<< orphan*/  pm_present; void* bytecount; int /*<<< orphan*/  mode; } ;
struct TYPE_8__ {TYPE_2__ sata; } ;
struct TYPE_6__ {int /*<<< orphan*/  valid; } ;
struct ccb_trans_settings {TYPE_3__ xport_specific; int /*<<< orphan*/  type; TYPE_1__ proto_specific; void* transport_version; void* transport; void* protocol_version; int /*<<< orphan*/  protocol; } ;
union ccb {TYPE_5__ ccb_h; struct ccb_pathinq cpi; struct ccb_trans_settings cts; } ;
typedef  int uint32_t ;
struct siis_device {int revision; int caps; int /*<<< orphan*/  atapi; void* tags; void* bytecount; int /*<<< orphan*/  mode; } ;
struct siis_channel {int quirks; int /*<<< orphan*/  pm_present; struct siis_device* user; int /*<<< orphan*/  pm_level; int /*<<< orphan*/  r_mem; struct siis_device* curr; int /*<<< orphan*/  sim; union ccb* frozen; int /*<<< orphan*/  devices; int /*<<< orphan*/  mtx; int /*<<< orphan*/  dev; } ;
struct cam_sim {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ATA_INL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATA_OUTL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ATA_SS_SPD_MASK ; 
 int /*<<< orphan*/  CAM_DEBUG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CAM_DEBUG_TRACE ; 
 void* CAM_REQ_CMP ; 
 void* CAM_REQ_INVALID ; 
 void* CAM_SEL_TIMEOUT ; 
 int CTS_SATA_CAPS_D ; 
 int CTS_SATA_CAPS_H_AN ; 
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
 int /*<<< orphan*/  MAXPHYS ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int PIM_ATA_EXT ; 
 int PIM_SEQSCAN ; 
 int PIM_UNMAPPED ; 
 int PI_SATAPM ; 
 int PI_SDTR_ABLE ; 
 int PI_TAG_ABLE ; 
 int /*<<< orphan*/  PROTO_ATA ; 
 int /*<<< orphan*/  PROTO_UNSPECIFIED ; 
 void* PROTO_VERSION_UNSPECIFIED ; 
 int /*<<< orphan*/  RECOVERY_NONE ; 
 int SIIS_MAX_SLOTS ; 
 int /*<<< orphan*/  SIIS_P_CTLCLR ; 
 int /*<<< orphan*/  SIIS_P_CTLSET ; 
 int /*<<< orphan*/  SIIS_P_CTL_PME ; 
 int /*<<< orphan*/  SIIS_P_SSTS ; 
 int SIIS_Q_SNTF ; 
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
 int /*<<< orphan*/  cam_sim_bus (struct cam_sim*) ; 
 char* cam_sim_name (struct cam_sim*) ; 
 scalar_t__ cam_sim_softc (struct cam_sim*) ; 
 int /*<<< orphan*/  cam_sim_unit (struct cam_sim*) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 void* min (int,void*) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_subdevice (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_subvendor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_vendor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  siis_begin_transaction (int /*<<< orphan*/ ,union ccb*) ; 
 int /*<<< orphan*/  siis_check_collision (int /*<<< orphan*/ ,union ccb*) ; 
 int /*<<< orphan*/  siis_check_ids (int /*<<< orphan*/ ,union ccb*) ; 
 int /*<<< orphan*/  siis_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_done (union ccb*) ; 
 int /*<<< orphan*/  xpt_freeze_simq (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
siisaction(struct cam_sim *sim, union ccb *ccb)
{
	device_t dev, parent;
	struct siis_channel *ch;

	CAM_DEBUG(ccb->ccb_h.path, CAM_DEBUG_TRACE, ("siisaction func_code=%x\n",
	    ccb->ccb_h.func_code));

	ch = (struct siis_channel *)cam_sim_softc(sim);
	dev = ch->dev;
	mtx_assert(&ch->mtx, MA_OWNED);
	switch (ccb->ccb_h.func_code) {
	/* Common cases first */
	case XPT_ATA_IO:	/* Execute the requested I/O operation */
	case XPT_SCSI_IO:
		if (siis_check_ids(dev, ccb))
			return;
		if (ch->devices == 0 ||
		    (ch->pm_present == 0 &&
		     ccb->ccb_h.target_id > 0 && ccb->ccb_h.target_id < 15)) {
			ccb->ccb_h.status = CAM_SEL_TIMEOUT;
			break;
		}
		ccb->ccb_h.recovery_type = RECOVERY_NONE;
		/* Check for command collision. */
		if (siis_check_collision(dev, ccb)) {
			/* Freeze command. */
			ch->frozen = ccb;
			/* We have only one frozen slot, so freeze simq also. */
			xpt_freeze_simq(ch->sim, 1);
			return;
		}
		siis_begin_transaction(dev, ccb);
		return;
	case XPT_ABORT:			/* Abort the specified CCB */
		/* XXX Implement */
		ccb->ccb_h.status = CAM_REQ_INVALID;
		break;
	case XPT_SET_TRAN_SETTINGS:
	{
		struct	ccb_trans_settings *cts = &ccb->cts;
		struct	siis_device *d; 

		if (siis_check_ids(dev, ccb))
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
			d->tags = min(SIIS_MAX_SLOTS, cts->xport_specific.sata.tags);
		if (cts->xport_specific.sata.valid & CTS_SATA_VALID_PM) {
			ch->pm_present = cts->xport_specific.sata.pm_present;
			if (ch->pm_present)
				ATA_OUTL(ch->r_mem, SIIS_P_CTLSET, SIIS_P_CTL_PME);
			else
				ATA_OUTL(ch->r_mem, SIIS_P_CTLCLR, SIIS_P_CTL_PME);
		}
		if (cts->xport_specific.sata.valid & CTS_SATA_VALID_TAGS)
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
		struct  siis_device *d;
		uint32_t status;

		if (siis_check_ids(dev, ccb))
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
			status = ATA_INL(ch->r_mem, SIIS_P_SSTS) & ATA_SS_SPD_MASK;
			if (status & 0x0f0) {
				cts->xport_specific.sata.revision =
				    (status & 0x0f0) >> 4;
				cts->xport_specific.sata.valid |=
				    CTS_SATA_VALID_REVISION;
			}
			cts->xport_specific.sata.caps = d->caps & CTS_SATA_CAPS_D;
			if (ch->pm_level)
				cts->xport_specific.sata.caps |= CTS_SATA_CAPS_H_PMREQ;
			cts->xport_specific.sata.caps |= CTS_SATA_CAPS_H_AN;
			cts->xport_specific.sata.caps &=
			    ch->user[ccb->ccb_h.target_id].caps;
			cts->xport_specific.sata.valid |= CTS_SATA_VALID_CAPS;
		} else {
			cts->xport_specific.sata.revision = d->revision;
			cts->xport_specific.sata.valid |= CTS_SATA_VALID_REVISION;
			cts->xport_specific.sata.caps = d->caps;
			if (cts->type == CTS_TYPE_CURRENT_SETTINGS &&
			    (ch->quirks & SIIS_Q_SNTF) == 0)
				cts->xport_specific.sata.caps &= ~CTS_SATA_CAPS_H_AN;
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
		siis_reset(dev);
		ccb->ccb_h.status = CAM_REQ_CMP;
		break;
	case XPT_TERM_IO:		/* Terminate the I/O process */
		/* XXX Implement */
		ccb->ccb_h.status = CAM_REQ_INVALID;
		break;
	case XPT_PATH_INQ:		/* Path routing inquiry */
	{
		struct ccb_pathinq *cpi = &ccb->cpi;

		parent = device_get_parent(dev);
		cpi->version_num = 1; /* XXX??? */
		cpi->hba_inquiry = PI_SDTR_ABLE | PI_TAG_ABLE;
		cpi->hba_inquiry |= PI_SATAPM;
		cpi->target_sprt = 0;
		cpi->hba_misc = PIM_SEQSCAN | PIM_UNMAPPED | PIM_ATA_EXT;
		cpi->hba_eng_cnt = 0;
		cpi->max_target = 15;
		cpi->max_lun = 0;
		cpi->initiator_id = 0;
		cpi->bus_id = cam_sim_bus(sim);
		cpi->base_transfer_speed = 150000;
		strlcpy(cpi->sim_vid, "FreeBSD", SIM_IDLEN);
		strlcpy(cpi->hba_vid, "SIIS", HBA_IDLEN);
		strlcpy(cpi->dev_name, cam_sim_name(sim), DEV_IDLEN);
		cpi->unit_number = cam_sim_unit(sim);
		cpi->transport = XPORT_SATA;
		cpi->transport_version = XPORT_VERSION_UNSPECIFIED;
		cpi->protocol = PROTO_ATA;
		cpi->protocol_version = PROTO_VERSION_UNSPECIFIED;
		cpi->maxio = MAXPHYS;
		cpi->hba_vendor = pci_get_vendor(parent);
		cpi->hba_device = pci_get_device(parent);
		cpi->hba_subvendor = pci_get_subvendor(parent);
		cpi->hba_subdevice = pci_get_subdevice(parent);
		cpi->ccb_h.status = CAM_REQ_CMP;
		break;
	}
	default:
		ccb->ccb_h.status = CAM_REQ_INVALID;
		break;
	}
	xpt_done(ccb);
}
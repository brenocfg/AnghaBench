#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int func_code; void* status; int /*<<< orphan*/  path; } ;
struct TYPE_15__ {void* status; } ;
struct ccb_trans_settings_nvme {int valid; int speed; int lanes; int max_speed; int max_lanes; void* spec; } ;
struct TYPE_14__ {struct ccb_trans_settings_nvme nvme; } ;
struct TYPE_13__ {struct ccb_trans_settings_nvme nvme; } ;
struct ccb_trans_settings {TYPE_7__ ccb_h; void* protocol; void* transport; TYPE_6__ proto_specific; TYPE_5__ xport_specific; } ;
struct TYPE_12__ {void* status; } ;
struct TYPE_10__ {int /*<<< orphan*/  extra; int /*<<< orphan*/  function; int /*<<< orphan*/  slot; int /*<<< orphan*/  bus; int /*<<< orphan*/  domain; int /*<<< orphan*/  nsid; } ;
struct TYPE_11__ {TYPE_2__ nvme; } ;
struct ccb_pathinq {int version_num; int hba_misc; TYPE_4__ ccb_h; TYPE_3__ xport_specific; void* protocol_version; void* protocol; void* transport_version; void* transport; int /*<<< orphan*/  unit_number; int /*<<< orphan*/  dev_name; int /*<<< orphan*/  hba_vid; int /*<<< orphan*/  sim_vid; int /*<<< orphan*/  base_transfer_speed; int /*<<< orphan*/  bus_id; int /*<<< orphan*/  initiator_id; int /*<<< orphan*/  maxio; int /*<<< orphan*/  max_lun; int /*<<< orphan*/  max_target; int /*<<< orphan*/  hba_eng_cnt; int /*<<< orphan*/  target_sprt; int /*<<< orphan*/  hba_inquiry; } ;
union ccb {TYPE_8__ ccb_h; struct ccb_trans_settings cts; struct ccb_pathinq cpi; } ;
typedef  int uint32_t ;
struct TYPE_9__ {int /*<<< orphan*/  nn; } ;
struct nvme_controller {int /*<<< orphan*/  dev; int /*<<< orphan*/  max_xfer_size; TYPE_1__ cdata; } ;
struct cam_sim {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DEBUG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CAM_DEBUG_TRACE ; 
 void* CAM_REQ_CMP ; 
 void* CAM_REQ_INVALID ; 
 int CTS_NVME_VALID_LINK ; 
 int CTS_NVME_VALID_SPEC ; 
 int /*<<< orphan*/  DEV_IDLEN ; 
 int /*<<< orphan*/  HBA_IDLEN ; 
 int PCIEM_FLAGS_TYPE ; 
 int PCIEM_LINK_CAP_MAX_SPEED ; 
 int PCIEM_LINK_CAP_MAX_WIDTH ; 
 int PCIEM_LINK_STA_SPEED ; 
 int PCIEM_LINK_STA_WIDTH ; 
 int PCIEM_TYPE_ENDPOINT ; 
 int /*<<< orphan*/  PCIER_FLAGS ; 
 int /*<<< orphan*/  PCIER_LINK_CAP ; 
 int /*<<< orphan*/  PCIER_LINK_STA ; 
 int PIM_NOSCAN ; 
 int PIM_UNMAPPED ; 
 void* PROTO_NVME ; 
 int /*<<< orphan*/  SIM_IDLEN ; 
 void* XPORT_NVME ; 
#define  XPT_ABORT 137 
#define  XPT_CALC_GEOMETRY 136 
#define  XPT_GET_TRAN_SETTINGS 135 
#define  XPT_NVME_ADMIN 134 
#define  XPT_NVME_IO 133 
#define  XPT_PATH_INQ 132 
#define  XPT_RESET_BUS 131 
#define  XPT_RESET_DEV 130 
#define  XPT_SET_TRAN_SETTINGS 129 
#define  XPT_TERM_IO 128 
 int /*<<< orphan*/  cam_sim_bus (struct cam_sim*) ; 
 char* cam_sim_name (struct cam_sim*) ; 
 int /*<<< orphan*/  cam_sim_unit (struct cam_sim*) ; 
 int /*<<< orphan*/  nvme_link_kBps (struct nvme_controller*) ; 
 void* nvme_mmio_read_4 (struct nvme_controller*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_sim_nvmeio (struct cam_sim*,union ccb*) ; 
 int /*<<< orphan*/  pci_get_bus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_domain (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_function (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_slot (int /*<<< orphan*/ ) ; 
 int pcie_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct nvme_controller* sim2ctrlr (struct cam_sim*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vs ; 
 int /*<<< orphan*/  xpt_done (union ccb*) ; 
 int /*<<< orphan*/  xpt_path_lun_id (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nvme_sim_action(struct cam_sim *sim, union ccb *ccb)
{
	struct nvme_controller *ctrlr;

	CAM_DEBUG(ccb->ccb_h.path, CAM_DEBUG_TRACE,
	    ("nvme_sim_action: func= %#x\n",
		ccb->ccb_h.func_code));

	ctrlr = sim2ctrlr(sim);

	switch (ccb->ccb_h.func_code) {
	case XPT_CALC_GEOMETRY:		/* Calculate Geometry Totally nuts ? XXX */
		/* 
		 * Only meaningful for old-school SCSI disks since only the SCSI
		 * da driver generates them. Reject all these that slip through.
		 */
		/*FALLTHROUGH*/
	case XPT_ABORT:			/* Abort the specified CCB */
		ccb->ccb_h.status = CAM_REQ_INVALID;
		break;
	case XPT_SET_TRAN_SETTINGS:
		/*
		 * NVMe doesn't really have different transfer settings, but
		 * other parts of CAM think failure here is a big deal.
		 */
		ccb->ccb_h.status = CAM_REQ_CMP;
		break;
	case XPT_PATH_INQ:		/* Path routing inquiry */
	{
		struct ccb_pathinq	*cpi = &ccb->cpi;
		device_t		dev = ctrlr->dev;

		/*
		 * NVMe may have multiple LUNs on the same path. Current generation
		 * of NVMe devives support only a single name space. Multiple name
		 * space drives are coming, but it's unclear how we should report
		 * them up the stack.
		 */
		cpi->version_num = 1;
		cpi->hba_inquiry = 0;
		cpi->target_sprt = 0;
		cpi->hba_misc =  PIM_UNMAPPED | PIM_NOSCAN;
		cpi->hba_eng_cnt = 0;
		cpi->max_target = 0;
		cpi->max_lun = ctrlr->cdata.nn;
		cpi->maxio = ctrlr->max_xfer_size;
		cpi->initiator_id = 0;
		cpi->bus_id = cam_sim_bus(sim);
		cpi->base_transfer_speed = nvme_link_kBps(ctrlr);
		strlcpy(cpi->sim_vid, "FreeBSD", SIM_IDLEN);
		strlcpy(cpi->hba_vid, "NVMe", HBA_IDLEN);
		strlcpy(cpi->dev_name, cam_sim_name(sim), DEV_IDLEN);
		cpi->unit_number = cam_sim_unit(sim);
		cpi->transport = XPORT_NVME;		/* XXX XPORT_PCIE ? */
		cpi->transport_version = nvme_mmio_read_4(ctrlr, vs);
		cpi->protocol = PROTO_NVME;
		cpi->protocol_version = nvme_mmio_read_4(ctrlr, vs);
		cpi->xport_specific.nvme.nsid = xpt_path_lun_id(ccb->ccb_h.path);
		cpi->xport_specific.nvme.domain = pci_get_domain(dev);
		cpi->xport_specific.nvme.bus = pci_get_bus(dev);
		cpi->xport_specific.nvme.slot = pci_get_slot(dev);
		cpi->xport_specific.nvme.function = pci_get_function(dev);
		cpi->xport_specific.nvme.extra = 0;
		cpi->ccb_h.status = CAM_REQ_CMP;
		break;
	}
	case XPT_GET_TRAN_SETTINGS:	/* Get transport settings */
	{
		struct ccb_trans_settings	*cts;
		struct ccb_trans_settings_nvme	*nvmep;
		struct ccb_trans_settings_nvme	*nvmex;
		device_t dev;
		uint32_t status, caps, flags;

		dev = ctrlr->dev;
		cts = &ccb->cts;
		nvmex = &cts->xport_specific.nvme;
		nvmep = &cts->proto_specific.nvme;

		status = pcie_read_config(dev, PCIER_LINK_STA, 2);
		caps = pcie_read_config(dev, PCIER_LINK_CAP, 2);
		flags = pcie_read_config(dev, PCIER_FLAGS, 2);
		nvmex->spec = nvme_mmio_read_4(ctrlr, vs);
		nvmex->valid = CTS_NVME_VALID_SPEC;
		if ((flags & PCIEM_FLAGS_TYPE) == PCIEM_TYPE_ENDPOINT) {
			nvmex->valid |= CTS_NVME_VALID_LINK;
			nvmex->speed = status & PCIEM_LINK_STA_SPEED;
			nvmex->lanes = (status & PCIEM_LINK_STA_WIDTH) >> 4;
			nvmex->max_speed = caps & PCIEM_LINK_CAP_MAX_SPEED;
			nvmex->max_lanes = (caps & PCIEM_LINK_CAP_MAX_WIDTH) >> 4;
		}

		/* XXX these should be something else maybe ? */
		nvmep->valid = 1;
		nvmep->spec = nvmex->spec;

		cts->transport = XPORT_NVME;
		cts->protocol = PROTO_NVME;
		cts->ccb_h.status = CAM_REQ_CMP;
		break;
	}
	case XPT_TERM_IO:		/* Terminate the I/O process */
		/*
		 * every driver handles this, but nothing generates it. Assume
		 * it's OK to just say 'that worked'.
		 */
		/*FALLTHROUGH*/
	case XPT_RESET_DEV:		/* Bus Device Reset the specified device */
	case XPT_RESET_BUS:		/* Reset the specified bus */
		/*
		 * NVMe doesn't really support physically resetting the bus. It's part
		 * of the bus scanning dance, so return sucess to tell the process to
		 * proceed.
		 */
		ccb->ccb_h.status = CAM_REQ_CMP;
		break;
	case XPT_NVME_IO:		/* Execute the requested I/O operation */
	case XPT_NVME_ADMIN:		/* or Admin operation */
		nvme_sim_nvmeio(sim, ccb);
		return;			/* no done */
	default:
		ccb->ccb_h.status = CAM_REQ_INVALID;
		break;
	}
	xpt_done(ccb);
}
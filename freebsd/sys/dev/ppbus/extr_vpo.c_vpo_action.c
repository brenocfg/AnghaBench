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
struct TYPE_4__ {int func_code; int flags; void* status; } ;
struct TYPE_3__ {void* status; } ;
struct ccb_pathinq {int version_num; int max_target; int base_transfer_speed; TYPE_1__ ccb_h; int /*<<< orphan*/  transport_version; int /*<<< orphan*/  transport; int /*<<< orphan*/  unit_number; int /*<<< orphan*/  dev_name; int /*<<< orphan*/  hba_vid; int /*<<< orphan*/  sim_vid; int /*<<< orphan*/  bus_id; int /*<<< orphan*/  initiator_id; int /*<<< orphan*/  max_lun; int /*<<< orphan*/  hba_eng_cnt; int /*<<< orphan*/  hba_misc; int /*<<< orphan*/  target_sprt; int /*<<< orphan*/  hba_inquiry; } ;
struct ccb_calc_geometry {int volume_size; int cylinders; int heads; int secs_per_track; int /*<<< orphan*/  block_size; } ;
struct ccb_scsiio {int dummy; } ;
union ccb {TYPE_2__ ccb_h; struct ccb_pathinq cpi; struct ccb_calc_geometry ccg; struct ccb_scsiio csio; } ;
struct vpo_data {int /*<<< orphan*/  vpo_dev; int /*<<< orphan*/  vpo_io; int /*<<< orphan*/  vpo_isplus; } ;
struct cam_sim {char* sim_name; int /*<<< orphan*/  unit_number; int /*<<< orphan*/  bus_id; scalar_t__ softc; } ;
typedef  int /*<<< orphan*/  intmax_t ;

/* Variables and functions */
 int CAM_CDB_PHYS ; 
 void* CAM_REQ_CMP ; 
 void* CAM_REQ_CMP_ERR ; 
 void* CAM_REQ_INVALID ; 
 int /*<<< orphan*/  DEV_IDLEN ; 
 int /*<<< orphan*/  HBA_IDLEN ; 
 int /*<<< orphan*/  SIM_IDLEN ; 
 int /*<<< orphan*/  VP0_INITIATOR ; 
 int /*<<< orphan*/  XPORT_PPB ; 
#define  XPT_CALC_GEOMETRY 131 
#define  XPT_PATH_INQ 130 
#define  XPT_RESET_BUS 129 
#define  XPT_SCSI_IO 128 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  imm_reset_bus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ppb_assert_locked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * scsiio_cdb_ptr (struct ccb_scsiio*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vpo_intr (struct vpo_data*,struct ccb_scsiio*) ; 
 int /*<<< orphan*/  vpoio_reset_bus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xpt_done (union ccb*) ; 

__attribute__((used)) static void
vpo_action(struct cam_sim *sim, union ccb *ccb)
{
	struct vpo_data *vpo = (struct vpo_data *)sim->softc;

	ppb_assert_locked(device_get_parent(vpo->vpo_dev));
	switch (ccb->ccb_h.func_code) {
	case XPT_SCSI_IO:
	{
		struct ccb_scsiio *csio;

		csio = &ccb->csio;

		if (ccb->ccb_h.flags & CAM_CDB_PHYS) {
			ccb->ccb_h.status = CAM_REQ_INVALID;
			xpt_done(ccb);
			break;
		}
#ifdef VP0_DEBUG
		device_printf(vpo->vpo_dev, "XPT_SCSI_IO (0x%x) request\n",
		    *scsiio_cdb_ptr(csio));
#endif
		vpo_intr(vpo, csio);

		xpt_done(ccb);

		break;
	}
	case XPT_CALC_GEOMETRY:
	{
		struct	  ccb_calc_geometry *ccg;

		ccg = &ccb->ccg;

#ifdef VP0_DEBUG
		device_printf(vpo->vpo_dev, "XPT_CALC_GEOMETRY (bs=%d,vs=%jd,c=%d,h=%d,spt=%d) request\n",
			ccg->block_size,
			(intmax_t)ccg->volume_size,
			ccg->cylinders,
			ccg->heads,
			ccg->secs_per_track);
#endif

		ccg->heads = 64;
		ccg->secs_per_track = 32;
		ccg->cylinders = ccg->volume_size /
				 (ccg->heads * ccg->secs_per_track);

		ccb->ccb_h.status = CAM_REQ_CMP;
		xpt_done(ccb);
		break;
	}
	case XPT_RESET_BUS:		/* Reset the specified SCSI bus */
	{

#ifdef VP0_DEBUG
		device_printf(vpo->vpo_dev, "XPT_RESET_BUS request\n");
#endif

		if (vpo->vpo_isplus) {
			if (imm_reset_bus(&vpo->vpo_io)) {
				ccb->ccb_h.status = CAM_REQ_CMP_ERR;
				xpt_done(ccb);
				return;
			}
		} else {
			if (vpoio_reset_bus(&vpo->vpo_io)) {
				ccb->ccb_h.status = CAM_REQ_CMP_ERR;
				xpt_done(ccb);
				return;
			}
		}

		ccb->ccb_h.status = CAM_REQ_CMP;
		xpt_done(ccb);
		break;
	}
	case XPT_PATH_INQ:		/* Path routing inquiry */
	{
		struct ccb_pathinq *cpi = &ccb->cpi;

#ifdef VP0_DEBUG
		device_printf(vpo->vpo_dev, "XPT_PATH_INQ request\n");
#endif
		cpi->version_num = 1; /* XXX??? */
		cpi->hba_inquiry = 0;
		cpi->target_sprt = 0;
		cpi->hba_misc = 0;
		cpi->hba_eng_cnt = 0;
		cpi->max_target = 7;
		cpi->max_lun = 0;
		cpi->initiator_id = VP0_INITIATOR;
		cpi->bus_id = sim->bus_id;
		cpi->base_transfer_speed = 93;
		strlcpy(cpi->sim_vid, "FreeBSD", SIM_IDLEN);
		strlcpy(cpi->hba_vid, "Iomega", HBA_IDLEN);
		strlcpy(cpi->dev_name, sim->sim_name, DEV_IDLEN);
		cpi->unit_number = sim->unit_number;
		cpi->transport = XPORT_PPB;
		cpi->transport_version = 0;

		cpi->ccb_h.status = CAM_REQ_CMP;
		xpt_done(ccb);
		break;
	}
	default:
		ccb->ccb_h.status = CAM_REQ_INVALID;
		xpt_done(ccb);
		break;
	}

	return;
}
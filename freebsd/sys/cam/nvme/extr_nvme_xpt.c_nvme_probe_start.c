#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  flags; struct cam_path* path; } ;
struct ccb_nvmeio {int dummy; } ;
union ccb {TYPE_1__ ccb_h; struct ccb_nvmeio nvmeio; } ;
typedef  int /*<<< orphan*/  uint8_t ;
struct cam_periph {int /*<<< orphan*/  path; scalar_t__ softc; } ;
struct cam_path {int dummy; } ;
struct TYPE_5__ {int action; int /*<<< orphan*/  ns; int /*<<< orphan*/  cd; scalar_t__ restart; } ;
typedef  TYPE_2__ nvme_probe_softc ;
typedef  int /*<<< orphan*/  lun_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DEBUG (struct cam_path*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CAM_DEBUG_TRACE ; 
 int /*<<< orphan*/  CAM_DEV_QFREEZE ; 
 int /*<<< orphan*/  CAM_DIR_IN ; 
 int /*<<< orphan*/  NVME_OPC_IDENTIFY ; 
#define  NVME_PROBE_IDENTIFY_CD 129 
#define  NVME_PROBE_IDENTIFY_NS 128 
 int /*<<< orphan*/  NVME_PROBE_SET_ACTION (TYPE_2__*,int) ; 
 int /*<<< orphan*/  cam_fill_nvmeadmin (struct ccb_nvmeio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  nvme_ns_cmd (struct ccb_nvmeio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_probe_done ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 int /*<<< orphan*/  xpt_action (union ccb*) ; 
 int /*<<< orphan*/  xpt_path_lun_id (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nvme_probe_start(struct cam_periph *periph, union ccb *start_ccb)
{
	struct ccb_nvmeio *nvmeio;
	nvme_probe_softc *softc;
	struct cam_path *path;
	lun_id_t lun;

	CAM_DEBUG(start_ccb->ccb_h.path, CAM_DEBUG_TRACE, ("nvme_probe_start\n"));

	softc = (nvme_probe_softc *)periph->softc;
	path = start_ccb->ccb_h.path;
	nvmeio = &start_ccb->nvmeio;
	lun = xpt_path_lun_id(periph->path);

	if (softc->restart) {
		softc->restart = 0;
		NVME_PROBE_SET_ACTION(softc, NVME_PROBE_IDENTIFY_CD);
	}

	switch (softc->action) {
	case NVME_PROBE_IDENTIFY_CD:
		cam_fill_nvmeadmin(nvmeio,
		    0,			/* retries */
		    nvme_probe_done,	/* cbfcnp */
		    CAM_DIR_IN,		/* flags */
		    (uint8_t *)&softc->cd,	/* data_ptr */
		    sizeof(softc->cd),		/* dxfer_len */
		    30 * 1000); /* timeout 30s */
		nvme_ns_cmd(nvmeio, NVME_OPC_IDENTIFY, 0,
		    1, 0, 0, 0, 0, 0);
		break;
	case NVME_PROBE_IDENTIFY_NS:
		cam_fill_nvmeadmin(nvmeio,
		    0,			/* retries */
		    nvme_probe_done,	/* cbfcnp */
		    CAM_DIR_IN,		/* flags */
		    (uint8_t *)&softc->ns,	/* data_ptr */
		    sizeof(softc->ns),		/* dxfer_len */
		    30 * 1000); /* timeout 30s */
		nvme_ns_cmd(nvmeio, NVME_OPC_IDENTIFY, lun,
		    0, 0, 0, 0, 0, 0);
		break;
	default:
		panic("nvme_probe_start: invalid action state 0x%x\n", softc->action);
	}
	start_ccb->ccb_h.flags |= CAM_DEV_QFREEZE;
	xpt_action(start_ccb);
}
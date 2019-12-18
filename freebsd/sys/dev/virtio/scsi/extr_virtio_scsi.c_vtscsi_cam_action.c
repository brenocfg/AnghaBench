#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ccb_hdr {int func_code; int /*<<< orphan*/  status; } ;
union ccb {int /*<<< orphan*/  ccg; struct ccb_hdr ccb_h; } ;
struct vtscsi_softc {int vtscsi_flags; } ;
struct cam_sim {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_FUNC_NOTAVAIL ; 
 int /*<<< orphan*/  CAM_NO_HBA ; 
 int /*<<< orphan*/  CAM_REQ_INVALID ; 
 int /*<<< orphan*/  VTSCSI_ERROR ; 
 int VTSCSI_FLAG_DETACH ; 
 int /*<<< orphan*/  VTSCSI_LOCK_OWNED (struct vtscsi_softc*) ; 
#define  XPT_ABORT 135 
#define  XPT_CALC_GEOMETRY 134 
#define  XPT_GET_TRAN_SETTINGS 133 
#define  XPT_PATH_INQ 132 
#define  XPT_RESET_BUS 131 
#define  XPT_RESET_DEV 130 
#define  XPT_SCSI_IO 129 
#define  XPT_SET_TRAN_SETTINGS 128 
 int /*<<< orphan*/  cam_calc_geometry (int /*<<< orphan*/ *,int) ; 
 struct vtscsi_softc* cam_sim_softc (struct cam_sim*) ; 
 int /*<<< orphan*/  vtscsi_cam_abort (struct vtscsi_softc*,union ccb*) ; 
 int /*<<< orphan*/  vtscsi_cam_get_tran_settings (struct vtscsi_softc*,union ccb*) ; 
 int /*<<< orphan*/  vtscsi_cam_path_inquiry (struct vtscsi_softc*,struct cam_sim*,union ccb*) ; 
 int /*<<< orphan*/  vtscsi_cam_reset_bus (struct vtscsi_softc*,union ccb*) ; 
 int /*<<< orphan*/  vtscsi_cam_reset_dev (struct vtscsi_softc*,union ccb*) ; 
 int /*<<< orphan*/  vtscsi_cam_scsi_io (struct vtscsi_softc*,struct cam_sim*,union ccb*) ; 
 int /*<<< orphan*/  vtscsi_dprintf (struct vtscsi_softc*,int /*<<< orphan*/ ,char*,union ccb*,int) ; 
 int /*<<< orphan*/  xpt_done (union ccb*) ; 

__attribute__((used)) static void
vtscsi_cam_action(struct cam_sim *sim, union ccb *ccb)
{
	struct vtscsi_softc *sc;
	struct ccb_hdr *ccbh;

	sc = cam_sim_softc(sim);
	ccbh = &ccb->ccb_h;

	VTSCSI_LOCK_OWNED(sc);

	if (sc->vtscsi_flags & VTSCSI_FLAG_DETACH) {
		/*
		 * The VTSCSI_MTX is briefly dropped between setting
		 * VTSCSI_FLAG_DETACH and deregistering with CAM, so
		 * drop any CCBs that come in during that window.
		 */
		ccbh->status = CAM_NO_HBA;
		xpt_done(ccb);
		return;
	}

	switch (ccbh->func_code) {
	case XPT_SCSI_IO:
		vtscsi_cam_scsi_io(sc, sim, ccb);
		break;

	case XPT_SET_TRAN_SETTINGS:
		ccbh->status = CAM_FUNC_NOTAVAIL;
		xpt_done(ccb);
		break;

	case XPT_GET_TRAN_SETTINGS:
		vtscsi_cam_get_tran_settings(sc, ccb);
		break;

	case XPT_RESET_BUS:
		vtscsi_cam_reset_bus(sc, ccb);
		break;

	case XPT_RESET_DEV:
		vtscsi_cam_reset_dev(sc, ccb);
		break;

	case XPT_ABORT:
		vtscsi_cam_abort(sc, ccb);
		break;

	case XPT_CALC_GEOMETRY:
		cam_calc_geometry(&ccb->ccg, 1);
		xpt_done(ccb);
		break;

	case XPT_PATH_INQ:
		vtscsi_cam_path_inquiry(sc, sim, ccb);
		break;

	default:
		vtscsi_dprintf(sc, VTSCSI_ERROR,
		    "invalid ccb=%p func=%#x\n", ccb, ccbh->func_code);

		ccbh->status = CAM_REQ_INVALID;
		xpt_done(ccb);
		break;
	}
}
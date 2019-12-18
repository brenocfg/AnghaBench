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
typedef  union ccb {int dummy; } ccb ;
typedef  int /*<<< orphan*/  u_int ;
struct ccb_trans_settings_sata {int valid; int /*<<< orphan*/  revision; } ;
struct ccb_trans_settings_pata {int valid; int /*<<< orphan*/  mode; } ;
struct TYPE_3__ {struct ccb_trans_settings_sata sata; struct ccb_trans_settings_pata ata; } ;
struct TYPE_4__ {int status; int /*<<< orphan*/  func_code; } ;
struct ccb_trans_settings {scalar_t__ transport; TYPE_1__ xport_specific; TYPE_2__ ccb_h; int /*<<< orphan*/  type; } ;
struct ccb_pathinq {int /*<<< orphan*/  base_transfer_speed; } ;
struct cam_periph {struct cam_path* path; } ;
struct cam_path {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_PRIORITY_NORMAL ; 
 int CAM_REQ_CMP ; 
 int CAM_STATUS_MASK ; 
 int CTS_ATA_VALID_MODE ; 
 int CTS_SATA_VALID_REVISION ; 
 int /*<<< orphan*/  CTS_TYPE_CURRENT_SETTINGS ; 
 int /*<<< orphan*/  MA_OWNED ; 
 scalar_t__ XPORT_ATA ; 
 scalar_t__ XPORT_SATA ; 
 int /*<<< orphan*/  XPT_GET_TRAN_SETTINGS ; 
 int /*<<< orphan*/  ata_mode2speed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_revision2speed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_periph_assert (struct cam_periph*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_action (union ccb*) ; 
 int /*<<< orphan*/  xpt_path_inq (struct ccb_pathinq*,struct cam_path*) ; 
 int /*<<< orphan*/  xpt_setup_ccb (TYPE_2__*,struct cam_path*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
_ata_announce_periph(struct cam_periph *periph, struct ccb_trans_settings *cts, u_int *speed)
{
	struct	ccb_pathinq cpi;
	struct	cam_path *path = periph->path;

	cam_periph_assert(periph, MA_OWNED);

	xpt_setup_ccb(&cts->ccb_h, path, CAM_PRIORITY_NORMAL);
	cts->ccb_h.func_code = XPT_GET_TRAN_SETTINGS;
	cts->type = CTS_TYPE_CURRENT_SETTINGS;
	xpt_action((union ccb*)cts);
	if ((cts->ccb_h.status & CAM_STATUS_MASK) != CAM_REQ_CMP)
		return;
	/* Ask the SIM for its base transfer speed */
	xpt_path_inq(&cpi, path);
	/* Report connection speed */
	*speed = cpi.base_transfer_speed;
	if (cts->transport == XPORT_ATA) {
		struct	ccb_trans_settings_pata *pata =
		    &cts->xport_specific.ata;

		if (pata->valid & CTS_ATA_VALID_MODE)
			*speed = ata_mode2speed(pata->mode);
	}
	if (cts->transport == XPORT_SATA) {
		struct	ccb_trans_settings_sata *sata =
		    &cts->xport_specific.sata;

		if (sata->valid & CTS_SATA_VALID_REVISION)
			*speed = ata_revision2speed(sata->revision);
	}
}
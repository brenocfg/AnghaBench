#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ status; int /*<<< orphan*/  path; int /*<<< orphan*/  flags; int /*<<< orphan*/  func_code; int /*<<< orphan*/  cbfcnp; } ;
struct TYPE_12__ {int /*<<< orphan*/  flags; } ;
union ccb {TYPE_6__ ccb_h; TYPE_4__ crcn; } ;
struct ccb_pathinq {int hba_misc; TYPE_6__ ccb_h; } ;
struct cam_periph {int flags; scalar_t__ softc; } ;
struct cam_path {TYPE_3__* device; TYPE_2__* target; TYPE_1__* bus; } ;
struct TYPE_13__ {int /*<<< orphan*/  request_ccbs; } ;
typedef  TYPE_5__ probe_softc ;
typedef  scalar_t__ cam_status ;
typedef  int /*<<< orphan*/  cam_flags ;
struct TYPE_15__ {int /*<<< orphan*/  tqe; } ;
struct TYPE_11__ {int /*<<< orphan*/  lun_id; } ;
struct TYPE_10__ {int /*<<< orphan*/  target_id; } ;
struct TYPE_9__ {int /*<<< orphan*/  path_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DEBUG (struct cam_path*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CAM_DEBUG_TRACE ; 
 int /*<<< orphan*/  CAM_PERIPH_BIO ; 
 int CAM_PERIPH_INVALID ; 
 int /*<<< orphan*/  CAM_PRIORITY_NONE ; 
 int /*<<< orphan*/  CAM_PRIORITY_XPT ; 
 scalar_t__ CAM_REQ_CMP ; 
 scalar_t__ CAM_REQ_CMP_ERR ; 
 int /*<<< orphan*/  CAM_UNLOCKED ; 
 int PIM_NOINITIATOR ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XPT_PATH_INQ ; 
 int /*<<< orphan*/  XPT_SCAN_LUN ; 
 scalar_t__ cam_periph_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,union ccb*) ; 
 struct cam_periph* cam_periph_find (struct cam_path*,char*) ; 
 TYPE_7__ periph_links ; 
 int /*<<< orphan*/  probecleanup ; 
 int /*<<< orphan*/  proberegister ; 
 int /*<<< orphan*/  probestart ; 
 int /*<<< orphan*/  xpt_action (union ccb*) ; 
 union ccb* xpt_alloc_ccb_nowait () ; 
 scalar_t__ xpt_create_path (struct cam_path**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_done (union ccb*) ; 
 int /*<<< orphan*/  xpt_free_ccb (union ccb*) ; 
 int /*<<< orphan*/  xpt_path_lock (struct cam_path*) ; 
 scalar_t__ xpt_path_owned (struct cam_path*) ; 
 int /*<<< orphan*/  xpt_path_unlock (struct cam_path*) ; 
 int /*<<< orphan*/  xpt_print (struct cam_path*,char*) ; 
 int /*<<< orphan*/  xpt_setup_ccb (TYPE_6__*,struct cam_path*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xptscandone ; 

__attribute__((used)) static void
scsi_scan_lun(struct cam_periph *periph, struct cam_path *path,
	     cam_flags flags, union ccb *request_ccb)
{
	struct ccb_pathinq cpi;
	cam_status status;
	struct cam_path *new_path;
	struct cam_periph *old_periph;
	int lock;

	CAM_DEBUG(path, CAM_DEBUG_TRACE, ("scsi_scan_lun\n"));

	xpt_setup_ccb(&cpi.ccb_h, path, CAM_PRIORITY_NONE);
	cpi.ccb_h.func_code = XPT_PATH_INQ;
	xpt_action((union ccb *)&cpi);

	if (cpi.ccb_h.status != CAM_REQ_CMP) {
		if (request_ccb != NULL) {
			request_ccb->ccb_h.status = cpi.ccb_h.status;
			xpt_done(request_ccb);
		}
		return;
	}

	if ((cpi.hba_misc & PIM_NOINITIATOR) != 0) {
		/*
		 * Can't scan the bus on an adapter that
		 * cannot perform the initiator role.
		 */
		if (request_ccb != NULL) {
			request_ccb->ccb_h.status = CAM_REQ_CMP;
			xpt_done(request_ccb);
		}
		return;
	}

	if (request_ccb == NULL) {
		request_ccb = xpt_alloc_ccb_nowait();
		if (request_ccb == NULL) {
			xpt_print(path, "scsi_scan_lun: can't allocate CCB, "
			    "can't continue\n");
			return;
		}
		status = xpt_create_path(&new_path, NULL,
					  path->bus->path_id,
					  path->target->target_id,
					  path->device->lun_id);
		if (status != CAM_REQ_CMP) {
			xpt_print(path, "scsi_scan_lun: can't create path, "
			    "can't continue\n");
			xpt_free_ccb(request_ccb);
			return;
		}
		xpt_setup_ccb(&request_ccb->ccb_h, new_path, CAM_PRIORITY_XPT);
		request_ccb->ccb_h.cbfcnp = xptscandone;
		request_ccb->ccb_h.func_code = XPT_SCAN_LUN;
		request_ccb->ccb_h.flags |= CAM_UNLOCKED;
		request_ccb->crcn.flags = flags;
	}

	lock = (xpt_path_owned(path) == 0);
	if (lock)
		xpt_path_lock(path);
	if ((old_periph = cam_periph_find(path, "probe")) != NULL) {
		if ((old_periph->flags & CAM_PERIPH_INVALID) == 0) {
			probe_softc *softc;

			softc = (probe_softc *)old_periph->softc;
			TAILQ_INSERT_TAIL(&softc->request_ccbs,
			    &request_ccb->ccb_h, periph_links.tqe);
		} else {
			request_ccb->ccb_h.status = CAM_REQ_CMP_ERR;
			xpt_done(request_ccb);
		}
	} else {
		status = cam_periph_alloc(proberegister, NULL, probecleanup,
					  probestart, "probe",
					  CAM_PERIPH_BIO,
					  request_ccb->ccb_h.path, NULL, 0,
					  request_ccb);

		if (status != CAM_REQ_CMP) {
			xpt_print(path, "scsi_scan_lun: cam_alloc_periph "
			    "returned an error, can't continue probe\n");
			request_ccb->ccb_h.status = status;
			xpt_done(request_ccb);
		}
	}
	if (lock)
		xpt_path_unlock(path);
}
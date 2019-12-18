#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct targ_softc {int state; scalar_t__ maxio; int /*<<< orphan*/ * periph; } ;
struct TYPE_2__ {int status; } ;
struct ccb_pathinq {int target_sprt; scalar_t__ maxio; TYPE_1__ ccb_h; } ;
struct cam_periph {int unit_number; scalar_t__ softc; } ;
struct cam_path {int dummy; } ;
typedef  int cam_status ;

/* Variables and functions */
 int CAM_FUNC_NOTAVAIL ; 
 int CAM_LUN_ALRDY_ENA ; 
 int /*<<< orphan*/  CAM_PERIPH_BIO ; 
 int CAM_REQ_CMP ; 
 int CAM_STATUS_MASK ; 
 scalar_t__ DFLTPHYS ; 
 scalar_t__ MAXPHYS ; 
 int PIT_PROCESSOR ; 
 int TARG_STATE_LUN_ENABLED ; 
 int cam_periph_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct cam_path*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct targ_softc*) ; 
 struct cam_periph* cam_periph_find (struct cam_path*,char*) ; 
 int /*<<< orphan*/  cam_periph_invalidate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  targasync ; 
 int /*<<< orphan*/  targctor ; 
 int /*<<< orphan*/  targdtor ; 
 int targendislun (struct cam_path*,int,int,int) ; 
 int /*<<< orphan*/  targstart ; 
 int /*<<< orphan*/  xpt_path_inq (struct ccb_pathinq*,struct cam_path*) ; 

__attribute__((used)) static cam_status
targenable(struct targ_softc *softc, struct cam_path *path, int grp6_len,
	   int grp7_len)
{
	struct cam_periph *periph;
	struct ccb_pathinq cpi;
	cam_status	   status;

	if ((softc->state & TARG_STATE_LUN_ENABLED) != 0)
		return (CAM_LUN_ALRDY_ENA);

	/* Make sure SIM supports target mode */
	xpt_path_inq(&cpi, path);
	status = cpi.ccb_h.status & CAM_STATUS_MASK;
	if (status != CAM_REQ_CMP) {
		printf("pathinq failed, status %#x\n", status);
		goto enable_fail;
	}
	if ((cpi.target_sprt & PIT_PROCESSOR) == 0) {
		printf("controller does not support target mode\n");
		status = CAM_FUNC_NOTAVAIL;
		goto enable_fail;
	}
	if (cpi.maxio == 0)
		softc->maxio = DFLTPHYS;	/* traditional default */
	else if (cpi.maxio > MAXPHYS)
		softc->maxio = MAXPHYS;		/* for safety */
	else
		softc->maxio = cpi.maxio;	/* real value */

	/* Destroy any periph on our path if it is disabled */
	periph = cam_periph_find(path, "targ");
	if (periph != NULL) {
		struct targ_softc *del_softc;

		del_softc = (struct targ_softc *)periph->softc;
		if ((del_softc->state & TARG_STATE_LUN_ENABLED) == 0) {
			cam_periph_invalidate(del_softc->periph);
			del_softc->periph = NULL;
		} else {
			printf("Requested path still in use by targ%d\n",
			       periph->unit_number);
			status = CAM_LUN_ALRDY_ENA;
			goto enable_fail;
		}
	}

	/* Create a periph instance attached to this path */
	status = cam_periph_alloc(targctor, NULL, targdtor, targstart,
			"targ", CAM_PERIPH_BIO, path, targasync, 0, softc);
	if (status != CAM_REQ_CMP) {
		printf("cam_periph_alloc failed, status %#x\n", status);
		goto enable_fail;
	}

	/* Ensure that the periph now exists. */
	if (cam_periph_find(path, "targ") == NULL) {
		panic("targenable: succeeded but no periph?");
		/* NOTREACHED */
	}

	/* Send the enable lun message */
	status = targendislun(path, /*enable*/1, grp6_len, grp7_len);
	if (status != CAM_REQ_CMP) {
		printf("enable lun failed, status %#x\n", status);
		goto enable_fail;
	}
	softc->state |= TARG_STATE_LUN_ENABLED;

enable_fail:
	return (status);
}
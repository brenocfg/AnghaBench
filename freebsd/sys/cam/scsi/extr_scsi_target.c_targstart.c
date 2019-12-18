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
struct targ_softc {int /*<<< orphan*/  abort_queue; int /*<<< orphan*/  work_queue; int /*<<< orphan*/  path; } ;
struct targ_cmd_descr {int /*<<< orphan*/  priority; TYPE_2__* user_ccb; } ;
struct cam_periph {int /*<<< orphan*/  path; scalar_t__ softc; } ;
struct TYPE_3__ {int /*<<< orphan*/  status; } ;
struct TYPE_4__ {TYPE_1__ ccb_h; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DEBUG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CAM_DEBUG_PERIPH ; 
 int /*<<< orphan*/  CAM_REQ_CMP_ERR ; 
 struct targ_cmd_descr* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct targ_cmd_descr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct targ_cmd_descr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  notify_user (struct targ_softc*) ; 
 int /*<<< orphan*/  suword (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int targsendccb (struct targ_softc*,union ccb*,struct targ_cmd_descr*) ; 
 int targusermerge (struct targ_softc*,struct targ_cmd_descr*,union ccb*) ; 
 int /*<<< orphan*/  tqe ; 
 int /*<<< orphan*/  xpt_print (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  xpt_release_ccb (union ccb*) ; 
 int /*<<< orphan*/  xpt_schedule (struct cam_periph*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
targstart(struct cam_periph *periph, union ccb *start_ccb)
{
	struct targ_softc *softc;
	struct targ_cmd_descr *descr, *next_descr;
	int error;

	softc = (struct targ_softc *)periph->softc;
	CAM_DEBUG(softc->path, CAM_DEBUG_PERIPH, ("targstart %p\n", start_ccb));

	descr = TAILQ_FIRST(&softc->work_queue);
	if (descr == NULL) {
		xpt_release_ccb(start_ccb);
	} else {
		TAILQ_REMOVE(&softc->work_queue, descr, tqe);
		next_descr = TAILQ_FIRST(&softc->work_queue);

		/* Initiate a transaction using the descr and supplied CCB */
		error = targusermerge(softc, descr, start_ccb);
		if (error == 0)
			error = targsendccb(softc, start_ccb, descr);
		if (error != 0) {
			xpt_print(periph->path,
			    "targsendccb failed, err %d\n", error);
			xpt_release_ccb(start_ccb);
			suword(&descr->user_ccb->ccb_h.status,
			       CAM_REQ_CMP_ERR);
			TAILQ_INSERT_TAIL(&softc->abort_queue, descr, tqe);
			notify_user(softc);
		}

		/* If we have more work to do, stay scheduled */
		if (next_descr != NULL)
			xpt_schedule(periph, next_descr->priority);
	}
}
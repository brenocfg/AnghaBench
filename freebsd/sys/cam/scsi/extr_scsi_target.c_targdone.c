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
struct TYPE_5__ {int status; int func_code; } ;
union ccb {TYPE_2__ ccb_h; } ;
struct targ_softc {int state; int /*<<< orphan*/  periph; int /*<<< orphan*/  user_ccb_queue; int /*<<< orphan*/  pending_ccb_queue; } ;
struct cam_periph {scalar_t__ softc; int /*<<< orphan*/  path; } ;
typedef  int cam_status ;
struct TYPE_4__ {int /*<<< orphan*/  tqe; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DEBUG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CAM_DEBUG_PERIPH ; 
 int CAM_STATUS_MASK ; 
 scalar_t__ TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int TARG_STATE_LUN_ENABLED ; 
#define  XPT_ACCEPT_TARGET_IO 131 
#define  XPT_CONT_TARGET_IO 130 
#define  XPT_IMMEDIATE_NOTIFY 129 
#define  XPT_IMMED_NOTIFY 128 
 int /*<<< orphan*/  cam_periph_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_periph_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  notify_user (struct targ_softc*) ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 TYPE_1__ periph_links ; 
 int /*<<< orphan*/  targfreeccb (struct targ_softc*,union ccb*) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
targdone(struct cam_periph *periph, union ccb *done_ccb)
{
	struct targ_softc *softc;
	cam_status status;

	CAM_DEBUG(periph->path, CAM_DEBUG_PERIPH, ("targdone %p\n", done_ccb));
	softc = (struct targ_softc *)periph->softc;
	TAILQ_REMOVE(&softc->pending_ccb_queue, &done_ccb->ccb_h,
		     periph_links.tqe);
	status = done_ccb->ccb_h.status & CAM_STATUS_MASK;

	/* If we're no longer enabled, throw away CCB */
	if ((softc->state & TARG_STATE_LUN_ENABLED) == 0) {
		targfreeccb(softc, done_ccb);
		return;
	}
	/* abort_all_pending() waits for pending queue to be empty */
	if (TAILQ_EMPTY(&softc->pending_ccb_queue))
		wakeup(&softc->pending_ccb_queue);

	switch (done_ccb->ccb_h.func_code) {
	/* All FC_*_QUEUED CCBs go back to userland */
	case XPT_IMMED_NOTIFY:
	case XPT_IMMEDIATE_NOTIFY:
	case XPT_ACCEPT_TARGET_IO:
	case XPT_CONT_TARGET_IO:
		TAILQ_INSERT_TAIL(&softc->user_ccb_queue, &done_ccb->ccb_h,
				  periph_links.tqe);
 		cam_periph_unlock(softc->periph);
		notify_user(softc);
 		cam_periph_lock(softc->periph);
		break;
	default:
		panic("targdone: impossible xpt opcode %#x",
		      done_ccb->ccb_h.func_code);
		/* NOTREACHED */
	}
}
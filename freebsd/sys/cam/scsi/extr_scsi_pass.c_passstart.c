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
struct TYPE_2__ {int /*<<< orphan*/  cbfcnp; struct pass_io_req* ccb_ioreq; int /*<<< orphan*/  ccb_type; } ;
union ccb {TYPE_1__ ccb_h; } ;
struct pass_softc {int state; int /*<<< orphan*/  incoming_queue; int /*<<< orphan*/  device_stats; int /*<<< orphan*/  active_queue; } ;
struct pass_io_req {int /*<<< orphan*/  start_time; union ccb* alloced_ccb; int /*<<< orphan*/  ccb; } ;
struct cam_periph {scalar_t__ softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_PRIORITY_NORMAL ; 
 int /*<<< orphan*/  PASS_CCB_QUEUED_IO ; 
#define  PASS_STATE_NORMAL 128 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct pass_io_req* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct pass_io_req*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct pass_io_req*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  binuptime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devstat_start_transaction (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  links ; 
 int /*<<< orphan*/  passdone ; 
 int /*<<< orphan*/  xpt_action (union ccb*) ; 
 int /*<<< orphan*/  xpt_merge_ccb (union ccb*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xpt_release_ccb (union ccb*) ; 
 int /*<<< orphan*/  xpt_schedule (struct cam_periph*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
passstart(struct cam_periph *periph, union ccb *start_ccb)
{
	struct pass_softc *softc;

	softc = (struct pass_softc *)periph->softc;

	switch (softc->state) {
	case PASS_STATE_NORMAL: {
		struct pass_io_req *io_req;

		/*
		 * Check for any queued I/O requests that require an
		 * allocated slot.
		 */
		io_req = TAILQ_FIRST(&softc->incoming_queue);
		if (io_req == NULL) {
			xpt_release_ccb(start_ccb);
			break;
		}
		TAILQ_REMOVE(&softc->incoming_queue, io_req, links);
		TAILQ_INSERT_TAIL(&softc->active_queue, io_req, links);
		/*
		 * Merge the user's CCB into the allocated CCB.
		 */
		xpt_merge_ccb(start_ccb, &io_req->ccb);
		start_ccb->ccb_h.ccb_type = PASS_CCB_QUEUED_IO;
		start_ccb->ccb_h.ccb_ioreq = io_req;
		start_ccb->ccb_h.cbfcnp = passdone;
		io_req->alloced_ccb = start_ccb;
		binuptime(&io_req->start_time);
		devstat_start_transaction(softc->device_stats,
					  &io_req->start_time);

		xpt_action(start_ccb);

		/*
		 * If we have any more I/O waiting, schedule ourselves again.
		 */
		if (!TAILQ_EMPTY(&softc->incoming_queue))
			xpt_schedule(periph, CAM_PRIORITY_NORMAL);
		break;
	}
	default:
		break;
	}
}
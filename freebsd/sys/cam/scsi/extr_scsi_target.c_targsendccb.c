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
struct ccb_hdr {scalar_t__ func_code; int /*<<< orphan*/  status; struct targ_cmd_descr* targ_descr; int /*<<< orphan*/  cbfcnp; } ;
union ccb {struct ccb_hdr ccb_h; } ;
struct targ_softc {int /*<<< orphan*/  pending_ccb_queue; int /*<<< orphan*/  path; int /*<<< orphan*/  maxio; } ;
struct cam_periph_map_info {scalar_t__ num_bufs_used; } ;
struct targ_cmd_descr {struct cam_periph_map_info mapinfo; } ;
struct TYPE_2__ {int /*<<< orphan*/  tqe; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DEBUG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CAM_DEBUG_PERIPH ; 
 int /*<<< orphan*/  CAM_REQ_CMP_ERR ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct ccb_hdr*,int /*<<< orphan*/ ) ; 
 scalar_t__ XPT_CONT_TARGET_IO ; 
 scalar_t__ XPT_DEV_MATCH ; 
 scalar_t__ XPT_FC_IS_QUEUED (union ccb*) ; 
 int cam_periph_mapmem (union ccb*,struct cam_periph_map_info*,int /*<<< orphan*/ ) ; 
 TYPE_1__ periph_links ; 
 int /*<<< orphan*/  targdone ; 
 int /*<<< orphan*/  xpt_action (union ccb*) ; 

__attribute__((used)) static int
targsendccb(struct targ_softc *softc, union ccb *ccb,
	    struct targ_cmd_descr *descr)
{
	struct cam_periph_map_info *mapinfo;
	struct ccb_hdr *ccb_h;
	int error;

	ccb_h = &ccb->ccb_h;
	mapinfo = &descr->mapinfo;
	mapinfo->num_bufs_used = 0;

	/*
	 * There's no way for the user to have a completion
	 * function, so we put our own completion function in here.
	 * We also stash in a reference to our descriptor so targreturnccb()
	 * can find our mapping info.
	 */
	ccb_h->cbfcnp = targdone;
	ccb_h->targ_descr = descr;

	if ((ccb_h->func_code == XPT_CONT_TARGET_IO) ||
	    (ccb_h->func_code == XPT_DEV_MATCH)) {

		error = cam_periph_mapmem(ccb, mapinfo, softc->maxio);

		/*
		 * cam_periph_mapmem returned an error, we can't continue.
		 * Return the error to the user.
		 */
		if (error) {
			ccb_h->status = CAM_REQ_CMP_ERR;
			mapinfo->num_bufs_used = 0;
			return (error);
		}
	}

	/*
	 * Once queued on the pending CCB list, this CCB will be protected
	 * by our error recovery handler.
	 */
	CAM_DEBUG(softc->path, CAM_DEBUG_PERIPH, ("sendccb %p\n", ccb));
	if (XPT_FC_IS_QUEUED(ccb)) {
		TAILQ_INSERT_TAIL(&softc->pending_ccb_queue, ccb_h,
				  periph_links.tqe);
	}
	xpt_action(ccb);

	return (0);
}
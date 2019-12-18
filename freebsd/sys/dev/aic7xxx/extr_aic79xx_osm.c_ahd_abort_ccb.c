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
struct ccb_hdr {int func_code; void* status; int /*<<< orphan*/  path; } ;
struct TYPE_3__ {union ccb* abort_ccb; } ;
union ccb {struct ccb_hdr ccb_h; TYPE_1__ cab; } ;
struct ccb_hdr_slist {int dummy; } ;
struct cam_sim {int dummy; } ;
struct ahd_tmode_tstate {int dummy; } ;
struct ahd_tmode_lstate {struct ccb_hdr_slist immed_notifies; struct ccb_hdr_slist accept_tios; } ;
struct ahd_softc {int dummy; } ;
typedef  void* cam_status ;
struct TYPE_4__ {int /*<<< orphan*/  sle; } ;

/* Variables and functions */
 void* CAM_PATH_INVALID ; 
 void* CAM_REQ_ABORTED ; 
 void* CAM_REQ_CMP ; 
 void* CAM_REQ_INVALID ; 
 void* CAM_UA_ABORT ; 
 struct ccb_hdr* SLIST_FIRST (struct ccb_hdr_slist*) ; 
 struct ccb_hdr* SLIST_NEXT (struct ccb_hdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLIST_REMOVE_HEAD (struct ccb_hdr_slist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
#define  XPT_ACCEPT_TARGET_IO 131 
#define  XPT_CONT_TARGET_IO 130 
#define  XPT_IMMEDIATE_NOTIFY 129 
#define  XPT_SCSI_IO 128 
 void* ahd_find_tmode_devs (struct ahd_softc*,struct cam_sim*,union ccb*,struct ahd_tmode_tstate**,struct ahd_tmode_lstate**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 TYPE_2__ sim_links ; 
 int /*<<< orphan*/  xpt_done (union ccb*) ; 
 int /*<<< orphan*/  xpt_print_path (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ahd_abort_ccb(struct ahd_softc *ahd, struct cam_sim *sim, union ccb *ccb)
{
	union ccb *abort_ccb;

	abort_ccb = ccb->cab.abort_ccb;
	switch (abort_ccb->ccb_h.func_code) {
#ifdef AHD_TARGET_MODE
	case XPT_ACCEPT_TARGET_IO:
	case XPT_IMMEDIATE_NOTIFY:
	case XPT_CONT_TARGET_IO:
	{
		struct ahd_tmode_tstate *tstate;
		struct ahd_tmode_lstate *lstate;
		struct ccb_hdr_slist *list;
		cam_status status;

		status = ahd_find_tmode_devs(ahd, sim, abort_ccb, &tstate,
					     &lstate, TRUE);

		if (status != CAM_REQ_CMP) {
			ccb->ccb_h.status = status;
			break;
		}

		if (abort_ccb->ccb_h.func_code == XPT_ACCEPT_TARGET_IO)
			list = &lstate->accept_tios;
		else if (abort_ccb->ccb_h.func_code == XPT_IMMEDIATE_NOTIFY)
			list = &lstate->immed_notifies;
		else
			list = NULL;

		if (list != NULL) {
			struct ccb_hdr *curelm;
			int found;

			curelm = SLIST_FIRST(list);
			found = 0;
			if (curelm == &abort_ccb->ccb_h) {
				found = 1;
				SLIST_REMOVE_HEAD(list, sim_links.sle);
			} else {
				while(curelm != NULL) {
					struct ccb_hdr *nextelm;

					nextelm =
					    SLIST_NEXT(curelm, sim_links.sle);

					if (nextelm == &abort_ccb->ccb_h) {
						found = 1;
						SLIST_NEXT(curelm,
							   sim_links.sle) =
						    SLIST_NEXT(nextelm,
							       sim_links.sle);
						break;
					}
					curelm = nextelm;
				}
			}

			if (found) {
				abort_ccb->ccb_h.status = CAM_REQ_ABORTED;
				xpt_done(abort_ccb);
				ccb->ccb_h.status = CAM_REQ_CMP;
			} else {
				xpt_print_path(abort_ccb->ccb_h.path);
				printf("Not found\n");
				ccb->ccb_h.status = CAM_PATH_INVALID;
			}
			break;
		}
		/* FALLTHROUGH */
	}
#endif
	case XPT_SCSI_IO:
		/* XXX Fully implement the hard ones */
		ccb->ccb_h.status = CAM_UA_ABORT;
		break;
	default:
		ccb->ccb_h.status = CAM_REQ_INVALID;
		break;
	}
	xpt_done(ccb);
}
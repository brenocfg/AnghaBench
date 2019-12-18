#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct ccb_accept_tio* ccb_atio; int /*<<< orphan*/  ccb_type; int /*<<< orphan*/  target_lun; int /*<<< orphan*/  target_id; } ;
struct ccb_scsiio {int /*<<< orphan*/  sense_data; scalar_t__ sense_len; } ;
union ccb {TYPE_1__ ccb_h; struct ccb_scsiio csio; } ;
struct targbh_softc {int /*<<< orphan*/  work_queue; int /*<<< orphan*/  pending_queue; } ;
struct targbh_cmd_desc {scalar_t__ data_resid; scalar_t__ data_increment; int /*<<< orphan*/  timeout; int /*<<< orphan*/ * data; int /*<<< orphan*/  status; } ;
struct ccb_hdr {int dummy; } ;
struct TYPE_5__ {int flags; int status; int /*<<< orphan*/  target_lun; int /*<<< orphan*/  target_id; scalar_t__ ccb_descr; } ;
struct ccb_accept_tio {TYPE_2__ ccb_h; int /*<<< orphan*/  init_id; int /*<<< orphan*/  tag_id; int /*<<< orphan*/  sense_data; scalar_t__ sense_len; } ;
struct cam_periph {int /*<<< orphan*/  path; scalar_t__ softc; } ;
typedef  int ccb_flags ;
struct TYPE_6__ {int /*<<< orphan*/  tqe; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DEBUG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CAM_DEBUG_SUBTRACE ; 
 int CAM_DEV_QFRZN ; 
 int CAM_DIR_MASK ; 
 int CAM_DIS_DISCONNECT ; 
 int /*<<< orphan*/  CAM_PRIORITY_NORMAL ; 
 int CAM_SEND_SENSE ; 
 int CAM_SEND_STATUS ; 
 int CAM_TAG_ACTION_VALID ; 
 int /*<<< orphan*/  MSG_SIMPLE_Q_TAG ; 
 struct ccb_hdr* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct ccb_hdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct ccb_hdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TARGBH_CCB_WORKQ ; 
 int /*<<< orphan*/  cam_fill_ctio (struct ccb_scsiio*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_release_devq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__ periph_links ; 
 int /*<<< orphan*/  targbhdone ; 
 int /*<<< orphan*/  xpt_action (union ccb*) ; 
 int /*<<< orphan*/  xpt_release_ccb (union ccb*) ; 
 int /*<<< orphan*/  xpt_schedule (struct cam_periph*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
targbhstart(struct cam_periph *periph, union ccb *start_ccb)
{
	struct targbh_softc *softc;
	struct ccb_hdr *ccbh;
	struct ccb_accept_tio *atio;
	struct targbh_cmd_desc *desc;
	struct ccb_scsiio *csio;
	ccb_flags flags;

	softc = (struct targbh_softc *)periph->softc;
	
	ccbh = TAILQ_FIRST(&softc->work_queue);
	if (ccbh == NULL) {
		xpt_release_ccb(start_ccb);	
	} else {
		TAILQ_REMOVE(&softc->work_queue, ccbh, periph_links.tqe);
		TAILQ_INSERT_HEAD(&softc->pending_queue, ccbh,
				  periph_links.tqe);
		atio = (struct ccb_accept_tio*)ccbh;
		desc = (struct targbh_cmd_desc *)atio->ccb_h.ccb_descr;

		/* Is this a tagged request? */
		flags = atio->ccb_h.flags &
		    (CAM_DIS_DISCONNECT|CAM_TAG_ACTION_VALID|CAM_DIR_MASK);

		csio = &start_ccb->csio;
		/*
		 * If we are done with the transaction, tell the
		 * controller to send status and perform a CMD_CMPLT.
		 * If we have associated sense data, see if we can
		 * send that too.
		 */
		if (desc->data_resid == desc->data_increment) {
			flags |= CAM_SEND_STATUS;
			if (atio->sense_len) {
				csio->sense_len = atio->sense_len;
				csio->sense_data = atio->sense_data;
				flags |= CAM_SEND_SENSE;
			}

		}

		cam_fill_ctio(csio,
			      /*retries*/2,
			      targbhdone,
			      flags,
			      (flags & CAM_TAG_ACTION_VALID)?
				MSG_SIMPLE_Q_TAG : 0,
			      atio->tag_id,
			      atio->init_id,
			      desc->status,
			      /*data_ptr*/desc->data_increment == 0
					  ? NULL : desc->data,
			      /*dxfer_len*/desc->data_increment,
			      /*timeout*/desc->timeout);

		/* Override our wildcard attachment */
		start_ccb->ccb_h.target_id = atio->ccb_h.target_id;
		start_ccb->ccb_h.target_lun = atio->ccb_h.target_lun;

		start_ccb->ccb_h.ccb_type = TARGBH_CCB_WORKQ;
		start_ccb->ccb_h.ccb_atio = atio;
		CAM_DEBUG(periph->path, CAM_DEBUG_SUBTRACE,
			  ("Sending a CTIO\n"));
		xpt_action(start_ccb);
		/*
		 * If the queue was frozen waiting for the response
		 * to this ATIO (for instance disconnection was disallowed),
		 * then release it now that our response has been queued.
		 */
		if ((atio->ccb_h.status & CAM_DEV_QFRZN) != 0) {
			cam_release_devq(periph->path,
					 /*relsim_flags*/0,
					 /*reduction*/0,
					 /*timeout*/0,
					 /*getcount_only*/0); 
			atio->ccb_h.status &= ~CAM_DEV_QFRZN;
		}
		ccbh = TAILQ_FIRST(&softc->work_queue);
	}
	if (ccbh != NULL)
		xpt_schedule(periph, CAM_PRIORITY_NORMAL);
}
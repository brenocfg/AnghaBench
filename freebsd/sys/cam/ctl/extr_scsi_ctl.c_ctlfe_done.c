#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ io_type; int flags; } ;
struct TYPE_7__ {int task_status; int /*<<< orphan*/  task_resp; } ;
union ctl_io {TYPE_3__ io_hdr; TYPE_2__ taskio; } ;
struct TYPE_10__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  func_code; int /*<<< orphan*/  status; int /*<<< orphan*/  path; } ;
struct TYPE_6__ {int arg; } ;
union ccb {TYPE_5__ ccb_h; TYPE_1__ cna2; } ;
struct ctlfe_lun_softc {int /*<<< orphan*/  work_queue; } ;
struct cam_periph {scalar_t__ softc; } ;
struct TYPE_9__ {int /*<<< orphan*/  stqe; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_PRIORITY_NORMAL ; 
 int /*<<< orphan*/  CAM_REQ_INPROG ; 
 int CAM_RSP_TMF_COMPLETE ; 
 int CAM_RSP_TMF_FAILED ; 
 int CAM_RSP_TMF_INCORRECT_LUN ; 
 int CAM_RSP_TMF_REJECTED ; 
 int CAM_RSP_TMF_SUCCEEDED ; 
 int /*<<< orphan*/  CAM_SEND_STATUS ; 
 int CTL_FLAG_STATUS_QUEUED ; 
 int CTL_FLAG_STATUS_SENT ; 
 scalar_t__ CTL_IO_TASK ; 
#define  CTL_TASK_FUNCTION_COMPLETE 132 
#define  CTL_TASK_FUNCTION_NOT_SUPPORTED 131 
#define  CTL_TASK_FUNCTION_REJECTED 130 
#define  CTL_TASK_FUNCTION_SUCCEEDED 129 
#define  CTL_TASK_LUN_DOES_NOT_EXIST 128 
 union ccb* PRIV_CCB (union ctl_io*) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XPT_NOTIFY_ACKNOWLEDGE ; 
 int /*<<< orphan*/  cam_periph_lock (struct cam_periph*) ; 
 int /*<<< orphan*/  cam_periph_unlock (struct cam_periph*) ; 
 int /*<<< orphan*/  ctlfe_requeue_ccb (struct cam_periph*,union ccb*,int) ; 
 TYPE_4__ periph_links ; 
 int scsi_3btoul (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_action (union ccb*) ; 
 struct cam_periph* xpt_path_periph (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_schedule (struct cam_periph*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ctlfe_done(union ctl_io *io)
{
	union ccb *ccb;
	struct cam_periph *periph;
	struct ctlfe_lun_softc *softc;

	ccb = PRIV_CCB(io);
	periph = xpt_path_periph(ccb->ccb_h.path);
	cam_periph_lock(periph);
	softc = (struct ctlfe_lun_softc *)periph->softc;

	if (io->io_hdr.io_type == CTL_IO_TASK) {
		/*
		 * Send the notify acknowledge down to the SIM, to let it
		 * know we processed the task management command.
		 */
		ccb->ccb_h.status = CAM_REQ_INPROG;
		ccb->ccb_h.func_code = XPT_NOTIFY_ACKNOWLEDGE;
		switch (io->taskio.task_status) {
		case CTL_TASK_FUNCTION_COMPLETE:
			ccb->cna2.arg = CAM_RSP_TMF_COMPLETE;
			break;
		case CTL_TASK_FUNCTION_SUCCEEDED:
			ccb->cna2.arg = CAM_RSP_TMF_SUCCEEDED;
			ccb->ccb_h.flags |= CAM_SEND_STATUS;
			break;
		case CTL_TASK_FUNCTION_REJECTED:
			ccb->cna2.arg = CAM_RSP_TMF_REJECTED;
			ccb->ccb_h.flags |= CAM_SEND_STATUS;
			break;
		case CTL_TASK_LUN_DOES_NOT_EXIST:
			ccb->cna2.arg = CAM_RSP_TMF_INCORRECT_LUN;
			ccb->ccb_h.flags |= CAM_SEND_STATUS;
			break;
		case CTL_TASK_FUNCTION_NOT_SUPPORTED:
			ccb->cna2.arg = CAM_RSP_TMF_FAILED;
			ccb->ccb_h.flags |= CAM_SEND_STATUS;
			break;
		}
		ccb->cna2.arg |= scsi_3btoul(io->taskio.task_resp) << 8;
		xpt_action(ccb);
	} else if (io->io_hdr.flags & CTL_FLAG_STATUS_SENT) {
		ctlfe_requeue_ccb(periph, ccb, /* unlock */1);
		return;
	} else {
		io->io_hdr.flags |= CTL_FLAG_STATUS_QUEUED;
		STAILQ_INSERT_TAIL(&softc->work_queue, &ccb->ccb_h,
				  periph_links.stqe);
		xpt_schedule(periph, CAM_PRIORITY_NORMAL);
	}

	cam_periph_unlock(periph);
}
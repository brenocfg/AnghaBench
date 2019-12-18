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
struct TYPE_5__ {int /*<<< orphan*/  retry_count; int /*<<< orphan*/  path; } ;
struct TYPE_4__ {int scsi_status; } ;
union ccb {TYPE_2__ ccb_h; TYPE_1__ csio; } ;
typedef  int u_int32_t ;
struct TYPE_6__ {int /*<<< orphan*/  func_code; } ;
struct ccb_getdevstats {int dev_active; int dev_openings; int mintags; TYPE_3__ ccb_h; } ;
struct cam_periph {int flags; } ;
typedef  int /*<<< orphan*/  cam_flags ;

/* Variables and functions */
 int CAM_PERIPH_INVALID ; 
 int /*<<< orphan*/  CAM_PRIORITY_NORMAL ; 
 int EIO ; 
 int ERESTART ; 
 int RELSIM_ADJUST_OPENINGS ; 
 int RELSIM_RELEASE_AFTER_CMDCMPLT ; 
 int RELSIM_RELEASE_AFTER_TIMEOUT ; 
#define  SCSI_STATUS_BUSY 136 
#define  SCSI_STATUS_CHECK_COND 135 
#define  SCSI_STATUS_CMD_TERMINATED 134 
#define  SCSI_STATUS_COND_MET 133 
#define  SCSI_STATUS_INTERMED 132 
#define  SCSI_STATUS_INTERMED_COND_MET 131 
#define  SCSI_STATUS_OK 130 
#define  SCSI_STATUS_QUEUE_FULL 129 
#define  SCSI_STATUS_RESERV_CONFLICT 128 
 int SF_RETRY_BUSY ; 
 int SSQ_PRINT_SENSE ; 
 int /*<<< orphan*/  XPT_GDEV_STATS ; 
 int camperiphscsisenseerror (union ccb*,union ccb**,int /*<<< orphan*/ ,int,int*,int*,int*,int*,char const**) ; 
 int /*<<< orphan*/  xpt_action (union ccb*) ; 
 struct cam_periph* xpt_path_periph (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_setup_ccb (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
camperiphscsistatuserror(union ccb *ccb, union ccb **orig_ccb,
    cam_flags camflags, u_int32_t sense_flags,
    int *openings, u_int32_t *relsim_flags,
    u_int32_t *timeout, u_int32_t *action, const char **action_string)
{
	struct cam_periph *periph;
	int error;

	switch (ccb->csio.scsi_status) {
	case SCSI_STATUS_OK:
	case SCSI_STATUS_COND_MET:
	case SCSI_STATUS_INTERMED:
	case SCSI_STATUS_INTERMED_COND_MET:
		error = 0;
		break;
	case SCSI_STATUS_CMD_TERMINATED:
	case SCSI_STATUS_CHECK_COND:
		error = camperiphscsisenseerror(ccb, orig_ccb,
					        camflags,
					        sense_flags,
					        openings,
					        relsim_flags,
					        timeout,
					        action,
					        action_string);
		break;
	case SCSI_STATUS_QUEUE_FULL:
	{
		/* no decrement */
		struct ccb_getdevstats cgds;

		/*
		 * First off, find out what the current
		 * transaction counts are.
		 */
		xpt_setup_ccb(&cgds.ccb_h,
			      ccb->ccb_h.path,
			      CAM_PRIORITY_NORMAL);
		cgds.ccb_h.func_code = XPT_GDEV_STATS;
		xpt_action((union ccb *)&cgds);

		/*
		 * If we were the only transaction active, treat
		 * the QUEUE FULL as if it were a BUSY condition.
		 */
		if (cgds.dev_active != 0) {
			int total_openings;

			/*
		 	 * Reduce the number of openings to
			 * be 1 less than the amount it took
			 * to get a queue full bounded by the
			 * minimum allowed tag count for this
			 * device.
		 	 */
			total_openings = cgds.dev_active + cgds.dev_openings;
			*openings = cgds.dev_active;
			if (*openings < cgds.mintags)
				*openings = cgds.mintags;
			if (*openings < total_openings)
				*relsim_flags = RELSIM_ADJUST_OPENINGS;
			else {
				/*
				 * Some devices report queue full for
				 * temporary resource shortages.  For
				 * this reason, we allow a minimum
				 * tag count to be entered via a
				 * quirk entry to prevent the queue
				 * count on these devices from falling
				 * to a pessimisticly low value.  We
				 * still wait for the next successful
				 * completion, however, before queueing
				 * more transactions to the device.
				 */
				*relsim_flags = RELSIM_RELEASE_AFTER_CMDCMPLT;
			}
			*timeout = 0;
			error = ERESTART;
			*action &= ~SSQ_PRINT_SENSE;
			break;
		}
		/* FALLTHROUGH */
	}
	case SCSI_STATUS_BUSY:
		/*
		 * Restart the queue after either another
		 * command completes or a 1 second timeout.
		 */
		periph = xpt_path_periph(ccb->ccb_h.path);
		if (periph->flags & CAM_PERIPH_INVALID) {
			error = EIO;
			*action_string = "Periph was invalidated";
		} else if ((sense_flags & SF_RETRY_BUSY) != 0 ||
		    ccb->ccb_h.retry_count > 0) {
			if ((sense_flags & SF_RETRY_BUSY) == 0)
				ccb->ccb_h.retry_count--;
			error = ERESTART;
			*relsim_flags = RELSIM_RELEASE_AFTER_TIMEOUT
				      | RELSIM_RELEASE_AFTER_CMDCMPLT;
			*timeout = 1000;
		} else {
			error = EIO;
			*action_string = "Retries exhausted";
		}
		break;
	case SCSI_STATUS_RESERV_CONFLICT:
	default:
		error = EIO;
		break;
	}
	return (error);
}
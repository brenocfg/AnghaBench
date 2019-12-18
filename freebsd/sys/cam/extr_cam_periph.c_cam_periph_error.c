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
struct TYPE_4__ {int status; struct cam_path* path; int /*<<< orphan*/  func_code; int /*<<< orphan*/  retry_count; } ;
struct TYPE_3__ {scalar_t__ flags; } ;
union ccb {TYPE_2__ ccb_h; TYPE_1__ crcn; } ;
typedef  scalar_t__ u_int32_t ;
struct cam_periph {int flags; } ;
struct cam_path {int dummy; } ;
typedef  int /*<<< orphan*/  lun_id_t ;
typedef  int cam_status ;
typedef  int cam_flags ;

/* Variables and functions */
 int /*<<< orphan*/  AC_LOST_DEVICE ; 
 int /*<<< orphan*/  AC_UNIT_ATTENTION ; 
#define  CAM_ATA_STATUS_ERROR 158 
#define  CAM_AUTOSENSE_FAIL 157 
#define  CAM_BDR_SENT 156 
#define  CAM_BUSY 155 
#define  CAM_CMD_TIMEOUT 154 
#define  CAM_DATA_RUN_ERR 153 
 scalar_t__ CAM_DEBUGGED (struct cam_path*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CAM_DEBUG_INFO ; 
#define  CAM_DEV_NOT_THERE 152 
 int CAM_DEV_QFRZN ; 
 int /*<<< orphan*/  CAM_EPF_ALL ; 
 int /*<<< orphan*/  CAM_ESF_ALL ; 
#define  CAM_FUNC_NOTAVAIL 151 
#define  CAM_LUN_INVALID 150 
 int /*<<< orphan*/  CAM_LUN_WILDCARD ; 
#define  CAM_MSG_REJECT_REC 149 
#define  CAM_NO_HBA 148 
#define  CAM_PATH_INVALID 147 
 int CAM_PERIPH_INVALID ; 
#define  CAM_PROVIDE_FAIL 146 
#define  CAM_REQUEUE_REQ 145 
#define  CAM_REQ_ABORTED 144 
#define  CAM_REQ_CMP 143 
#define  CAM_REQ_CMP_ERR 142 
#define  CAM_REQ_INVALID 141 
#define  CAM_REQ_TERMIO 140 
#define  CAM_REQ_TOO_BIG 139 
#define  CAM_RESRC_UNAVAIL 138 
 int CAM_RETRY_SELTO ; 
#define  CAM_SCSI_BUS_RESET 137 
#define  CAM_SCSI_STATUS_ERROR 136 
#define  CAM_SEL_TIMEOUT 135 
#define  CAM_SMP_STATUS_ERROR 134 
 int CAM_STATUS_MASK ; 
#define  CAM_TID_INVALID 133 
#define  CAM_UA_ABORT 132 
#define  CAM_UA_TERMIO 131 
#define  CAM_UNCOR_PARITY 130 
#define  CAM_UNEXP_BUSFREE 129 
#define  CAM_UNREC_HBA_ERROR 128 
 int EINVAL ; 
 int EIO ; 
 int ENXIO ; 
 int ERESTART ; 
 scalar_t__ RELSIM_RELEASE_AFTER_TIMEOUT ; 
 scalar_t__ SF_NO_PRINT ; 
 scalar_t__ SF_NO_RETRY ; 
 scalar_t__ SF_PRINT_ALWAYS ; 
 scalar_t__ SSQ_LOST ; 
 scalar_t__ SSQ_PRINT_SENSE ; 
 scalar_t__ SSQ_RESCAN ; 
 scalar_t__ SSQ_UA ; 
 int /*<<< orphan*/  XPT_SCAN_TGT ; 
 int /*<<< orphan*/  cam_error_print (union ccb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_periph_devctl_notify (union ccb*) ; 
 int /*<<< orphan*/  cam_release_devq (struct cam_path*,scalar_t__,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int camperiphscsistatuserror (union ccb*,union ccb**,int,scalar_t__,int*,scalar_t__*,scalar_t__*,scalar_t__*,char const**) ; 
 scalar_t__ periph_busy_delay ; 
 scalar_t__ periph_noresrc_delay ; 
 scalar_t__ periph_selto_delay ; 
 int /*<<< orphan*/  xpt_action (union ccb*) ; 
 union ccb* xpt_alloc_ccb_nowait () ; 
 int /*<<< orphan*/  xpt_async (int /*<<< orphan*/ ,struct cam_path*,union ccb*) ; 
 int const xpt_create_path (struct cam_path**,struct cam_periph*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_free_path (struct cam_path*) ; 
 int /*<<< orphan*/  xpt_path_lun_id (struct cam_path*) ; 
 int /*<<< orphan*/  xpt_path_path_id (struct cam_path*) ; 
 struct cam_periph* xpt_path_periph (struct cam_path*) ; 
 int /*<<< orphan*/  xpt_path_target_id (struct cam_path*) ; 
 int /*<<< orphan*/  xpt_print (struct cam_path*,char*,...) ; 
 int /*<<< orphan*/  xpt_rescan (union ccb*) ; 

int
cam_periph_error(union ccb *ccb, cam_flags camflags,
		 u_int32_t sense_flags)
{
	struct cam_path *newpath;
	union ccb  *orig_ccb, *scan_ccb;
	struct cam_periph *periph;
	const char *action_string;
	cam_status  status;
	int	    frozen, error, openings, devctl_err;
	u_int32_t   action, relsim_flags, timeout;

	action = SSQ_PRINT_SENSE;
	periph = xpt_path_periph(ccb->ccb_h.path);
	action_string = NULL;
	status = ccb->ccb_h.status;
	frozen = (status & CAM_DEV_QFRZN) != 0;
	status &= CAM_STATUS_MASK;
	devctl_err = openings = relsim_flags = timeout = 0;
	orig_ccb = ccb;

	/* Filter the errors that should be reported via devctl */
	switch (ccb->ccb_h.status & CAM_STATUS_MASK) {
	case CAM_CMD_TIMEOUT:
	case CAM_REQ_ABORTED:
	case CAM_REQ_CMP_ERR:
	case CAM_REQ_TERMIO:
	case CAM_UNREC_HBA_ERROR:
	case CAM_DATA_RUN_ERR:
	case CAM_SCSI_STATUS_ERROR:
	case CAM_ATA_STATUS_ERROR:
	case CAM_SMP_STATUS_ERROR:
		devctl_err++;
		break;
	default:
		break;
	}

	switch (status) {
	case CAM_REQ_CMP:
		error = 0;
		action &= ~SSQ_PRINT_SENSE;
		break;
	case CAM_SCSI_STATUS_ERROR:
		error = camperiphscsistatuserror(ccb, &orig_ccb,
		    camflags, sense_flags, &openings, &relsim_flags,
		    &timeout, &action, &action_string);
		break;
	case CAM_AUTOSENSE_FAIL:
		error = EIO;	/* we have to kill the command */
		break;
	case CAM_UA_ABORT:
	case CAM_UA_TERMIO:
	case CAM_MSG_REJECT_REC:
		/* XXX Don't know that these are correct */
		error = EIO;
		break;
	case CAM_SEL_TIMEOUT:
		if ((camflags & CAM_RETRY_SELTO) != 0) {
			if (ccb->ccb_h.retry_count > 0 &&
			    (periph->flags & CAM_PERIPH_INVALID) == 0) {
				ccb->ccb_h.retry_count--;
				error = ERESTART;

				/*
				 * Wait a bit to give the device
				 * time to recover before we try again.
				 */
				relsim_flags = RELSIM_RELEASE_AFTER_TIMEOUT;
				timeout = periph_selto_delay;
				break;
			}
			action_string = "Retries exhausted";
		}
		/* FALLTHROUGH */
	case CAM_DEV_NOT_THERE:
		error = ENXIO;
		action = SSQ_LOST;
		break;
	case CAM_REQ_INVALID:
	case CAM_PATH_INVALID:
	case CAM_NO_HBA:
	case CAM_PROVIDE_FAIL:
	case CAM_REQ_TOO_BIG:
	case CAM_LUN_INVALID:
	case CAM_TID_INVALID:
	case CAM_FUNC_NOTAVAIL:
		error = EINVAL;
		break;
	case CAM_SCSI_BUS_RESET:
	case CAM_BDR_SENT:
		/*
		 * Commands that repeatedly timeout and cause these
		 * kinds of error recovery actions, should return
		 * CAM_CMD_TIMEOUT, which allows us to safely assume
		 * that this command was an innocent bystander to
		 * these events and should be unconditionally
		 * retried.
		 */
	case CAM_REQUEUE_REQ:
		/* Unconditional requeue if device is still there */
		if (periph->flags & CAM_PERIPH_INVALID) {
			action_string = "Periph was invalidated";
			error = EIO;
		} else if (sense_flags & SF_NO_RETRY) {
			error = EIO;
			action_string = "Retry was blocked";
		} else {
			error = ERESTART;
			action &= ~SSQ_PRINT_SENSE;
		}
		break;
	case CAM_RESRC_UNAVAIL:
		/* Wait a bit for the resource shortage to abate. */
		timeout = periph_noresrc_delay;
		/* FALLTHROUGH */
	case CAM_BUSY:
		if (timeout == 0) {
			/* Wait a bit for the busy condition to abate. */
			timeout = periph_busy_delay;
		}
		relsim_flags = RELSIM_RELEASE_AFTER_TIMEOUT;
		/* FALLTHROUGH */
	case CAM_ATA_STATUS_ERROR:
	case CAM_REQ_CMP_ERR:
	case CAM_CMD_TIMEOUT:
	case CAM_UNEXP_BUSFREE:
	case CAM_UNCOR_PARITY:
	case CAM_DATA_RUN_ERR:
	default:
		if (periph->flags & CAM_PERIPH_INVALID) {
			error = EIO;
			action_string = "Periph was invalidated";
		} else if (ccb->ccb_h.retry_count == 0) {
			error = EIO;
			action_string = "Retries exhausted";
		} else if (sense_flags & SF_NO_RETRY) {
			error = EIO;
			action_string = "Retry was blocked";
		} else {
			ccb->ccb_h.retry_count--;
			error = ERESTART;
		}
		break;
	}

	if ((sense_flags & SF_PRINT_ALWAYS) ||
	    CAM_DEBUGGED(ccb->ccb_h.path, CAM_DEBUG_INFO))
		action |= SSQ_PRINT_SENSE;
	else if (sense_flags & SF_NO_PRINT)
		action &= ~SSQ_PRINT_SENSE;
	if ((action & SSQ_PRINT_SENSE) != 0)
		cam_error_print(orig_ccb, CAM_ESF_ALL, CAM_EPF_ALL);
	if (error != 0 && (action & SSQ_PRINT_SENSE) != 0) {
		if (error != ERESTART) {
			if (action_string == NULL)
				action_string = "Unretryable error";
			xpt_print(ccb->ccb_h.path, "Error %d, %s\n",
			    error, action_string);
		} else if (action_string != NULL)
			xpt_print(ccb->ccb_h.path, "%s\n", action_string);
		else {
			xpt_print(ccb->ccb_h.path,
			    "Retrying command, %d more tries remain\n",
			    ccb->ccb_h.retry_count);
		}
	}

	if (devctl_err && (error != 0 || (action & SSQ_PRINT_SENSE) != 0))
		cam_periph_devctl_notify(orig_ccb);

	if ((action & SSQ_LOST) != 0) {
		lun_id_t lun_id;

		/*
		 * For a selection timeout, we consider all of the LUNs on
		 * the target to be gone.  If the status is CAM_DEV_NOT_THERE,
		 * then we only get rid of the device(s) specified by the
		 * path in the original CCB.
		 */
		if (status == CAM_SEL_TIMEOUT)
			lun_id = CAM_LUN_WILDCARD;
		else
			lun_id = xpt_path_lun_id(ccb->ccb_h.path);

		/* Should we do more if we can't create the path?? */
		if (xpt_create_path(&newpath, periph,
				    xpt_path_path_id(ccb->ccb_h.path),
				    xpt_path_target_id(ccb->ccb_h.path),
				    lun_id) == CAM_REQ_CMP) {

			/*
			 * Let peripheral drivers know that this
			 * device has gone away.
			 */
			xpt_async(AC_LOST_DEVICE, newpath, NULL);
			xpt_free_path(newpath);
		}
	}

	/* Broadcast UNIT ATTENTIONs to all periphs. */
	if ((action & SSQ_UA) != 0)
		xpt_async(AC_UNIT_ATTENTION, orig_ccb->ccb_h.path, orig_ccb);

	/* Rescan target on "Reported LUNs data has changed" */
	if ((action & SSQ_RESCAN) != 0) {
		if (xpt_create_path(&newpath, NULL,
				    xpt_path_path_id(ccb->ccb_h.path),
				    xpt_path_target_id(ccb->ccb_h.path),
				    CAM_LUN_WILDCARD) == CAM_REQ_CMP) {

			scan_ccb = xpt_alloc_ccb_nowait();
			if (scan_ccb != NULL) {
				scan_ccb->ccb_h.path = newpath;
				scan_ccb->ccb_h.func_code = XPT_SCAN_TGT;
				scan_ccb->crcn.flags = 0;
				xpt_rescan(scan_ccb);
			} else {
				xpt_print(newpath,
				    "Can't allocate CCB to rescan target\n");
				xpt_free_path(newpath);
			}
		}
	}

	/* Attempt a retry */
	if (error == ERESTART || error == 0) {
		if (frozen != 0)
			ccb->ccb_h.status &= ~CAM_DEV_QFRZN;
		if (error == ERESTART)
			xpt_action(ccb);
		if (frozen != 0)
			cam_release_devq(ccb->ccb_h.path,
					 relsim_flags,
					 openings,
					 timeout,
					 /*getcount_only*/0);
	}

	return (error);
}
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
struct TYPE_6__ {int status; scalar_t__ cbfcnp; int /*<<< orphan*/  path; scalar_t__ retry_count; scalar_t__ saved_ccb_ptr; } ;
struct TYPE_4__ {int /*<<< orphan*/  cdb_bytes; } ;
struct TYPE_5__ {TYPE_1__ cdb_io; } ;
union ccb {TYPE_3__ ccb_h; TYPE_2__ csio; } ;
struct scsi_start_stop_unit {scalar_t__ opcode; int how; } ;
struct cam_periph {int /*<<< orphan*/  flags; } ;
typedef  int cam_status ;

/* Variables and functions */
 int /*<<< orphan*/  AC_INQ_CHANGED ; 
 int CAM_DEV_QFRZN ; 
 int /*<<< orphan*/  CAM_PERIPH_RECOVERY_INPROG ; 
 int CAM_REQ_CMP ; 
 int CAM_STATUS_MASK ; 
 int ERESTART ; 
 int SF_NO_PRINT ; 
 int SF_RETRY_UA ; 
 int SSS_LOEJ ; 
 scalar_t__ START_STOP_UNIT ; 
 int /*<<< orphan*/  bcopy (union ccb*,union ccb*,int) ; 
 int cam_periph_error (union ccb*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cam_release_devq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ scsi_extract_sense_ccb (union ccb*,int*,int*,int*,int*) ; 
 int /*<<< orphan*/  xpt_action (union ccb*) ; 
 int /*<<< orphan*/  xpt_async (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xpt_free_ccb (union ccb*) ; 

__attribute__((used)) static void
camperiphdone(struct cam_periph *periph, union ccb *done_ccb)
{
	union ccb      *saved_ccb;
	cam_status	status;
	struct scsi_start_stop_unit *scsi_cmd;
	int		error = 0, error_code, sense_key, asc, ascq;

	scsi_cmd = (struct scsi_start_stop_unit *)
	    &done_ccb->csio.cdb_io.cdb_bytes;
	status = done_ccb->ccb_h.status;

	if ((status & CAM_STATUS_MASK) != CAM_REQ_CMP) {
		if (scsi_extract_sense_ccb(done_ccb,
		    &error_code, &sense_key, &asc, &ascq)) {
			/*
			 * If the error is "invalid field in CDB",
			 * and the load/eject flag is set, turn the
			 * flag off and try again.  This is just in
			 * case the drive in question barfs on the
			 * load eject flag.  The CAM code should set
			 * the load/eject flag by default for
			 * removable media.
			 */
			if ((scsi_cmd->opcode == START_STOP_UNIT) &&
			    ((scsi_cmd->how & SSS_LOEJ) != 0) &&
			     (asc == 0x24) && (ascq == 0x00)) {
				scsi_cmd->how &= ~SSS_LOEJ;
				if (status & CAM_DEV_QFRZN) {
					cam_release_devq(done_ccb->ccb_h.path,
					    0, 0, 0, 0);
					done_ccb->ccb_h.status &=
					    ~CAM_DEV_QFRZN;
				}
				xpt_action(done_ccb);
				goto out;
			}
		}
		error = cam_periph_error(done_ccb, 0,
		    SF_RETRY_UA | SF_NO_PRINT);
		if (error == ERESTART)
			goto out;
		if (done_ccb->ccb_h.status & CAM_DEV_QFRZN) {
			cam_release_devq(done_ccb->ccb_h.path, 0, 0, 0, 0);
			done_ccb->ccb_h.status &= ~CAM_DEV_QFRZN;
		}
	} else {
		/*
		 * If we have successfully taken a device from the not
		 * ready to ready state, re-scan the device and re-get
		 * the inquiry information.  Many devices (mostly disks)
		 * don't properly report their inquiry information unless
		 * they are spun up.
		 */
		if (scsi_cmd->opcode == START_STOP_UNIT)
			xpt_async(AC_INQ_CHANGED, done_ccb->ccb_h.path, NULL);
	}

	/*
	 * After recovery action(s) completed, return to the original CCB.
	 * If the recovery CCB has failed, considering its own possible
	 * retries and recovery, assume we are back in state where we have
	 * been originally, but without recovery hopes left.  In such case,
	 * after the final attempt below, we cancel any further retries,
	 * blocking by that also any new recovery attempts for this CCB,
	 * and the result will be the final one returned to the CCB owher.
	 */
	saved_ccb = (union ccb *)done_ccb->ccb_h.saved_ccb_ptr;
	bcopy(saved_ccb, done_ccb, sizeof(*done_ccb));
	xpt_free_ccb(saved_ccb);
	if (done_ccb->ccb_h.cbfcnp != camperiphdone)
		periph->flags &= ~CAM_PERIPH_RECOVERY_INPROG;
	if (error != 0)
		done_ccb->ccb_h.retry_count = 0;
	xpt_action(done_ccb);

out:
	/* Drop freeze taken due to CAM_DEV_QFREEZE flag set. */
	cam_release_devq(done_ccb->ccb_h.path, 0, 0, 0, 0);
}
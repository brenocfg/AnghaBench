#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct scsi_sense_data {int dummy; } ;
struct TYPE_6__ {scalar_t__ sense_resid; scalar_t__ sense_len; struct scsi_sense_data sense_data; } ;
struct TYPE_5__ {int status; int /*<<< orphan*/  flags; } ;
union ccb {TYPE_2__ csio; TYPE_1__ ccb_h; } ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int u_int ;
struct cam_device {int dummy; } ;
typedef  int cam_status ;

/* Variables and functions */
 int CAM_ARG_VERBOSE ; 
 int CAM_AUTOSNS_VALID ; 
 int /*<<< orphan*/  CAM_DEV_QFRZDIS ; 
 int /*<<< orphan*/  CAM_EPF_ALL ; 
 int /*<<< orphan*/  CAM_ESF_ALL ; 
 int CAM_REQUEUE_REQ ; 
 int CAM_REQ_CMP ; 
 int CAM_SCSI_STATUS_ERROR ; 
 int CAM_STATUS_MASK ; 
 int /*<<< orphan*/  CCB_CLEAR_ALL_EXCEPT_HDR (TYPE_2__*) ; 
 int /*<<< orphan*/  SSD_FULL_SIZE ; 
 int SSD_KEY_NOT_READY ; 
 int arglist ; 
 int /*<<< orphan*/  cam_error_print (struct cam_device*,union ccb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cam_send_ccb (struct cam_device*,union ccb*) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,int,int) ; 
 int scsi_2btoul (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_extract_sense_len (struct scsi_sense_data*,scalar_t__,int*,int*,int*,int*,int) ; 
 scalar_t__ scsi_get_sks (struct scsi_sense_data*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_sense_print (struct cam_device*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_test_unit_ready (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  warn (char*) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

__attribute__((used)) static int
sanitize_wait_scsi(struct cam_device *device, union ccb *ccb, int task_attr, int quiet)
{
	int warnings = 0, retval;
	cam_status status;
	u_int val, perc;

	do {
		CCB_CLEAR_ALL_EXCEPT_HDR(&ccb->csio);

		/*
		 * There's really no need to do error recovery or
		 * retries here, since we're just going to sit in a
		 * loop and wait for the device to finish sanitizing.
		 */
		scsi_test_unit_ready(&ccb->csio,
				     /* retries */ 0,
				     /* cbfcnp */ NULL,
				     /* tag_action */ task_attr,
				     /* sense_len */ SSD_FULL_SIZE,
				     /* timeout */ 5000);

		/* Disable freezing the device queue */
		ccb->ccb_h.flags |= CAM_DEV_QFRZDIS;

		retval = cam_send_ccb(device, ccb);

		/*
		 * If we get an error from the ioctl, bail out.  SCSI
		 * errors are expected.
		 */
		if (retval < 0) {
			warn("error sending TEST UNIT READY command");
			return (1);
		}

		status = ccb->ccb_h.status & CAM_STATUS_MASK;
		if ((status == CAM_SCSI_STATUS_ERROR) &&
		    ((ccb->ccb_h.status & CAM_AUTOSNS_VALID) != 0)) {
			struct scsi_sense_data *sense;
			int error_code, sense_key, asc, ascq;

			sense = &ccb->csio.sense_data;
			scsi_extract_sense_len(sense, ccb->csio.sense_len -
			    ccb->csio.sense_resid, &error_code, &sense_key,
			    &asc, &ascq, /*show_errors*/ 1);

			/*
			 * According to the SCSI-3 spec, a drive that is in the
			 * middle of a sanitize should return NOT READY with an
			 * ASC of "logical unit not ready, sanitize in
			 * progress". The sense key specific bytes will then
			 * be a progress indicator.
			 */
			if ((sense_key == SSD_KEY_NOT_READY)
			 && (asc == 0x04) && (ascq == 0x1b)) {
				uint8_t sks[3];

				if ((scsi_get_sks(sense, ccb->csio.sense_len -
				     ccb->csio.sense_resid, sks) == 0)
				 && (quiet == 0)) {
					val = scsi_2btoul(&sks[1]);
					perc = 10000 * val;
					fprintf(stdout,
					    "Sanitizing: %u.%02u%% (%d/%d)\r",
					    (perc / (0x10000 * 100)),
					    ((perc / 0x10000) % 100),
					    val, 0x10000);
					fflush(stdout);
				} else if ((quiet == 0) && (++warnings <= 1)) {
					warnx("Unexpected SCSI Sense Key "
					      "Specific value returned "
					      "during sanitize:");
					scsi_sense_print(device, &ccb->csio,
							 stderr);
					warnx("Unable to print status "
					      "information, but sanitze will "
					      "proceed.");
					warnx("will exit when sanitize is "
					      "complete");
				}
				sleep(1);
			} else {
				warnx("Unexpected SCSI error during sanitize");
				cam_error_print(device, ccb, CAM_ESF_ALL,
						CAM_EPF_ALL, stderr);
				return (1);
			}

		} else if (status != CAM_REQ_CMP && status != CAM_REQUEUE_REQ) {
			warnx("Unexpected CAM status %#x", status);
			if (arglist & CAM_ARG_VERBOSE)
				cam_error_print(device, ccb, CAM_ESF_ALL,
						CAM_EPF_ALL, stderr);
			return (1);
		}
	} while ((ccb->ccb_h.status & CAM_STATUS_MASK) != CAM_REQ_CMP);
	return (0);
}
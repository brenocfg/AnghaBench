#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int status; int /*<<< orphan*/  flags; } ;
struct TYPE_5__ {scalar_t__ cdb_bytes; } ;
struct TYPE_7__ {int cdb_len; TYPE_1__ cdb_io; } ;
union ccb {TYPE_2__ ccb_h; TYPE_3__ csio; } ;
typedef  int /*<<< orphan*/  u_int8_t ;
struct scsi_mode_sense_10 {int /*<<< orphan*/  byte2; } ;
struct cam_device {int dummy; } ;

/* Variables and functions */
 int CAM_ARG_ERR_RECOVER ; 
 int CAM_ARG_VERBOSE ; 
 int /*<<< orphan*/  CAM_DEV_QFRZDIS ; 
 int /*<<< orphan*/  CAM_EPF_ALL ; 
 int /*<<< orphan*/  CAM_ESF_ALL ; 
 int /*<<< orphan*/  CAM_PASS_ERR_RECOVER ; 
 int CAM_REQ_CMP ; 
 int CAM_REQ_INVALID ; 
 int CAM_STATUS_MASK ; 
 int /*<<< orphan*/  CCB_CLEAR_ALL_EXCEPT_HDR (TYPE_3__*) ; 
 int /*<<< orphan*/  SMS10_LLBAA ; 
 int /*<<< orphan*/  SSD_FULL_SIZE ; 
 int SSD_KEY_ILLEGAL_REQUEST ; 
 int arglist ; 
 int /*<<< orphan*/  cam_close_device (struct cam_device*) ; 
 int /*<<< orphan*/  cam_error_print (struct cam_device*,union ccb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_freeccb (union ccb*) ; 
 union ccb* cam_getccb (struct cam_device*) ; 
 scalar_t__ cam_send_ccb (struct cam_device*,union ccb*) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 scalar_t__ scsi_extract_sense_ccb (union ccb*,int*,int*,int*,int*) ; 
 int /*<<< orphan*/  scsi_mode_sense_subpage (TYPE_3__*,int,int /*<<< orphan*/ *,int,int,int,int,int,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stderr ; 

void
mode_sense(struct cam_device *device, int *cdb_len, int dbd, int llbaa, int pc,
    int page, int subpage, int task_attr, int retry_count, int timeout,
    u_int8_t *data, int datalen)
{
	union ccb *ccb;
	int error_code, sense_key, asc, ascq;

	ccb = cam_getccb(device);
	if (ccb == NULL)
		errx(1, "mode_sense: couldn't allocate CCB");

retry:
	/*
	 * MODE SENSE(6) can't handle more then 255 bytes.  If there are more,
	 * device must return error, so we should not get trucated data.
	 */
	if (*cdb_len == 6 && datalen > 255)
		datalen = 255;

	CCB_CLEAR_ALL_EXCEPT_HDR(&ccb->csio);

	scsi_mode_sense_subpage(&ccb->csio,
			/* retries */ retry_count,
			/* cbfcnp */ NULL,
			/* tag_action */ task_attr,
			/* dbd */ dbd,
			/* pc */ pc << 6,
			/* page */ page,
			/* subpage */ subpage,
			/* param_buf */ data,
			/* param_len */ datalen,
			/* minimum_cmd_size */ *cdb_len,
			/* sense_len */ SSD_FULL_SIZE,
			/* timeout */ timeout ? timeout : 5000);
	if (llbaa && ccb->csio.cdb_len == 10) {
		struct scsi_mode_sense_10 *cdb =
		    (struct scsi_mode_sense_10 *)ccb->csio.cdb_io.cdb_bytes;
		cdb->byte2 |= SMS10_LLBAA;
	}

	/* Record what CDB size the above function really set. */
	*cdb_len = ccb->csio.cdb_len;

	if (arglist & CAM_ARG_ERR_RECOVER)
		ccb->ccb_h.flags |= CAM_PASS_ERR_RECOVER;

	/* Disable freezing the device queue */
	ccb->ccb_h.flags |= CAM_DEV_QFRZDIS;

	if (cam_send_ccb(device, ccb) < 0)
		err(1, "error sending mode sense command");

	/* In case of ILLEGEL REQUEST try to fall back to 6-byte command. */
	if (*cdb_len != 6 &&
	    ((ccb->ccb_h.status & CAM_STATUS_MASK) == CAM_REQ_INVALID ||
	     (scsi_extract_sense_ccb(ccb, &error_code, &sense_key, &asc, &ascq)
	      && sense_key == SSD_KEY_ILLEGAL_REQUEST))) {
		*cdb_len = 6;
		goto retry;
	}

	if ((ccb->ccb_h.status & CAM_STATUS_MASK) != CAM_REQ_CMP) {
		if (arglist & CAM_ARG_VERBOSE) {
			cam_error_print(device, ccb, CAM_ESF_ALL,
					CAM_EPF_ALL, stderr);
		}
		cam_freeccb(ccb);
		cam_close_device(device);
		errx(1, "mode sense command returned error");
	}

	cam_freeccb(ccb);
}
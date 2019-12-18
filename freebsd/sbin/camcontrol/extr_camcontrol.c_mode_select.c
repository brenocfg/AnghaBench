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
struct TYPE_2__ {int status; int /*<<< orphan*/  flags; } ;
union ccb {TYPE_1__ ccb_h; int /*<<< orphan*/  csio; } ;
typedef  int /*<<< orphan*/  u_int8_t ;
struct cam_device {int dummy; } ;

/* Variables and functions */
 int CAM_ARG_ERR_RECOVER ; 
 int CAM_ARG_VERBOSE ; 
 int /*<<< orphan*/  CAM_DEV_QFRZDIS ; 
 int /*<<< orphan*/  CAM_EPF_ALL ; 
 int /*<<< orphan*/  CAM_ESF_ALL ; 
 int /*<<< orphan*/  CAM_PASS_ERR_RECOVER ; 
 int CAM_REQ_CMP ; 
 int CAM_STATUS_MASK ; 
 int /*<<< orphan*/  CCB_CLEAR_ALL_EXCEPT_HDR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSD_FULL_SIZE ; 
 int arglist ; 
 int /*<<< orphan*/  cam_close_device (struct cam_device*) ; 
 int /*<<< orphan*/  cam_error_print (struct cam_device*,union ccb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_freeccb (union ccb*) ; 
 union ccb* cam_getccb (struct cam_device*) ; 
 int cam_send_ccb (struct cam_device*,union ccb*) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  scsi_mode_select_len (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stderr ; 

void
mode_select(struct cam_device *device, int cdb_len, int save_pages,
    int task_attr, int retry_count, int timeout, u_int8_t *data, int datalen)
{
	union ccb *ccb;
	int retval;

	ccb = cam_getccb(device);

	if (ccb == NULL)
		errx(1, "mode_select: couldn't allocate CCB");

	CCB_CLEAR_ALL_EXCEPT_HDR(&ccb->csio);

	scsi_mode_select_len(&ccb->csio,
			 /* retries */ retry_count,
			 /* cbfcnp */ NULL,
			 /* tag_action */ task_attr,
			 /* scsi_page_fmt */ 1,
			 /* save_pages */ save_pages,
			 /* param_buf */ data,
			 /* param_len */ datalen,
			 /* minimum_cmd_size */ cdb_len,
			 /* sense_len */ SSD_FULL_SIZE,
			 /* timeout */ timeout ? timeout : 5000);

	if (arglist & CAM_ARG_ERR_RECOVER)
		ccb->ccb_h.flags |= CAM_PASS_ERR_RECOVER;

	/* Disable freezing the device queue */
	ccb->ccb_h.flags |= CAM_DEV_QFRZDIS;

	if (((retval = cam_send_ccb(device, ccb)) < 0)
	 || ((ccb->ccb_h.status & CAM_STATUS_MASK) != CAM_REQ_CMP)) {
		if (arglist & CAM_ARG_VERBOSE) {
			cam_error_print(device, ccb, CAM_ESF_ALL,
					CAM_EPF_ALL, stderr);
		}
		cam_freeccb(ccb);
		cam_close_device(device);

		if (retval < 0)
			err(1, "error sending mode select command");
		else
			errx(1, "error sending mode select command");

	}

	cam_freeccb(ccb);
}
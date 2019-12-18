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
struct scsi_vpd_unit_serial_number {size_t length; int /*<<< orphan*/  serial_num; } ;
struct cam_device {char* device_name; int /*<<< orphan*/  dev_unit_num; } ;

/* Variables and functions */
 int CAM_ARG_ERR_RECOVER ; 
 int CAM_ARG_GET_STDINQ ; 
 int CAM_ARG_GET_XFERRATE ; 
 int CAM_ARG_VERBOSE ; 
 int /*<<< orphan*/  CAM_DEV_QFRZDIS ; 
 int /*<<< orphan*/  CAM_EPF_ALL ; 
 int /*<<< orphan*/  CAM_ESF_ALL ; 
 int /*<<< orphan*/  CAM_PASS_ERR_RECOVER ; 
 int CAM_REQ_CMP ; 
 int CAM_STATUS_MASK ; 
 int /*<<< orphan*/  CCB_CLEAR_ALL_EXCEPT_HDR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSD_FULL_SIZE ; 
 int /*<<< orphan*/  SVPD_SERIAL_NUM_SIZE ; 
 int /*<<< orphan*/  SVPD_UNIT_SERIAL_NUMBER ; 
 int arglist ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  cam_error_print (struct cam_device*,union ccb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_freeccb (union ccb*) ; 
 union ccb* cam_getccb (struct cam_device*) ; 
 scalar_t__ cam_send_ccb (struct cam_device*,union ccb*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  free (struct scsi_vpd_unit_serial_number*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  scsi_inquiry (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  warn (char*) ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static int
scsiserial(struct cam_device *device, int task_attr, int retry_count,
	   int timeout)
{
	union ccb *ccb;
	struct scsi_vpd_unit_serial_number *serial_buf;
	char serial_num[SVPD_SERIAL_NUM_SIZE + 1];
	int error = 0;

	ccb = cam_getccb(device);

	if (ccb == NULL) {
		warnx("couldn't allocate CCB");
		return (1);
	}

	/* cam_getccb cleans up the header, caller has to zero the payload */
	CCB_CLEAR_ALL_EXCEPT_HDR(&ccb->csio);

	serial_buf = (struct scsi_vpd_unit_serial_number *)
		malloc(sizeof(*serial_buf));

	if (serial_buf == NULL) {
		cam_freeccb(ccb);
		warnx("can't malloc memory for serial number");
		return (1);
	}

	scsi_inquiry(&ccb->csio,
		     /*retries*/ retry_count,
		     /*cbfcnp*/ NULL,
		     /* tag_action */ task_attr,
		     /* inq_buf */ (u_int8_t *)serial_buf,
		     /* inq_len */ sizeof(*serial_buf),
		     /* evpd */ 1,
		     /* page_code */ SVPD_UNIT_SERIAL_NUMBER,
		     /* sense_len */ SSD_FULL_SIZE,
		     /* timeout */ timeout ? timeout : 5000);

	/* Disable freezing the device queue */
	ccb->ccb_h.flags |= CAM_DEV_QFRZDIS;

	if (arglist & CAM_ARG_ERR_RECOVER)
		ccb->ccb_h.flags |= CAM_PASS_ERR_RECOVER;

	if (cam_send_ccb(device, ccb) < 0) {
		warn("error sending INQUIRY command");
		cam_freeccb(ccb);
		free(serial_buf);
		return (1);
	}

	if ((ccb->ccb_h.status & CAM_STATUS_MASK) != CAM_REQ_CMP) {
		error = 1;

		if (arglist & CAM_ARG_VERBOSE) {
			cam_error_print(device, ccb, CAM_ESF_ALL,
					CAM_EPF_ALL, stderr);
		}
	}

	cam_freeccb(ccb);

	if (error != 0) {
		free(serial_buf);
		return (error);
	}

	bcopy(serial_buf->serial_num, serial_num, serial_buf->length);
	serial_num[serial_buf->length] = '\0';

	if ((arglist & CAM_ARG_GET_STDINQ)
	 || (arglist & CAM_ARG_GET_XFERRATE))
		fprintf(stdout, "%s%d: Serial Number ",
			device->device_name, device->dev_unit_num);

	fprintf(stdout, "%.60s\n", serial_num);

	free(serial_buf);

	return (0);
}
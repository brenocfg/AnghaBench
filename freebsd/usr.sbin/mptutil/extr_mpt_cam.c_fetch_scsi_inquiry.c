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
struct scsi_inquiry_data {int dummy; } ;
struct mpt_standalone_disk {int dummy; } ;
struct cam_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DEV_QFRZDIS ; 
 int CAM_REQ_CMP ; 
 int CAM_STATUS_MASK ; 
 int /*<<< orphan*/  CCB_CLEAR_ALL_EXCEPT_HDR (int /*<<< orphan*/ *) ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  MSG_SIMPLE_Q_TAG ; 
 int /*<<< orphan*/  SHORT_INQUIRY_LENGTH ; 
 int /*<<< orphan*/  SSD_FULL_SIZE ; 
 struct scsi_inquiry_data* calloc (int,int) ; 
 int /*<<< orphan*/  cam_freeccb (union ccb*) ; 
 union ccb* cam_getccb (struct cam_device*) ; 
 scalar_t__ cam_send_ccb (struct cam_device*,union ccb*) ; 
 int errno ; 
 int /*<<< orphan*/  format_scsi_inquiry (struct mpt_standalone_disk*,struct scsi_inquiry_data*) ; 
 int /*<<< orphan*/  free (struct scsi_inquiry_data*) ; 
 int /*<<< orphan*/  scsi_inquiry (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
fetch_scsi_inquiry(struct cam_device *dev, struct mpt_standalone_disk *disk)
{
	struct scsi_inquiry_data *inq_buf;
	union ccb *ccb;
	int error;

	ccb = cam_getccb(dev);
	if (ccb == NULL)
		return (ENOMEM);

	/* Zero the rest of the ccb. */
	CCB_CLEAR_ALL_EXCEPT_HDR(&ccb->csio);

	inq_buf = calloc(1, sizeof(*inq_buf));
	if (inq_buf == NULL) {
		cam_freeccb(ccb);
		return (ENOMEM);
	}
	scsi_inquiry(&ccb->csio, 1, NULL, MSG_SIMPLE_Q_TAG, (void *)inq_buf,
	    SHORT_INQUIRY_LENGTH, 0, 0, SSD_FULL_SIZE, 5000);

	/* Disable freezing the device queue */
	ccb->ccb_h.flags |= CAM_DEV_QFRZDIS;

	if (cam_send_ccb(dev, ccb) < 0) {
		error = errno;
		free(inq_buf);
		cam_freeccb(ccb);
		return (error);
	}

	if ((ccb->ccb_h.status & CAM_STATUS_MASK) != CAM_REQ_CMP) {
		free(inq_buf);
		cam_freeccb(ccb);
		return (EIO);
	}

	cam_freeccb(ccb);
	format_scsi_inquiry(disk, inq_buf);
	free(inq_buf);
	return (0);
}
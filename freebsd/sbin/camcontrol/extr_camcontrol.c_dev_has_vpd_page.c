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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  int /*<<< orphan*/  sup_pages ;
struct scsi_vpd_supported_page_list {int length; scalar_t__* list; } ;
struct cam_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DEV_QFRZDIS ; 
 int /*<<< orphan*/  CAM_EPF_ALL ; 
 int /*<<< orphan*/  CAM_ESF_ALL ; 
 int /*<<< orphan*/  CAM_PASS_ERR_RECOVER ; 
 int CAM_REQ_CMP ; 
 int CAM_STATUS_MASK ; 
 int /*<<< orphan*/  CCB_CLEAR_ALL_EXCEPT_HDR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MSG_SIMPLE_Q_TAG ; 
 int /*<<< orphan*/  SSD_FULL_SIZE ; 
 int /*<<< orphan*/  SVPD_SUPPORTED_PAGE_LIST ; 
 int /*<<< orphan*/  bzero (struct scsi_vpd_supported_page_list*,int) ; 
 int /*<<< orphan*/  cam_error_print (struct cam_device*,union ccb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_freeccb (union ccb*) ; 
 union ccb* cam_getccb (struct cam_device*) ; 
 scalar_t__ cam_send_ccb (struct cam_device*,union ccb*) ; 
 int /*<<< orphan*/  scsi_inquiry (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  warn (char*) ; 

int
dev_has_vpd_page(struct cam_device *dev, uint8_t page_id, int retry_count,
		 int timeout, int verbosemode)
{
	union ccb *ccb = NULL;
	struct scsi_vpd_supported_page_list sup_pages;
	int i;
	int retval = 0;

	ccb = cam_getccb(dev);
	if (ccb == NULL) {
		warn("Unable to allocate CCB");
		retval = -1;
		goto bailout;
	}

	/* cam_getccb cleans up the header, caller has to zero the payload */
	CCB_CLEAR_ALL_EXCEPT_HDR(&ccb->csio);

	bzero(&sup_pages, sizeof(sup_pages));

	scsi_inquiry(&ccb->csio,
		     /*retries*/ retry_count,
		     /*cbfcnp*/ NULL,
		     /* tag_action */ MSG_SIMPLE_Q_TAG,
		     /* inq_buf */ (u_int8_t *)&sup_pages,
		     /* inq_len */ sizeof(sup_pages),
		     /* evpd */ 1,
		     /* page_code */ SVPD_SUPPORTED_PAGE_LIST,
		     /* sense_len */ SSD_FULL_SIZE,
		     /* timeout */ timeout ? timeout : 5000);

	/* Disable freezing the device queue */
	ccb->ccb_h.flags |= CAM_DEV_QFRZDIS;

	if (retry_count != 0)
		ccb->ccb_h.flags |= CAM_PASS_ERR_RECOVER;

	if (cam_send_ccb(dev, ccb) < 0) {
		cam_freeccb(ccb);
		ccb = NULL;
		retval = -1;
		goto bailout;
	}

	if ((ccb->ccb_h.status & CAM_STATUS_MASK) != CAM_REQ_CMP) {
		if (verbosemode != 0)
			cam_error_print(dev, ccb, CAM_ESF_ALL,
					CAM_EPF_ALL, stderr);
		retval = -1;
		goto bailout;
	}

	for (i = 0; i < sup_pages.length; i++) {
		if (sup_pages.list[i] == page_id) {
			retval = 1;
			goto bailout;
		}
	}
bailout:
	if (ccb != NULL)
		cam_freeccb(ccb);

	return (retval);
}
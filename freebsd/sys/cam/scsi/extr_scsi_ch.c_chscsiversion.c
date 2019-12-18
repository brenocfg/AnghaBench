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
typedef  union ccb {int dummy; } ccb ;
struct scsi_inquiry_data {int version; } ;
struct TYPE_2__ {scalar_t__ status; int /*<<< orphan*/  func_code; } ;
struct ccb_getdev {struct scsi_inquiry_data inq_data; TYPE_1__ ccb_h; } ;
struct cam_periph {int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_PRIORITY_NORMAL ; 
 scalar_t__ CAM_REQ_CMP ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  XPT_GDEV_TYPE ; 
 int /*<<< orphan*/  cam_periph_assert (struct cam_periph*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_action (union ccb*) ; 
 scalar_t__ xpt_alloc_ccb_nowait () ; 
 int /*<<< orphan*/  xpt_free_ccb (union ccb*) ; 
 int /*<<< orphan*/  xpt_setup_ccb (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
chscsiversion(struct cam_periph *periph)
{
	struct scsi_inquiry_data *inq_data;
	struct ccb_getdev *cgd;
	int dev_scsi_version;

	cam_periph_assert(periph, MA_OWNED);
	if ((cgd = (struct ccb_getdev *)xpt_alloc_ccb_nowait()) == NULL)
		return (-1);
	/*
	 * Get the device information.
	 */
	xpt_setup_ccb(&cgd->ccb_h,
		      periph->path,
		      CAM_PRIORITY_NORMAL);
	cgd->ccb_h.func_code = XPT_GDEV_TYPE;
	xpt_action((union ccb *)cgd);

	if (cgd->ccb_h.status != CAM_REQ_CMP) {
		xpt_free_ccb((union ccb *)cgd);
		return -1;
	}

	inq_data = &cgd->inq_data;
	dev_scsi_version = inq_data->version;
	xpt_free_ccb((union ccb *)cgd);

	return dev_scsi_version;
}
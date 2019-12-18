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
struct sbp_dev {scalar_t__ status; int /*<<< orphan*/ * path; scalar_t__ freeze; TYPE_1__* target; } ;
struct TYPE_2__ {int /*<<< orphan*/  sbp; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_LOST_DEVICE ; 
 int /*<<< orphan*/  CAM_DEV_NOT_THERE ; 
 scalar_t__ SBP_DEV_DEAD ; 
 scalar_t__ SBP_DEV_RESET ; 
 int /*<<< orphan*/  SBP_LOCK_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  sbp_abort_all_ocbs (struct sbp_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_async (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xpt_free_path (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xpt_release_devq (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sbp_cam_detach_sdev(struct sbp_dev *sdev)
{
	if (sdev == NULL)
		return;
	if (sdev->status == SBP_DEV_DEAD)
		return;
	if (sdev->status == SBP_DEV_RESET)
		return;
	SBP_LOCK_ASSERT(sdev->target->sbp);
	sbp_abort_all_ocbs(sdev, CAM_DEV_NOT_THERE);
	if (sdev->path) {
		xpt_release_devq(sdev->path,
				 sdev->freeze, TRUE);
		sdev->freeze = 0;
		xpt_async(AC_LOST_DEVICE, sdev->path, NULL);
		xpt_free_path(sdev->path);
		sdev->path = NULL;
	}
}
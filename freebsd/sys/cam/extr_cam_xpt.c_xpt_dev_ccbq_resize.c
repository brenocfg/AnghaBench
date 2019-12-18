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
typedef  int u_int32_t ;
struct cam_path {struct cam_ed* device; } ;
struct cam_ed {int flags; int inq_flags; int tag_saved_openings; TYPE_2__* sim; int /*<<< orphan*/  ccbq; } ;
struct TYPE_4__ {TYPE_1__* devq; } ;
struct TYPE_3__ {int /*<<< orphan*/  send_mtx; } ;

/* Variables and functions */
 int CAM_DEV_TAG_AFTER_COUNT ; 
 int SID_CmdQue ; 
 int cam_ccbq_resize (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

u_int32_t
xpt_dev_ccbq_resize(struct cam_path *path, int newopenings)
{
	int	result;
	struct	cam_ed *dev;

	dev = path->device;
	mtx_lock(&dev->sim->devq->send_mtx);
	result = cam_ccbq_resize(&dev->ccbq, newopenings);
	mtx_unlock(&dev->sim->devq->send_mtx);
	if ((dev->flags & CAM_DEV_TAG_AFTER_COUNT) != 0
	 || (dev->inq_flags & SID_CmdQue) != 0)
		dev->tag_saved_openings = newopenings;
	return (result);
}
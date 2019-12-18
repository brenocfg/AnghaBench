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
typedef  int /*<<< orphan*/  u_int ;
struct cam_path {struct cam_ed* device; } ;
struct cam_ed {TYPE_1__* sim; } ;
struct cam_devq {int /*<<< orphan*/  send_mtx; } ;
struct TYPE_2__ {struct cam_devq* devq; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DEBUG (struct cam_path*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CAM_DEBUG_TRACE ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ xpt_release_devq_device (struct cam_ed*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xpt_run_devq (struct cam_devq*) ; 

void
xpt_release_devq(struct cam_path *path, u_int count, int run_queue)
{
	struct cam_ed *dev;
	struct cam_devq *devq;

	CAM_DEBUG(path, CAM_DEBUG_TRACE, ("xpt_release_devq(%d, %d)\n",
	    count, run_queue));
	dev = path->device;
	devq = dev->sim->devq;
	mtx_lock(&devq->send_mtx);
	if (xpt_release_devq_device(dev, count, run_queue))
		xpt_run_devq(dev->sim->devq);
	mtx_unlock(&devq->send_mtx);
}
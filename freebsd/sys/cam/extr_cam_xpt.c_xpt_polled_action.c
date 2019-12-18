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
struct TYPE_4__ {int timeout; int /*<<< orphan*/  status; TYPE_1__* path; } ;
union ccb {TYPE_2__ ccb_h; } ;
typedef  int uint32_t ;
struct cam_ed {int /*<<< orphan*/  device_mtx; } ;
struct TYPE_3__ {struct cam_ed* device; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_RESRC_UNAVAIL ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xpt_action (union ccb*) ; 
 int xpt_poll_setup (union ccb*) ; 
 int /*<<< orphan*/  xpt_pollwait (union ccb*,int) ; 

void
xpt_polled_action(union ccb *start_ccb)
{
	uint32_t	timeout;
	struct cam_ed	*dev;

	timeout = start_ccb->ccb_h.timeout * 10;
	dev = start_ccb->ccb_h.path->device;

	mtx_unlock(&dev->device_mtx);

	timeout = xpt_poll_setup(start_ccb);
	if (timeout > 0) {
		xpt_action(start_ccb);
		xpt_pollwait(start_ccb, timeout);
	} else {
		start_ccb->ccb_h.status = CAM_RESRC_UNAVAIL;
	}

	mtx_lock(&dev->device_mtx);
}
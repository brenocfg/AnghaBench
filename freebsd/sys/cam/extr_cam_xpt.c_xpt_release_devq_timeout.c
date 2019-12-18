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
struct cam_ed {TYPE_1__* sim; } ;
struct cam_devq {int /*<<< orphan*/  send_mtx; } ;
struct TYPE_2__ {struct cam_devq* devq; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DEBUG_DEV (struct cam_ed*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CAM_DEBUG_TRACE ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ xpt_release_devq_device (struct cam_ed*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_run_devq (struct cam_devq*) ; 

__attribute__((used)) static void
xpt_release_devq_timeout(void *arg)
{
	struct cam_ed *dev;
	struct cam_devq *devq;

	dev = (struct cam_ed *)arg;
	CAM_DEBUG_DEV(dev, CAM_DEBUG_TRACE, ("xpt_release_devq_timeout\n"));
	devq = dev->sim->devq;
	mtx_assert(&devq->send_mtx, MA_OWNED);
	if (xpt_release_devq_device(dev, /*count*/1, /*run_queue*/TRUE))
		xpt_run_devq(devq);
}
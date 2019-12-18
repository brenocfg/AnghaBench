#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
struct TYPE_5__ {scalar_t__ qfrozen_cnt; } ;
struct TYPE_6__ {TYPE_1__ queue; } ;
struct cam_ed {int flags; TYPE_3__* sim; int /*<<< orphan*/  callout; TYPE_2__ ccbq; } ;
struct TYPE_8__ {int /*<<< orphan*/  send_mtx; } ;
struct TYPE_7__ {TYPE_4__* devq; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DEBUG_DEV (struct cam_ed*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CAM_DEBUG_TRACE ; 
 int CAM_DEV_REL_ON_COMPLETE ; 
 int CAM_DEV_REL_TIMEOUT_PENDING ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  xpt_schedule_devq (TYPE_4__*,struct cam_ed*) ; 

__attribute__((used)) static int
xpt_release_devq_device(struct cam_ed *dev, u_int count, int run_queue)
{

	mtx_assert(&dev->sim->devq->send_mtx, MA_OWNED);
	CAM_DEBUG_DEV(dev, CAM_DEBUG_TRACE,
	    ("xpt_release_devq_device(%d, %d) %u->%u\n", count, run_queue,
	    dev->ccbq.queue.qfrozen_cnt, dev->ccbq.queue.qfrozen_cnt - count));
	if (count > dev->ccbq.queue.qfrozen_cnt) {
#ifdef INVARIANTS
		printf("xpt_release_devq(): requested %u > present %u\n",
		    count, dev->ccbq.queue.qfrozen_cnt);
#endif
		count = dev->ccbq.queue.qfrozen_cnt;
	}
	dev->ccbq.queue.qfrozen_cnt -= count;
	if (dev->ccbq.queue.qfrozen_cnt == 0) {
		/*
		 * No longer need to wait for a successful
		 * command completion.
		 */
		dev->flags &= ~CAM_DEV_REL_ON_COMPLETE;
		/*
		 * Remove any timeouts that might be scheduled
		 * to release this queue.
		 */
		if ((dev->flags & CAM_DEV_REL_TIMEOUT_PENDING) != 0) {
			callout_stop(&dev->callout);
			dev->flags &= ~CAM_DEV_REL_TIMEOUT_PENDING;
		}
		/*
		 * Now that we are unfrozen schedule the
		 * device so any pending transactions are
		 * run.
		 */
		xpt_schedule_devq(dev->sim->devq, dev);
	} else
		run_queue = 0;
	return (run_queue);
}
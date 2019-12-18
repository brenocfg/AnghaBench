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
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ u_int ;
struct TYPE_7__ {int /*<<< orphan*/  index; } ;
struct TYPE_5__ {scalar_t__ qfrozen_cnt; } ;
struct TYPE_6__ {TYPE_1__ queue; } ;
struct cam_ed {TYPE_3__ devq_entry; TYPE_2__ ccbq; TYPE_4__* sim; } ;
struct cam_devq {int /*<<< orphan*/  send_queue; int /*<<< orphan*/  send_mtx; } ;
struct TYPE_8__ {struct cam_devq* devq; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DEBUG_DEV (struct cam_ed*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CAM_DEBUG_TRACE ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  camq_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ device_is_queued (struct cam_ed*) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
xpt_freeze_devq_device(struct cam_ed *dev, u_int count)
{
	struct cam_devq	*devq;
	uint32_t freeze;

	devq = dev->sim->devq;
	mtx_assert(&devq->send_mtx, MA_OWNED);
	CAM_DEBUG_DEV(dev, CAM_DEBUG_TRACE,
	    ("xpt_freeze_devq_device(%d) %u->%u\n", count,
	    dev->ccbq.queue.qfrozen_cnt, dev->ccbq.queue.qfrozen_cnt + count));
	freeze = (dev->ccbq.queue.qfrozen_cnt += count);
	/* Remove frozen device from sendq. */
	if (device_is_queued(dev))
		camq_remove(&devq->send_queue, dev->devq_entry.index);
	return (freeze);
}
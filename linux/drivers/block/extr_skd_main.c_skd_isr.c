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
typedef  int u32 ;
struct skd_device {scalar_t__ state; int /*<<< orphan*/  lock; int /*<<< orphan*/  start_queue; int /*<<< orphan*/  completion_worker; TYPE_1__* pdev; } ;
typedef  int irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int FIT_INT_DEF_MASK ; 
 int /*<<< orphan*/  FIT_INT_STATUS_HOST ; 
 int FIT_ISH_COMPLETION_POSTED ; 
 int FIT_ISH_FW_STATE_CHANGE ; 
 int FIT_ISH_MSG_FROM_DEV ; 
 int IRQ_HANDLED ; 
 scalar_t__ SKD_DRVR_STATE_DISAPPEARED ; 
 scalar_t__ SKD_DRVR_STATE_FAULT ; 
 scalar_t__ SKD_DRVR_STATE_LOAD ; 
 scalar_t__ SKD_DRVR_STATE_ONLINE ; 
 scalar_t__ SKD_DRVR_STATE_STOPPING ; 
 int SKD_READL (struct skd_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SKD_WRITEL (struct skd_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skd_isr_comp_limit ; 
 int skd_isr_completion_posted (struct skd_device*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  skd_isr_fwstate (struct skd_device*) ; 
 int /*<<< orphan*/  skd_isr_msg_from_dev (struct skd_device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static irqreturn_t
skd_isr(int irq, void *ptr)
{
	struct skd_device *skdev = ptr;
	u32 intstat;
	u32 ack;
	int rc = 0;
	int deferred = 0;
	int flush_enqueued = 0;

	spin_lock(&skdev->lock);

	for (;; ) {
		intstat = SKD_READL(skdev, FIT_INT_STATUS_HOST);

		ack = FIT_INT_DEF_MASK;
		ack &= intstat;

		dev_dbg(&skdev->pdev->dev, "intstat=0x%x ack=0x%x\n", intstat,
			ack);

		/* As long as there is an int pending on device, keep
		 * running loop.  When none, get out, but if we've never
		 * done any processing, call completion handler?
		 */
		if (ack == 0) {
			/* No interrupts on device, but run the completion
			 * processor anyway?
			 */
			if (rc == 0)
				if (likely (skdev->state
					== SKD_DRVR_STATE_ONLINE))
					deferred = 1;
			break;
		}

		rc = IRQ_HANDLED;

		SKD_WRITEL(skdev, ack, FIT_INT_STATUS_HOST);

		if (likely((skdev->state != SKD_DRVR_STATE_LOAD) &&
			   (skdev->state != SKD_DRVR_STATE_STOPPING))) {
			if (intstat & FIT_ISH_COMPLETION_POSTED) {
				/*
				 * If we have already deferred completion
				 * processing, don't bother running it again
				 */
				if (deferred == 0)
					deferred =
						skd_isr_completion_posted(skdev,
						skd_isr_comp_limit, &flush_enqueued);
			}

			if (intstat & FIT_ISH_FW_STATE_CHANGE) {
				skd_isr_fwstate(skdev);
				if (skdev->state == SKD_DRVR_STATE_FAULT ||
				    skdev->state ==
				    SKD_DRVR_STATE_DISAPPEARED) {
					spin_unlock(&skdev->lock);
					return rc;
				}
			}

			if (intstat & FIT_ISH_MSG_FROM_DEV)
				skd_isr_msg_from_dev(skdev);
		}
	}

	if (unlikely(flush_enqueued))
		schedule_work(&skdev->start_queue);

	if (deferred)
		schedule_work(&skdev->completion_worker);
	else if (!flush_enqueued)
		schedule_work(&skdev->start_queue);

	spin_unlock(&skdev->lock);

	return rc;
}
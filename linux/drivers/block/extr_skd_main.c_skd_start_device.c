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
struct skd_device {int drive_state; int gendisk_on; int /*<<< orphan*/  lock; TYPE_1__* pdev; int /*<<< orphan*/  waitq; int /*<<< orphan*/  start_queue; void* timer_countdown; int /*<<< orphan*/  state; scalar_t__ last_mtd; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIT_CONTROL ; 
 int /*<<< orphan*/  FIT_HW_VERSION ; 
 int /*<<< orphan*/  FIT_INT_DEF_MASK ; 
 int /*<<< orphan*/  FIT_INT_MASK_HOST ; 
 int /*<<< orphan*/  FIT_INT_STATUS_HOST ; 
 int /*<<< orphan*/  FIT_MSG_FROM_DEVICE ; 
#define  FIT_SR_DRIVE_BUSY 136 
#define  FIT_SR_DRIVE_BUSY_ERASE 135 
#define  FIT_SR_DRIVE_BUSY_SANITIZE 134 
#define  FIT_SR_DRIVE_FAULT 133 
#define  FIT_SR_DRIVE_FW_BOOTING 132 
#define  FIT_SR_DRIVE_INIT 131 
#define  FIT_SR_DRIVE_OFFLINE 130 
#define  FIT_SR_DRIVE_ONLINE 129 
#define  FIT_SR_DRIVE_SOFT_RESET 128 
 int FIT_SR_DRIVE_STATE_MASK ; 
 int /*<<< orphan*/  FIT_STATUS ; 
 int /*<<< orphan*/  SKD_DRVR_STATE_BUSY ; 
 int /*<<< orphan*/  SKD_DRVR_STATE_BUSY_ERASE ; 
 int /*<<< orphan*/  SKD_DRVR_STATE_BUSY_SANITIZE ; 
 int /*<<< orphan*/  SKD_DRVR_STATE_STARTING ; 
 int /*<<< orphan*/  SKD_DRVR_STATE_WAIT_BOOT ; 
 int SKD_READL (struct skd_device*,int /*<<< orphan*/ ) ; 
 void* SKD_STARTED_BUSY_TIMO ; 
 void* SKD_STARTING_TIMO ; 
 void* SKD_WAIT_BOOT_TIMO ; 
 int /*<<< orphan*/  SKD_WRITEL (struct skd_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skd_drive_disappeared (struct skd_device*) ; 
 int /*<<< orphan*/  skd_drive_fault (struct skd_device*) ; 
 int /*<<< orphan*/  skd_enable_interrupts (struct skd_device*) ; 
 int /*<<< orphan*/  skd_soft_reset (struct skd_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void skd_start_device(struct skd_device *skdev)
{
	unsigned long flags;
	u32 sense;
	u32 state;

	spin_lock_irqsave(&skdev->lock, flags);

	/* ack all ghost interrupts */
	SKD_WRITEL(skdev, FIT_INT_DEF_MASK, FIT_INT_STATUS_HOST);

	sense = SKD_READL(skdev, FIT_STATUS);

	dev_dbg(&skdev->pdev->dev, "initial status=0x%x\n", sense);

	state = sense & FIT_SR_DRIVE_STATE_MASK;
	skdev->drive_state = state;
	skdev->last_mtd = 0;

	skdev->state = SKD_DRVR_STATE_STARTING;
	skdev->timer_countdown = SKD_STARTING_TIMO;

	skd_enable_interrupts(skdev);

	switch (skdev->drive_state) {
	case FIT_SR_DRIVE_OFFLINE:
		dev_err(&skdev->pdev->dev, "Drive offline...\n");
		break;

	case FIT_SR_DRIVE_FW_BOOTING:
		dev_dbg(&skdev->pdev->dev, "FIT_SR_DRIVE_FW_BOOTING\n");
		skdev->state = SKD_DRVR_STATE_WAIT_BOOT;
		skdev->timer_countdown = SKD_WAIT_BOOT_TIMO;
		break;

	case FIT_SR_DRIVE_BUSY_SANITIZE:
		dev_info(&skdev->pdev->dev, "Start: BUSY_SANITIZE\n");
		skdev->state = SKD_DRVR_STATE_BUSY_SANITIZE;
		skdev->timer_countdown = SKD_STARTED_BUSY_TIMO;
		break;

	case FIT_SR_DRIVE_BUSY_ERASE:
		dev_info(&skdev->pdev->dev, "Start: BUSY_ERASE\n");
		skdev->state = SKD_DRVR_STATE_BUSY_ERASE;
		skdev->timer_countdown = SKD_STARTED_BUSY_TIMO;
		break;

	case FIT_SR_DRIVE_INIT:
	case FIT_SR_DRIVE_ONLINE:
		skd_soft_reset(skdev);
		break;

	case FIT_SR_DRIVE_BUSY:
		dev_err(&skdev->pdev->dev, "Drive Busy...\n");
		skdev->state = SKD_DRVR_STATE_BUSY;
		skdev->timer_countdown = SKD_STARTED_BUSY_TIMO;
		break;

	case FIT_SR_DRIVE_SOFT_RESET:
		dev_err(&skdev->pdev->dev, "drive soft reset in prog\n");
		break;

	case FIT_SR_DRIVE_FAULT:
		/* Fault state is bad...soft reset won't do it...
		 * Hard reset, maybe, but does it work on device?
		 * For now, just fault so the system doesn't hang.
		 */
		skd_drive_fault(skdev);
		/*start the queue so we can respond with error to requests */
		dev_dbg(&skdev->pdev->dev, "starting queue\n");
		schedule_work(&skdev->start_queue);
		skdev->gendisk_on = -1;
		wake_up_interruptible(&skdev->waitq);
		break;

	case 0xFF:
		/* Most likely the device isn't there or isn't responding
		 * to the BAR1 addresses. */
		skd_drive_disappeared(skdev);
		/*start the queue so we can respond with error to requests */
		dev_dbg(&skdev->pdev->dev,
			"starting queue to error-out reqs\n");
		schedule_work(&skdev->start_queue);
		skdev->gendisk_on = -1;
		wake_up_interruptible(&skdev->waitq);
		break;

	default:
		dev_err(&skdev->pdev->dev, "Start: unknown state %x\n",
			skdev->drive_state);
		break;
	}

	state = SKD_READL(skdev, FIT_CONTROL);
	dev_dbg(&skdev->pdev->dev, "FIT Control Status=0x%x\n", state);

	state = SKD_READL(skdev, FIT_INT_STATUS_HOST);
	dev_dbg(&skdev->pdev->dev, "Intr Status=0x%x\n", state);

	state = SKD_READL(skdev, FIT_INT_MASK_HOST);
	dev_dbg(&skdev->pdev->dev, "Intr Mask=0x%x\n", state);

	state = SKD_READL(skdev, FIT_MSG_FROM_DEVICE);
	dev_dbg(&skdev->pdev->dev, "Msg from Dev=0x%x\n", state);

	state = SKD_READL(skdev, FIT_HW_VERSION);
	dev_dbg(&skdev->pdev->dev, "HW version=0x%x\n", state);

	spin_unlock_irqrestore(&skdev->lock, flags);
}
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
typedef  int /*<<< orphan*/  u32 ;
struct skd_device {int /*<<< orphan*/  timer_countdown; int /*<<< orphan*/  state; scalar_t__ last_mtd; int /*<<< orphan*/  drive_state; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIT_INT_DEF_MASK ; 
 int /*<<< orphan*/  FIT_INT_STATUS_HOST ; 
 int /*<<< orphan*/  FIT_SR_DRIVE_STATE_MASK ; 
 int /*<<< orphan*/  FIT_STATUS ; 
 int /*<<< orphan*/  SKD_DRVR_STATE_RESTARTING ; 
 int /*<<< orphan*/  SKD_READL (struct skd_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SKD_RESTARTING_TIMO ; 
 int /*<<< orphan*/  SKD_WRITEL (struct skd_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skd_soft_reset (struct skd_device*) ; 

__attribute__((used)) static void skd_restart_device(struct skd_device *skdev)
{
	u32 state;

	/* ack all ghost interrupts */
	SKD_WRITEL(skdev, FIT_INT_DEF_MASK, FIT_INT_STATUS_HOST);

	state = SKD_READL(skdev, FIT_STATUS);

	dev_dbg(&skdev->pdev->dev, "drive status=0x%x\n", state);

	state &= FIT_SR_DRIVE_STATE_MASK;
	skdev->drive_state = state;
	skdev->last_mtd = 0;

	skdev->state = SKD_DRVR_STATE_RESTARTING;
	skdev->timer_countdown = SKD_RESTARTING_TIMO;

	skd_soft_reset(skdev);
}
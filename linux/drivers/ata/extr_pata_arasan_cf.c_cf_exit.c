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
struct arasan_cf_dev {int /*<<< orphan*/  clk; TYPE_1__* host; scalar_t__ vbase; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int CFHOST_ENB ; 
 scalar_t__ OP_MODE ; 
 int /*<<< orphan*/  TRUE_IDE_IRQS ; 
 int /*<<< orphan*/  cf_card_reset (struct arasan_cf_dev*) ; 
 int /*<<< orphan*/  cf_ginterrupt_enable (struct arasan_cf_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cf_interrupt_enable (struct arasan_cf_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void cf_exit(struct arasan_cf_dev *acdev)
{
	unsigned long flags;

	spin_lock_irqsave(&acdev->host->lock, flags);
	cf_ginterrupt_enable(acdev, 0);
	cf_interrupt_enable(acdev, TRUE_IDE_IRQS, 0);
	cf_card_reset(acdev);
	writel(readl(acdev->vbase + OP_MODE) & ~CFHOST_ENB,
			acdev->vbase + OP_MODE);
	spin_unlock_irqrestore(&acdev->host->lock, flags);
	clk_disable_unprepare(acdev->clk);
}
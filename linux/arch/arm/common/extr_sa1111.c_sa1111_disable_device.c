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
struct sa1111_dev {unsigned int skpcr_mask; int /*<<< orphan*/  devid; } ;
struct sa1111 {TYPE_1__* pdata; int /*<<< orphan*/  lock; scalar_t__ base; } ;
struct TYPE_2__ {int /*<<< orphan*/  data; int /*<<< orphan*/  (* disable ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ SA1111_SKPCR ; 
 unsigned int readl_relaxed (scalar_t__) ; 
 struct sa1111* sa1111_chip_driver (struct sa1111_dev*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_relaxed (unsigned int,scalar_t__) ; 

void sa1111_disable_device(struct sa1111_dev *sadev)
{
	struct sa1111 *sachip = sa1111_chip_driver(sadev);
	unsigned long flags;
	unsigned int val;

	spin_lock_irqsave(&sachip->lock, flags);
	val = readl_relaxed(sachip->base + SA1111_SKPCR);
	writel_relaxed(val & ~sadev->skpcr_mask, sachip->base + SA1111_SKPCR);
	spin_unlock_irqrestore(&sachip->lock, flags);

	if (sachip->pdata && sachip->pdata->disable)
		sachip->pdata->disable(sachip->pdata->data, sadev->devid);
}
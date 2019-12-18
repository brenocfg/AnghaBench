#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct hidma_lldev {int /*<<< orphan*/  lock; scalar_t__ trca; int /*<<< orphan*/  tre_write_offset; } ;

/* Variables and functions */
 scalar_t__ HIDMA_TRCA_DOORBELL_REG ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

void hidma_ll_start(struct hidma_lldev *lldev)
{
	unsigned long irqflags;

	spin_lock_irqsave(&lldev->lock, irqflags);
	writel(lldev->tre_write_offset, lldev->trca + HIDMA_TRCA_DOORBELL_REG);
	spin_unlock_irqrestore(&lldev->lock, irqflags);
}
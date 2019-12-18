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
struct msi_bitmap {int /*<<< orphan*/  lock; int /*<<< orphan*/  bitmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  bitmap_allocate_region (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void msi_bitmap_reserve_hwirq(struct msi_bitmap *bmp, unsigned int hwirq)
{
	unsigned long flags;

	pr_debug("msi_bitmap: reserving hwirq 0x%x\n", hwirq);

	spin_lock_irqsave(&bmp->lock, flags);
	bitmap_allocate_region(bmp->bitmap, hwirq, 0);
	spin_unlock_irqrestore(&bmp->lock, flags);
}
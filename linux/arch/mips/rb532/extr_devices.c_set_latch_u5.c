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
struct TYPE_2__ {unsigned char state; int /*<<< orphan*/  lock; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 TYPE_1__ dev3 ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writeb (unsigned char,int /*<<< orphan*/ ) ; 

void set_latch_u5(unsigned char or_mask, unsigned char nand_mask)
{
	unsigned long flags;

	spin_lock_irqsave(&dev3.lock, flags);

	dev3.state = (dev3.state | or_mask) & ~nand_mask;
	writeb(dev3.state, dev3.base);

	spin_unlock_irqrestore(&dev3.lock, flags);
}
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
typedef  enum bcsr_id { ____Placeholder_bcsr_id } bcsr_id ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  raddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  __raw_writew (unsigned short,int /*<<< orphan*/ ) ; 
 TYPE_1__* bcsr_regs ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wmb () ; 

void bcsr_write(enum bcsr_id reg, unsigned short val)
{
	unsigned long flags;

	spin_lock_irqsave(&bcsr_regs[reg].lock, flags);
	__raw_writew(val, bcsr_regs[reg].raddr);
	wmb();
	spin_unlock_irqrestore(&bcsr_regs[reg].lock, flags);
}
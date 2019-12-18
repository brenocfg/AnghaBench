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
typedef  int u32 ;
struct ccu_common {int /*<<< orphan*/  lock; scalar_t__ reg; scalar_t__ base; } ;

/* Variables and functions */
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

void ccu_gate_helper_disable(struct ccu_common *common, u32 gate)
{
	unsigned long flags;
	u32 reg;

	if (!gate)
		return;

	spin_lock_irqsave(common->lock, flags);

	reg = readl(common->base + common->reg);
	writel(reg & ~gate, common->base + common->reg);

	spin_unlock_irqrestore(common->lock, flags);
}
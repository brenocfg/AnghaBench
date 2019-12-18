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

/* Variables and functions */
 scalar_t__ INTEGRATOR_HDR_CTRL_OFFSET ; 
 scalar_t__ cm_base ; 
 int /*<<< orphan*/  cm_lock ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

void cm_control(u32 mask, u32 set)
{
	unsigned long flags;
	u32 val;

	raw_spin_lock_irqsave(&cm_lock, flags);
	val = readl(cm_base + INTEGRATOR_HDR_CTRL_OFFSET) & ~mask;
	writel(val | set, cm_base + INTEGRATOR_HDR_CTRL_OFFSET);
	raw_spin_unlock_irqrestore(&cm_lock, flags);
}
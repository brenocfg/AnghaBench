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
 int /*<<< orphan*/  config_lock ; 
 int pic32_conf_base ; 
 int readl (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int,int) ; 

__attribute__((used)) static u32 pic32_conf_modify_atomic(u32 offset, u32 mask, u32 set)
{
	u32 v;
	unsigned long flags;

	spin_lock_irqsave(&config_lock, flags);
	v = readl(pic32_conf_base + offset);
	v &= ~mask;
	v |= (set & mask);
	writel(v, pic32_conf_base + offset);
	spin_unlock_irqrestore(&config_lock, flags);

	return 0;
}
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
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clocks_lock ; 
 int local_clk_enable (struct clk*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int clk_enable(struct clk *clk)
{
	int ret;
	unsigned long flags;

	spin_lock_irqsave(&clocks_lock, flags);
	ret = local_clk_enable(clk);
	spin_unlock_irqrestore(&clocks_lock, flags);

	return ret;
}
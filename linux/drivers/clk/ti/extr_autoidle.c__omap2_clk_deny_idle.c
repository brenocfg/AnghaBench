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
struct clk_hw_omap {int autoidle_count; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* deny_idle ) (struct clk_hw_omap*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  autoidle_spinlock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct clk_hw_omap*) ; 

__attribute__((used)) static int _omap2_clk_deny_idle(struct clk_hw_omap *clk)
{
	if (clk->ops && clk->ops->deny_idle) {
		unsigned long irqflags;

		spin_lock_irqsave(&autoidle_spinlock, irqflags);
		clk->autoidle_count++;
		if (clk->autoidle_count == 1)
			clk->ops->deny_idle(clk);

		spin_unlock_irqrestore(&autoidle_spinlock, irqflags);
	}
	return 0;
}
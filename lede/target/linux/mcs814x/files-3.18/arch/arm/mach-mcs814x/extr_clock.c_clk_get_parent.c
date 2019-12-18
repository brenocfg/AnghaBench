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
struct clk {struct clk* parent; TYPE_1__* ops; } ;
struct TYPE_2__ {struct clk* (* get_parent ) (struct clk*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR_OR_NULL (struct clk*) ; 
 int /*<<< orphan*/  clocks_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct clk* stub1 (struct clk*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

struct clk *clk_get_parent(struct clk *clk)
{
	unsigned long flags;

	if (unlikely(IS_ERR_OR_NULL(clk)))
		return NULL;

	if (!clk->ops || !clk->ops->get_parent)
		return clk->parent;

	spin_lock_irqsave(&clocks_lock, flags);
	clk->parent = clk->ops->get_parent(clk);
	spin_unlock_irqrestore(&clocks_lock, flags);

	return clk->parent;
}
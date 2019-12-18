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
struct clk_hw {int dummy; } ;
struct clk_gate {int /*<<< orphan*/  lock; scalar_t__ reg; int /*<<< orphan*/  bit_idx; } ;
struct TYPE_2__ {scalar_t__ (* is_enabled ) (struct clk_hw*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 scalar_t__ RCC_CLR ; 
 TYPE_1__ clk_gate_ops ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ stub1 (struct clk_hw*) ; 
 struct clk_gate* to_clk_gate (struct clk_hw*) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void mp1_gate_clk_disable(struct clk_hw *hw)
{
	struct clk_gate *gate = to_clk_gate(hw);
	unsigned long flags = 0;

	if (clk_gate_ops.is_enabled(hw)) {
		spin_lock_irqsave(gate->lock, flags);
		writel_relaxed(BIT(gate->bit_idx), gate->reg + RCC_CLR);
		spin_unlock_irqrestore(gate->lock, flags);
	}
}
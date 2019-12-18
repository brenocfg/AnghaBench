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
struct clk_pfdv2 {int gate_bit; int /*<<< orphan*/  reg; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int clk_pfdv2_wait (struct clk_pfdv2*) ; 
 int /*<<< orphan*/  pfd_lock ; 
 int readl_relaxed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct clk_pfdv2* to_clk_pfdv2 (struct clk_hw*) ; 
 int /*<<< orphan*/  writel_relaxed (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int clk_pfdv2_enable(struct clk_hw *hw)
{
	struct clk_pfdv2 *pfd = to_clk_pfdv2(hw);
	unsigned long flags;
	u32 val;

	spin_lock_irqsave(&pfd_lock, flags);
	val = readl_relaxed(pfd->reg);
	val &= ~(1 << pfd->gate_bit);
	writel_relaxed(val, pfd->reg);
	spin_unlock_irqrestore(&pfd_lock, flags);

	return clk_pfdv2_wait(pfd);
}
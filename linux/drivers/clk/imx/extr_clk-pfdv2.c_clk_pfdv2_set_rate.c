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
typedef  int u8 ;
typedef  int u64 ;
typedef  int u32 ;
struct clk_pfdv2 {int frac_off; int /*<<< orphan*/  reg; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int CLK_PFDV2_FRAC_MASK ; 
 int /*<<< orphan*/  do_div (int,unsigned long) ; 
 int /*<<< orphan*/  pfd_lock ; 
 int readl_relaxed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct clk_pfdv2* to_clk_pfdv2 (struct clk_hw*) ; 
 int /*<<< orphan*/  writel_relaxed (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int clk_pfdv2_set_rate(struct clk_hw *hw, unsigned long rate,
			      unsigned long parent_rate)
{
	struct clk_pfdv2 *pfd = to_clk_pfdv2(hw);
	unsigned long flags;
	u64 tmp = parent_rate;
	u32 val;
	u8 frac;

	tmp = tmp * 18 + rate / 2;
	do_div(tmp, rate);
	frac = tmp;
	if (frac < 12)
		frac = 12;
	else if (frac > 35)
		frac = 35;

	spin_lock_irqsave(&pfd_lock, flags);
	val = readl_relaxed(pfd->reg);
	val &= ~(CLK_PFDV2_FRAC_MASK << pfd->frac_off);
	val |= frac << pfd->frac_off;
	writel_relaxed(val, pfd->reg);
	spin_unlock_irqrestore(&pfd_lock, flags);

	return 0;
}
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
typedef  scalar_t__ u8 ;
struct clk_hw {int dummy; } ;
struct alchemy_fgcs_clk {int shift; int /*<<< orphan*/  reglock; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 unsigned long alchemy_rdsys (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alchemy_wrsys (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 struct alchemy_fgcs_clk* to_fgcs_clk (struct clk_hw*) ; 

__attribute__((used)) static int alchemy_clk_fgv1_setp(struct clk_hw *hw, u8 index)
{
	struct alchemy_fgcs_clk *c = to_fgcs_clk(hw);
	unsigned long v, flags;

	spin_lock_irqsave(c->reglock, flags);
	v = alchemy_rdsys(c->reg);
	if (index)
		v |= (1 << c->shift);
	else
		v &= ~(1 << c->shift);
	alchemy_wrsys(v, c->reg);
	spin_unlock_irqrestore(c->reglock, flags);

	return 0;
}
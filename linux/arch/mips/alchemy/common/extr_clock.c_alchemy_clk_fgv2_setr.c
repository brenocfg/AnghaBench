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
struct clk_hw {int dummy; } ;
struct alchemy_fgcs_clk {int shift; int /*<<< orphan*/  reglock; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long alchemy_calc_div (unsigned long,unsigned long,int,int,unsigned long*) ; 
 int alchemy_rdsys (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alchemy_wrsys (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 struct alchemy_fgcs_clk* to_fgcs_clk (struct clk_hw*) ; 

__attribute__((used)) static int alchemy_clk_fgv2_setr(struct clk_hw *hw, unsigned long rate,
				 unsigned long parent_rate)
{
	struct alchemy_fgcs_clk *c = to_fgcs_clk(hw);
	int sh = c->shift + 2;
	unsigned long div, v, flags, ret;

	if (!rate || !parent_rate || rate > parent_rate)
		return -EINVAL;

	v = alchemy_rdsys(c->reg) & (1 << 30); /* test "scale" bit */
	ret = alchemy_calc_div(rate, parent_rate, v ? 1 : 2,
			       v ? 256 : 512, &div);

	spin_lock_irqsave(c->reglock, flags);
	v = alchemy_rdsys(c->reg);
	v &= ~(0xff << sh);
	v |= (div & 0xff) << sh;
	alchemy_wrsys(v, c->reg);
	spin_unlock_irqrestore(c->reglock, flags);

	return 0;
}
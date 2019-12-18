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
struct krait_mux_clk {int mask; int shift; int /*<<< orphan*/  offset; scalar_t__ lpl; } ;

/* Variables and functions */
 int LPL_SHIFT ; 
 int /*<<< orphan*/  krait_clock_reg_lock ; 
 int krait_get_l2_indirect_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krait_set_l2_indirect_reg (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void __krait_mux_set_sel(struct krait_mux_clk *mux, int sel)
{
	unsigned long flags;
	u32 regval;

	spin_lock_irqsave(&krait_clock_reg_lock, flags);
	regval = krait_get_l2_indirect_reg(mux->offset);
	regval &= ~(mux->mask << mux->shift);
	regval |= (sel & mux->mask) << mux->shift;
	if (mux->lpl) {
		regval &= ~(mux->mask << (mux->shift + LPL_SHIFT));
		regval |= (sel & mux->mask) << (mux->shift + LPL_SHIFT);
	}
	krait_set_l2_indirect_reg(mux->offset, regval);
	spin_unlock_irqrestore(&krait_clock_reg_lock, flags);

	/* Wait for switch to complete. */
	mb();
	udelay(1);
}
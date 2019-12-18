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
struct clk_aux {TYPE_1__* masks; scalar_t__ lock; int /*<<< orphan*/  reg; } ;
struct TYPE_2__ {unsigned int eq_sel_shift; unsigned int eq_sel_mask; unsigned int eq1_mask; unsigned int xscale_sel_shift; unsigned int xscale_sel_mask; unsigned int yscale_sel_shift; unsigned int yscale_sel_mask; } ;

/* Variables and functions */
 unsigned int readl_relaxed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (scalar_t__,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (scalar_t__,unsigned long) ; 
 struct clk_aux* to_clk_aux (struct clk_hw*) ; 

__attribute__((used)) static unsigned long clk_aux_recalc_rate(struct clk_hw *hw,
		unsigned long parent_rate)
{
	struct clk_aux *aux = to_clk_aux(hw);
	unsigned int num = 1, den = 1, val, eqn;
	unsigned long flags = 0;

	if (aux->lock)
		spin_lock_irqsave(aux->lock, flags);

	val = readl_relaxed(aux->reg);

	if (aux->lock)
		spin_unlock_irqrestore(aux->lock, flags);

	eqn = (val >> aux->masks->eq_sel_shift) & aux->masks->eq_sel_mask;
	if (eqn == aux->masks->eq1_mask)
		den = 2;

	/* calculate numerator */
	num = (val >> aux->masks->xscale_sel_shift) &
		aux->masks->xscale_sel_mask;

	/* calculate denominator */
	den *= (val >> aux->masks->yscale_sel_shift) &
		aux->masks->yscale_sel_mask;

	if (!den)
		return 0;

	return (((parent_rate / 10000) * num) / den) * 10000;
}
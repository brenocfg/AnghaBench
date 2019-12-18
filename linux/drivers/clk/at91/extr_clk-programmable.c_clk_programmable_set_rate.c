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
struct clk_programmable_layout {int pres_mask; int pres_shift; scalar_t__ is_pres_direct; } ;
struct clk_programmable {int /*<<< orphan*/  id; int /*<<< orphan*/  regmap; struct clk_programmable_layout* layout; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_PMC_PCKR (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int fls (unsigned long) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct clk_programmable* to_clk_programmable (struct clk_hw*) ; 

__attribute__((used)) static int clk_programmable_set_rate(struct clk_hw *hw, unsigned long rate,
				     unsigned long parent_rate)
{
	struct clk_programmable *prog = to_clk_programmable(hw);
	const struct clk_programmable_layout *layout = prog->layout;
	unsigned long div = parent_rate / rate;
	int shift = 0;

	if (!div)
		return -EINVAL;

	if (layout->is_pres_direct) {
		shift = div - 1;

		if (shift > layout->pres_mask)
			return -EINVAL;
	} else {
		shift = fls(div) - 1;

		if (div != (1 << shift))
			return -EINVAL;

		if (shift >= layout->pres_mask)
			return -EINVAL;
	}

	regmap_update_bits(prog->regmap, AT91_PMC_PCKR(prog->id),
			   layout->pres_mask << layout->pres_shift,
			   shift << layout->pres_shift);

	return 0;
}
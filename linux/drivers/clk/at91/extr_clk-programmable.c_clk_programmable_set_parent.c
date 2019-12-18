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
typedef  unsigned int u8 ;
struct clk_programmable_layout {unsigned int css_mask; scalar_t__ have_slck_mck; } ;
struct clk_programmable {int /*<<< orphan*/  id; int /*<<< orphan*/  regmap; struct clk_programmable_layout* layout; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 unsigned int AT91_PMC_CSSMCK_MCK ; 
 int /*<<< orphan*/  AT91_PMC_PCKR (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 unsigned int PROG_MAX_RM9200_CSS ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 struct clk_programmable* to_clk_programmable (struct clk_hw*) ; 

__attribute__((used)) static int clk_programmable_set_parent(struct clk_hw *hw, u8 index)
{
	struct clk_programmable *prog = to_clk_programmable(hw);
	const struct clk_programmable_layout *layout = prog->layout;
	unsigned int mask = layout->css_mask;
	unsigned int pckr = index;

	if (layout->have_slck_mck)
		mask |= AT91_PMC_CSSMCK_MCK;

	if (index > layout->css_mask) {
		if (index > PROG_MAX_RM9200_CSS && !layout->have_slck_mck)
			return -EINVAL;

		pckr |= AT91_PMC_CSSMCK_MCK;
	}

	regmap_update_bits(prog->regmap, AT91_PMC_PCKR(prog->id), mask, pckr);

	return 0;
}
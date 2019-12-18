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
struct clk_hw {int dummy; } ;
struct at91sam9x5_clk_smd {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_PMC_SMD ; 
 int /*<<< orphan*/  AT91_PMC_SMDS ; 
 int EINVAL ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct at91sam9x5_clk_smd* to_at91sam9x5_clk_smd (struct clk_hw*) ; 

__attribute__((used)) static int at91sam9x5_clk_smd_set_parent(struct clk_hw *hw, u8 index)
{
	struct at91sam9x5_clk_smd *smd = to_at91sam9x5_clk_smd(hw);

	if (index > 1)
		return -EINVAL;

	regmap_update_bits(smd->regmap, AT91_PMC_SMD, AT91_PMC_SMDS,
			   index ? AT91_PMC_SMDS : 0);

	return 0;
}
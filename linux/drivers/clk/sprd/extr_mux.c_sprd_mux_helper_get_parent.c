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
struct sprd_mux_ssel {unsigned int shift; int width; int* table; } ;
struct sprd_clk_common {int /*<<< orphan*/  hw; int /*<<< orphan*/  reg; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int clk_hw_get_num_parents (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

u8 sprd_mux_helper_get_parent(const struct sprd_clk_common *common,
			      const struct sprd_mux_ssel *mux)
{
	unsigned int reg;
	u8 parent;
	int num_parents;
	int i;

	regmap_read(common->regmap, common->reg, &reg);
	parent = reg >> mux->shift;
	parent &= (1 << mux->width) - 1;

	if (!mux->table)
		return parent;

	num_parents = clk_hw_get_num_parents(&common->hw);

	for (i = 0; i < num_parents - 1; i++)
		if (parent >= mux->table[i] && parent < mux->table[i + 1])
			return i;

	return num_parents - 1;
}
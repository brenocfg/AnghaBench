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
struct mmp_clk_mix {int /*<<< orphan*/  table_size; scalar_t__ table; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _filter_clk_table (struct mmp_clk_mix*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct mmp_clk_mix* to_clk_mix (struct clk_hw*) ; 

__attribute__((used)) static void mmp_clk_mix_init(struct clk_hw *hw)
{
	struct mmp_clk_mix *mix = to_clk_mix(hw);

	if (mix->table)
		_filter_clk_table(mix, mix->table, mix->table_size);
}
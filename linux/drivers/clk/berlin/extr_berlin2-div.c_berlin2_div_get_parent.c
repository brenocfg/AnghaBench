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
typedef  int u32 ;
struct clk_hw {int dummy; } ;
struct berlin2_div_map {int pll_select_shift; scalar_t__ pll_select_offs; int /*<<< orphan*/  pll_switch_shift; scalar_t__ pll_switch_offs; } ;
struct berlin2_div {scalar_t__ lock; scalar_t__ base; struct berlin2_div_map map; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int PLL_SELECT_MASK ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (scalar_t__) ; 
 int /*<<< orphan*/  spin_unlock (scalar_t__) ; 
 struct berlin2_div* to_berlin2_div (struct clk_hw*) ; 

__attribute__((used)) static u8 berlin2_div_get_parent(struct clk_hw *hw)
{
	struct berlin2_div *div = to_berlin2_div(hw);
	struct berlin2_div_map *map = &div->map;
	u32 reg;
	u8 index = 0;

	if (div->lock)
		spin_lock(div->lock);

	/* PLL_SWITCH == 0 is index 0 */
	reg = readl_relaxed(div->base + map->pll_switch_offs);
	reg &= BIT(map->pll_switch_shift);
	if (reg) {
		reg = readl_relaxed(div->base + map->pll_select_offs);
		reg >>= map->pll_select_shift;
		reg &= PLL_SELECT_MASK;
		index = 1 + reg;
	}

	if (div->lock)
		spin_unlock(div->lock);

	return index;
}
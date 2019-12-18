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
struct clk_hw {int dummy; } ;
struct berlin2_div_map {int gate_shift; scalar_t__ gate_offs; } ;
struct berlin2_div {scalar_t__ lock; scalar_t__ base; struct berlin2_div_map map; } ;

/* Variables and functions */
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (scalar_t__) ; 
 int /*<<< orphan*/  spin_unlock (scalar_t__) ; 
 struct berlin2_div* to_berlin2_div (struct clk_hw*) ; 

__attribute__((used)) static int berlin2_div_is_enabled(struct clk_hw *hw)
{
	struct berlin2_div *div = to_berlin2_div(hw);
	struct berlin2_div_map *map = &div->map;
	u32 reg;

	if (div->lock)
		spin_lock(div->lock);

	reg = readl_relaxed(div->base + map->gate_offs);
	reg >>= map->gate_shift;

	if (div->lock)
		spin_unlock(div->lock);

	return (reg & 0x1);
}
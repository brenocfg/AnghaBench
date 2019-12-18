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
struct clk_hw {int /*<<< orphan*/  core; } ;
struct clk_core {struct clk_hw* hw; } ;

/* Variables and functions */
 struct clk_core* clk_core_get_parent_by_index (int /*<<< orphan*/ ,unsigned int) ; 

struct clk_hw *
clk_hw_get_parent_by_index(const struct clk_hw *hw, unsigned int index)
{
	struct clk_core *parent;

	parent = clk_core_get_parent_by_index(hw->core, index);

	return !parent ? NULL : parent->hw;
}
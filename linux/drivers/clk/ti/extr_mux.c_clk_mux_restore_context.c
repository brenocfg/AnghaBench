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
struct clk_omap_mux {int /*<<< orphan*/  saved_parent; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ti_clk_mux_set_parent (struct clk_hw*,int /*<<< orphan*/ ) ; 
 struct clk_omap_mux* to_clk_omap_mux (struct clk_hw*) ; 

__attribute__((used)) static void clk_mux_restore_context(struct clk_hw *hw)
{
	struct clk_omap_mux *mux = to_clk_omap_mux(hw);

	ti_clk_mux_set_parent(hw, mux->saved_parent);
}
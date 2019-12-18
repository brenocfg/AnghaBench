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
struct clk_mux {int dummy; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_hw_unregister (struct clk_hw*) ; 
 int /*<<< orphan*/  kfree (struct clk_mux*) ; 
 struct clk_mux* to_clk_mux (struct clk_hw*) ; 

void clk_hw_unregister_mux(struct clk_hw *hw)
{
	struct clk_mux *mux;

	mux = to_clk_mux(hw);

	clk_hw_unregister(hw);
	kfree(mux);
}
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
struct clk_sama5d4_slow_osc {int prepared; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 struct clk_sama5d4_slow_osc* to_clk_sama5d4_slow_osc (struct clk_hw*) ; 

__attribute__((used)) static int clk_sama5d4_slow_osc_is_prepared(struct clk_hw *hw)
{
	struct clk_sama5d4_slow_osc *osc = to_clk_sama5d4_slow_osc(hw);

	return osc->prepared;
}
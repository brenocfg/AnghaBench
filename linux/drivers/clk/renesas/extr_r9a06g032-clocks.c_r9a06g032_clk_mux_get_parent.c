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
typedef  int /*<<< orphan*/  u8 ;
struct r9a06g032_clk_bitsel {int /*<<< orphan*/  selector; int /*<<< orphan*/  clocks; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_rdesc_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct r9a06g032_clk_bitsel* to_clk_bitselect (struct clk_hw*) ; 

__attribute__((used)) static u8 r9a06g032_clk_mux_get_parent(struct clk_hw *hw)
{
	struct r9a06g032_clk_bitsel *set = to_clk_bitselect(hw);

	return clk_rdesc_get(set->clocks, set->selector);
}
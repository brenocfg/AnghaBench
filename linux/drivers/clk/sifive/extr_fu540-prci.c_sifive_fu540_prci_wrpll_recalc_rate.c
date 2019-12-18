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
struct clk_hw {int dummy; } ;
struct __prci_wrpll_data {int /*<<< orphan*/  c; } ;
struct __prci_clock {struct __prci_wrpll_data* pwd; } ;

/* Variables and functions */
 struct __prci_clock* clk_hw_to_prci_clock (struct clk_hw*) ; 
 unsigned long wrpll_calc_output_rate (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static unsigned long sifive_fu540_prci_wrpll_recalc_rate(struct clk_hw *hw,
							 unsigned long parent_rate)
{
	struct __prci_clock *pc = clk_hw_to_prci_clock(hw);
	struct __prci_wrpll_data *pwd = pc->pwd;

	return wrpll_calc_output_rate(&pwd->c, parent_rate);
}
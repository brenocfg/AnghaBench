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
struct ti_adpll_dco_data {int dummy; } ;
struct ti_adpll_data {int dummy; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int ti_adpll_is_locked (struct ti_adpll_data*) ; 
 struct ti_adpll_data* to_adpll (struct ti_adpll_dco_data*) ; 
 struct ti_adpll_dco_data* to_dco (struct clk_hw*) ; 

__attribute__((used)) static int ti_adpll_is_prepared(struct clk_hw *hw)
{
	struct ti_adpll_dco_data *dco = to_dco(hw);
	struct ti_adpll_data *d = to_adpll(dco);

	return ti_adpll_is_locked(d);
}
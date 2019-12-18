#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct clk_hw {int dummy; } ;
struct TYPE_2__ {unsigned long (* recalc_rate ) (struct clk_hw*,unsigned long) ;} ;

/* Variables and functions */
 unsigned long stub1 (struct clk_hw*,unsigned long) ; 
 TYPE_1__ ti_clk_divider_ops ; 

__attribute__((used)) static unsigned long ti_composite_recalc_rate(struct clk_hw *hw,
					      unsigned long parent_rate)
{
	return ti_clk_divider_ops.recalc_rate(hw, parent_rate);
}
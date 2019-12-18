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
struct pic32_ref_osc {scalar_t__ ctrl_reg; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int REFO_DIV_MASK ; 
 int REFO_DIV_SHIFT ; 
 int REFO_TRIM_MASK ; 
 scalar_t__ REFO_TRIM_REG ; 
 int REFO_TRIM_SHIFT ; 
 struct pic32_ref_osc* clkhw_to_refosc (struct clk_hw*) ; 
 int readl (scalar_t__) ; 
 unsigned long roclk_calc_rate (unsigned long,int,int) ; 

__attribute__((used)) static unsigned long roclk_recalc_rate(struct clk_hw *hw,
				       unsigned long parent_rate)
{
	struct pic32_ref_osc *refo = clkhw_to_refosc(hw);
	u32 v, rodiv, rotrim;

	/* get rodiv */
	v = readl(refo->ctrl_reg);
	rodiv = (v >> REFO_DIV_SHIFT) & REFO_DIV_MASK;

	/* get trim */
	v = readl(refo->ctrl_reg + REFO_TRIM_REG);
	rotrim = (v >> REFO_TRIM_SHIFT) & REFO_TRIM_MASK;

	return roclk_calc_rate(parent_rate, rodiv, rotrim);
}
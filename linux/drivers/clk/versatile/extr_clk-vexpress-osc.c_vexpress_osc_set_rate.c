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
struct vexpress_osc {int /*<<< orphan*/  reg; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 struct vexpress_osc* to_vexpress_osc (struct clk_hw*) ; 

__attribute__((used)) static int vexpress_osc_set_rate(struct clk_hw *hw, unsigned long rate,
		unsigned long parent_rate)
{
	struct vexpress_osc *osc = to_vexpress_osc(hw);

	return regmap_write(osc->reg, 0, rate);
}
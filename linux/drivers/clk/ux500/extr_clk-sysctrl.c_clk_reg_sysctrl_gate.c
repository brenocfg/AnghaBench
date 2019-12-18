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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct device {int dummy; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 struct clk* clk_reg_sysctrl (struct device*,char const*,char const**,int,int /*<<< orphan*/ *,int*,int*,int /*<<< orphan*/ ,unsigned long,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_sysctrl_gate_ops ; 

struct clk *clk_reg_sysctrl_gate(struct device *dev,
				const char *name,
				const char *parent_name,
				u16 reg_sel,
				u8 reg_mask,
				u8 reg_bits,
				unsigned long enable_delay_us,
				unsigned long flags)
{
	const char **parent_names = (parent_name ? &parent_name : NULL);
	u8 num_parents = (parent_name ? 1 : 0);

	return clk_reg_sysctrl(dev, name, parent_names, num_parents,
			&reg_sel, &reg_mask, &reg_bits, 0, enable_delay_us,
			flags, &clk_sysctrl_gate_ops);
}
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
struct device {int dummy; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 struct clk_hw* __clk_hw_register_fixed_factor (struct device*,int /*<<< orphan*/ *,char const*,char const*,int,unsigned long,unsigned int,unsigned int) ; 

struct clk_hw *clk_hw_register_fixed_factor(struct device *dev,
		const char *name, const char *parent_name, unsigned long flags,
		unsigned int mult, unsigned int div)
{
	return __clk_hw_register_fixed_factor(dev, NULL, name, parent_name, -1,
					      flags, mult, div);
}
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
struct clk {int dummy; } ;

/* Variables and functions */
 struct clk* __clk_register (struct device*,int /*<<< orphan*/ ,struct clk_hw*) ; 
 int /*<<< orphan*/  dev_of_node (struct device*) ; 

struct clk *clk_register(struct device *dev, struct clk_hw *hw)
{
	return __clk_register(dev, dev_of_node(dev), hw);
}
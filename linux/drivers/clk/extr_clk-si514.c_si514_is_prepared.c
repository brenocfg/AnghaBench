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
struct clk_si514 {int /*<<< orphan*/  regmap; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 unsigned int SI514_CONTROL_OE ; 
 int /*<<< orphan*/  SI514_REG_CONTROL ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 struct clk_si514* to_clk_si514 (struct clk_hw*) ; 

__attribute__((used)) static int si514_is_prepared(struct clk_hw *hw)
{
	struct clk_si514 *data = to_clk_si514(hw);
	unsigned int val;
	int err;

	err = regmap_read(data->regmap, SI514_REG_CONTROL, &val);
	if (err < 0)
		return err;

	return !!(val & SI514_CONTROL_OE);
}
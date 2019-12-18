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
struct clk_si544 {int /*<<< orphan*/  regmap; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 unsigned int SI544_OE_STATE_ODC_OE ; 
 int /*<<< orphan*/  SI544_REG_OE_STATE ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 struct clk_si544* to_clk_si544 (struct clk_hw*) ; 

__attribute__((used)) static int si544_is_prepared(struct clk_hw *hw)
{
	struct clk_si544 *data = to_clk_si544(hw);
	unsigned int val;
	int err;

	err = regmap_read(data->regmap, SI544_REG_OE_STATE, &val);
	if (err < 0)
		return err;

	return !!(val & SI544_OE_STATE_ODC_OE);
}
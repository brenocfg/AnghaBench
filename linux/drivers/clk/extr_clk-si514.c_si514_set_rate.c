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
struct clk_si514_muldiv {int dummy; } ;
struct clk_si514 {int /*<<< orphan*/  regmap; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SI514_CONTROL_FCAL ; 
 unsigned int SI514_CONTROL_OE ; 
 int /*<<< orphan*/  SI514_REG_CONTROL ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int si514_calc_muldiv (struct clk_si514_muldiv*,unsigned long) ; 
 int /*<<< orphan*/  si514_enable_output (struct clk_si514*,int) ; 
 int si514_set_muldiv (struct clk_si514*,struct clk_si514_muldiv*) ; 
 struct clk_si514* to_clk_si514 (struct clk_hw*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int si514_set_rate(struct clk_hw *hw, unsigned long rate,
		unsigned long parent_rate)
{
	struct clk_si514 *data = to_clk_si514(hw);
	struct clk_si514_muldiv settings;
	unsigned int old_oe_state;
	int err;

	err = si514_calc_muldiv(&settings, rate);
	if (err)
		return err;

	err = regmap_read(data->regmap, SI514_REG_CONTROL, &old_oe_state);
	if (err)
		return err;

	si514_enable_output(data, false);

	err = si514_set_muldiv(data, &settings);
	if (err < 0)
		return err; /* Undefined state now, best to leave disabled */

	/* Trigger calibration */
	err = regmap_write(data->regmap, SI514_REG_CONTROL, SI514_CONTROL_FCAL);
	if (err < 0)
		return err;

	/* Applying a new frequency can take up to 10ms */
	usleep_range(10000, 12000);

	if (old_oe_state & SI514_CONTROL_OE)
		si514_enable_output(data, true);

	return err;
}
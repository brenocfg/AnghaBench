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
struct clk_si544_muldiv {int /*<<< orphan*/  delta_m; } ;
struct clk_si544 {int /*<<< orphan*/  regmap; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SI544_CONTROL_MS_ICAL2 ; 
 unsigned int SI544_OE_STATE_ODC_OE ; 
 int /*<<< orphan*/  SI544_REG_CONTROL ; 
 int /*<<< orphan*/  SI544_REG_FCAL_OVR ; 
 int /*<<< orphan*/  SI544_REG_OE_STATE ; 
 long abs (long) ; 
 int /*<<< orphan*/  is_valid_frequency (struct clk_si544*,unsigned long) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long si544_calc_center_rate (struct clk_si544_muldiv*) ; 
 int /*<<< orphan*/  si544_calc_delta (long,long) ; 
 int si544_calc_muldiv (struct clk_si544_muldiv*,unsigned long) ; 
 int /*<<< orphan*/  si544_enable_output (struct clk_si544*,int) ; 
 int si544_get_muldiv (struct clk_si544*,struct clk_si544_muldiv*) ; 
 long si544_max_delta (unsigned long) ; 
 int si544_set_delta_m (struct clk_si544*,int /*<<< orphan*/ ) ; 
 int si544_set_muldiv (struct clk_si544*,struct clk_si544_muldiv*) ; 
 struct clk_si544* to_clk_si544 (struct clk_hw*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int si544_set_rate(struct clk_hw *hw, unsigned long rate,
		unsigned long parent_rate)
{
	struct clk_si544 *data = to_clk_si544(hw);
	struct clk_si544_muldiv settings;
	unsigned long center;
	long max_delta;
	long delta;
	unsigned int old_oe_state;
	int err;

	if (!is_valid_frequency(data, rate))
		return -EINVAL;

	/* Try using the frequency adjustment feature for a <= 950ppm change */
	err = si544_get_muldiv(data, &settings);
	if (err)
		return err;

	center = si544_calc_center_rate(&settings);
	max_delta = si544_max_delta(center);
	delta = rate - center;

	if (abs(delta) <= max_delta)
		return si544_set_delta_m(data,
					 si544_calc_delta(delta, max_delta));

	/* Too big for the delta adjustment, need to reprogram */
	err = si544_calc_muldiv(&settings, rate);
	if (err)
		return err;

	err = regmap_read(data->regmap, SI544_REG_OE_STATE, &old_oe_state);
	if (err)
		return err;

	si544_enable_output(data, false);

	/* Allow FCAL for this frequency update */
	err = regmap_write(data->regmap, SI544_REG_FCAL_OVR, 0);
	if (err < 0)
		return err;

	err = si544_set_delta_m(data, settings.delta_m);
	if (err < 0)
		return err;

	err = si544_set_muldiv(data, &settings);
	if (err < 0)
		return err; /* Undefined state now, best to leave disabled */

	/* Trigger calibration */
	err = regmap_write(data->regmap, SI544_REG_CONTROL,
			   SI544_CONTROL_MS_ICAL2);
	if (err < 0)
		return err;

	/* Applying a new frequency can take up to 10ms */
	usleep_range(10000, 12000);

	if (old_oe_state & SI544_OE_STATE_ODC_OE)
		si544_enable_output(data, true);

	return err;
}
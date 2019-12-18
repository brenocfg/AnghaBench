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
typedef  int u8 ;
typedef  int u32 ;
struct clk_si5341_output {TYPE_1__* data; } ;
struct clk_hw {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int SI5341_OUT_CFG_RDIV_FORCE2 ; 
 int /*<<< orphan*/  SI5341_OUT_CONFIG (struct clk_si5341_output*) ; 
 int /*<<< orphan*/  SI5341_OUT_R_REG (struct clk_si5341_output*) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 struct clk_si5341_output* to_clk_si5341_output (struct clk_hw*) ; 

__attribute__((used)) static unsigned long si5341_output_clk_recalc_rate(struct clk_hw *hw,
		unsigned long parent_rate)
{
	struct clk_si5341_output *output = to_clk_si5341_output(hw);
	int err;
	u32 val;
	u32 r_divider;
	u8 r[3];

	err = regmap_bulk_read(output->data->regmap,
			SI5341_OUT_R_REG(output), r, 3);
	if (err < 0)
		return err;

	/* Calculate value as 24-bit integer*/
	r_divider = r[2] << 16 | r[1] << 8 | r[0];

	/* If Rx_REG is zero, the divider is disabled, so return a "0" rate */
	if (!r_divider)
		return 0;

	/* Divider is 2*(Rx_REG+1) */
	r_divider += 1;
	r_divider <<= 1;

	err = regmap_read(output->data->regmap,
			SI5341_OUT_CONFIG(output), &val);
	if (err < 0)
		return err;

	if (val & SI5341_OUT_CFG_RDIV_FORCE2)
		r_divider = 2;

	return parent_rate / r_divider;
}
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
typedef  int /*<<< orphan*/  u8 ;
struct si5351_driver_data {int /*<<< orphan*/  variant; } ;
typedef  enum si5351_clkout_src { ____Placeholder_si5351_clkout_src } si5351_clkout_src ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ SI5351_CLK0_CTRL ; 
#define  SI5351_CLKOUT_SRC_CLKIN 131 
#define  SI5351_CLKOUT_SRC_MSYNTH_0_4 130 
#define  SI5351_CLKOUT_SRC_MSYNTH_N 129 
#define  SI5351_CLKOUT_SRC_XTAL 128 
 int /*<<< orphan*/  SI5351_CLK_INPUT_CLKIN ; 
 int /*<<< orphan*/  SI5351_CLK_INPUT_MASK ; 
 int /*<<< orphan*/  SI5351_CLK_INPUT_MULTISYNTH_0_4 ; 
 int /*<<< orphan*/  SI5351_CLK_INPUT_MULTISYNTH_N ; 
 int /*<<< orphan*/  SI5351_CLK_INPUT_XTAL ; 
 int /*<<< orphan*/  SI5351_VARIANT_C ; 
 int /*<<< orphan*/  si5351_set_bits (struct si5351_driver_data*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _si5351_clkout_reparent(struct si5351_driver_data *drvdata,
				   int num, enum si5351_clkout_src parent)
{
	u8 val;

	if (num > 8)
		return -EINVAL;

	switch (parent) {
	case SI5351_CLKOUT_SRC_MSYNTH_N:
		val = SI5351_CLK_INPUT_MULTISYNTH_N;
		break;
	case SI5351_CLKOUT_SRC_MSYNTH_0_4:
		/* clk0/clk4 can only connect to its own multisync */
		if (num == 0 || num == 4)
			val = SI5351_CLK_INPUT_MULTISYNTH_N;
		else
			val = SI5351_CLK_INPUT_MULTISYNTH_0_4;
		break;
	case SI5351_CLKOUT_SRC_XTAL:
		val = SI5351_CLK_INPUT_XTAL;
		break;
	case SI5351_CLKOUT_SRC_CLKIN:
		if (drvdata->variant != SI5351_VARIANT_C)
			return -EINVAL;

		val = SI5351_CLK_INPUT_CLKIN;
		break;
	default:
		return 0;
	}

	si5351_set_bits(drvdata, SI5351_CLK0_CTRL + num,
			SI5351_CLK_INPUT_MASK, val);
	return 0;
}
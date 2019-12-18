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
typedef  int u32 ;
struct clk_si5341_output {TYPE_1__* data; } ;
struct clk_hw {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int SI5341_OUT_CFG_OE ; 
 int /*<<< orphan*/  SI5341_OUT_CONFIG (struct clk_si5341_output*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 struct clk_si5341_output* to_clk_si5341_output (struct clk_hw*) ; 

__attribute__((used)) static int si5341_output_clk_is_on(struct clk_hw *hw)
{
	struct clk_si5341_output *output = to_clk_si5341_output(hw);
	int err;
	u32 val;

	err = regmap_read(output->data->regmap,
			SI5341_OUT_CONFIG(output), &val);
	if (err < 0)
		return err;

	/* Bit 0=PDN, 1=OE so only a value of 0x2 enables the output */
	return (val & 0x03) == SI5341_OUT_CFG_OE;
}
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
struct clk_si5341_output {TYPE_1__* data; } ;
struct clk_hw {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  SI5341_OUT_CFG_OE ; 
 int /*<<< orphan*/  SI5341_OUT_CFG_PDN ; 
 int /*<<< orphan*/  SI5341_OUT_CONFIG (struct clk_si5341_output*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct clk_si5341_output* to_clk_si5341_output (struct clk_hw*) ; 

__attribute__((used)) static void si5341_output_clk_unprepare(struct clk_hw *hw)
{
	struct clk_si5341_output *output = to_clk_si5341_output(hw);

	regmap_update_bits(output->data->regmap,
			SI5341_OUT_CONFIG(output),
			SI5341_OUT_CFG_OE, 0);
	regmap_update_bits(output->data->regmap,
			SI5341_OUT_CONFIG(output),
			SI5341_OUT_CFG_PDN, SI5341_OUT_CFG_PDN);
}
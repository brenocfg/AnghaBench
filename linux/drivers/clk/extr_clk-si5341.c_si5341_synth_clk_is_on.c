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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct clk_si5341_synth {TYPE_1__* data; int /*<<< orphan*/  index; } ;
struct clk_hw {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SI5341_SYNTH_N_CLK_DIS ; 
 int /*<<< orphan*/  SI5341_SYNTH_N_CLK_TO_OUTX_EN ; 
 int /*<<< orphan*/  SI5341_SYNTH_N_PDNB ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 struct clk_si5341_synth* to_clk_si5341_synth (struct clk_hw*) ; 

__attribute__((used)) static int si5341_synth_clk_is_on(struct clk_hw *hw)
{
	struct clk_si5341_synth *synth = to_clk_si5341_synth(hw);
	int err;
	u32 val;
	u8 index = synth->index;

	err = regmap_read(synth->data->regmap,
			SI5341_SYNTH_N_CLK_TO_OUTX_EN, &val);
	if (err < 0)
		return 0;

	if (!(val & BIT(index)))
		return 0;

	err = regmap_read(synth->data->regmap, SI5341_SYNTH_N_PDNB, &val);
	if (err < 0)
		return 0;

	if (!(val & BIT(index)))
		return 0;

	/* This bit must be 0 for the synthesizer to receive clock input */
	err = regmap_read(synth->data->regmap, SI5341_SYNTH_N_CLK_DIS, &val);
	if (err < 0)
		return 0;

	return !(val & BIT(index));
}
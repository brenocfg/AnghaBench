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
typedef  size_t u8 ;
struct clk_si5341 {size_t num_synth; size_t num_outputs; int /*<<< orphan*/ * reg_rdiv_offset; int /*<<< orphan*/  regmap; int /*<<< orphan*/ * reg_output_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  SI5341_PLL_M_NUM ; 
 int /*<<< orphan*/  SI5341_SYNTH_N_CLK_DIS ; 
 int /*<<< orphan*/  SI5341_SYNTH_N_CLK_TO_OUTX_EN ; 
 int /*<<< orphan*/  SI5341_SYNTH_N_NUM (size_t) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*,int) ; 

__attribute__((used)) static int si5341_read_settings(struct clk_si5341 *data)
{
	int err;
	u8 i;
	u8 r[10];

	err = regmap_bulk_read(data->regmap, SI5341_PLL_M_NUM, r, 10);
	if (err < 0)
		return err;

	err = regmap_bulk_read(data->regmap,
				SI5341_SYNTH_N_CLK_TO_OUTX_EN, r, 3);
	if (err < 0)
		return err;

	err = regmap_bulk_read(data->regmap,
				SI5341_SYNTH_N_CLK_DIS, r, 1);
	if (err < 0)
		return err;

	for (i = 0; i < data->num_synth; ++i) {
		err = regmap_bulk_read(data->regmap,
					SI5341_SYNTH_N_NUM(i), r, 10);
		if (err < 0)
			return err;
	}

	for (i = 0; i < data->num_outputs; ++i) {
		err = regmap_bulk_read(data->regmap,
					data->reg_output_offset[i], r, 4);
		if (err < 0)
			return err;

		err = regmap_bulk_read(data->regmap,
					data->reg_rdiv_offset[i], r, 3);
		if (err < 0)
			return err;
	}

	return 0;
}
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
typedef  int u8 ;
struct clk_si544_muldiv {int ls_div_bits; int hs_div; int fb_div_int; int fb_div_frac; int delta_m; } ;
struct clk_si544 {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  SI544_REG_ADPLL_DELTA_M0 ; 
 int /*<<< orphan*/  SI544_REG_FBDIV0 ; 
 int /*<<< orphan*/  SI544_REG_HS_DIV ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int si544_get_muldiv(struct clk_si544 *data,
	struct clk_si544_muldiv *settings)
{
	int err;
	u8 reg[6];

	err = regmap_bulk_read(data->regmap, SI544_REG_HS_DIV, reg, 2);
	if (err)
		return err;

	settings->ls_div_bits = (reg[1] >> 4) & 0x07;
	settings->hs_div = (reg[1] & 0x07) << 8 | reg[0];

	err = regmap_bulk_read(data->regmap, SI544_REG_FBDIV0, reg, 6);
	if (err)
		return err;

	settings->fb_div_int = reg[4] | (reg[5] & 0x07) << 8;
	settings->fb_div_frac = reg[0] | reg[1] << 8 | reg[2] << 16 |
				reg[3] << 24;

	err = regmap_bulk_read(data->regmap, SI544_REG_ADPLL_DELTA_M0, reg, 3);
	if (err)
		return err;

	/* Interpret as 24-bit signed number */
	settings->delta_m = reg[0] << 8 | reg[1] << 16 | reg[2] << 24;
	settings->delta_m >>= 8;

	return 0;
}
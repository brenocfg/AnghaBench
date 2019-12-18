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
struct clk_si514_muldiv {int m_frac; int m_int; int ls_div_bits; int hs_div; } ;
struct clk_si514 {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  SI514_REG_M_FRAC1 ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int si514_get_muldiv(struct clk_si514 *data,
	struct clk_si514_muldiv *settings)
{
	int err;
	u8 reg[7];

	err = regmap_bulk_read(data->regmap, SI514_REG_M_FRAC1,
			reg, ARRAY_SIZE(reg));
	if (err)
		return err;

	settings->m_frac = reg[0] | reg[1] << 8 | reg[2] << 16 |
			   (reg[3] & 0x1F) << 24;
	settings->m_int = (reg[4] & 0x3f) << 3 | reg[3] >> 5;
	settings->ls_div_bits = (reg[6] >> 4) & 0x07;
	settings->hs_div = (reg[6] & 0x03) << 8 | reg[5];
	return 0;
}
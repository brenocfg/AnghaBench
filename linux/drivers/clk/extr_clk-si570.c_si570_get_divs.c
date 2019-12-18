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
typedef  int u64 ;
struct clk_si570 {scalar_t__ div_offset; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int*) ; 
 int HS_DIV_MASK ; 
 int HS_DIV_OFFSET ; 
 int HS_DIV_SHIFT ; 
 int N1_1_0_MASK ; 
 int N1_6_2_MASK ; 
 int RFREQ_37_32_MASK ; 
 scalar_t__ SI570_REG_HS_N1 ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,scalar_t__,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int si570_get_divs(struct clk_si570 *data, u64 *rfreq,
		unsigned int *n1, unsigned int *hs_div)
{
	int err;
	u8 reg[6];
	u64 tmp;

	err = regmap_bulk_read(data->regmap, SI570_REG_HS_N1 + data->div_offset,
			reg, ARRAY_SIZE(reg));
	if (err)
		return err;

	*hs_div = ((reg[0] & HS_DIV_MASK) >> HS_DIV_SHIFT) + HS_DIV_OFFSET;
	*n1 = ((reg[0] & N1_6_2_MASK) << 2) + ((reg[1] & N1_1_0_MASK) >> 6) + 1;
	/* Handle invalid cases */
	if (*n1 > 1)
		*n1 &= ~1;

	tmp = reg[1] & RFREQ_37_32_MASK;
	tmp = (tmp << 8) + reg[2];
	tmp = (tmp << 8) + reg[3];
	tmp = (tmp << 8) + reg[4];
	tmp = (tmp << 8) + reg[5];
	*rfreq = tmp;

	return 0;
}
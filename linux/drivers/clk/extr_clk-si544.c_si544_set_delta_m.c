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
struct clk_si544 {int /*<<< orphan*/  regmap; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  SI544_REG_ADPLL_DELTA_M0 ; 
 int regmap_bulk_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int si544_set_delta_m(struct clk_si544 *data, s32 delta_m)
{
	u8 reg[3];

	reg[0] = delta_m;
	reg[1] = delta_m >> 8;
	reg[2] = delta_m >> 16;

	return regmap_bulk_write(data->regmap, SI544_REG_ADPLL_DELTA_M0,
				 reg, 3);
}
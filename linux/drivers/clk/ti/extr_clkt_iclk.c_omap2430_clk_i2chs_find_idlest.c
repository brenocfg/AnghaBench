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
struct clk_omap_reg {int offset; } ;
struct clk_hw_omap {int /*<<< orphan*/  enable_bit; int /*<<< orphan*/  enable_reg; } ;

/* Variables and functions */
 int CM_IDLEST ; 
 int OMAP24XX_CM_FCLKEN2 ; 
 int /*<<< orphan*/  OMAP24XX_CM_IDLEST_VAL ; 
 int /*<<< orphan*/  memcpy (struct clk_omap_reg*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void omap2430_clk_i2chs_find_idlest(struct clk_hw_omap *clk,
					   struct clk_omap_reg *idlest_reg,
					   u8 *idlest_bit,
					   u8 *idlest_val)
{
	memcpy(idlest_reg, &clk->enable_reg, sizeof(*idlest_reg));
	idlest_reg->offset ^= (OMAP24XX_CM_FCLKEN2 ^ CM_IDLEST);
	*idlest_bit = clk->enable_bit;
	*idlest_val = OMAP24XX_CM_IDLEST_VAL;
}
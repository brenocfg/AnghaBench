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
typedef  scalar_t__ u8 ;
struct clk_omap_reg {int dummy; } ;
struct clk_hw_omap {int enable_bit; int /*<<< orphan*/  enable_reg; } ;

/* Variables and functions */
 scalar_t__ AM35XX_IPSS_ICK_FCK_OFFSET ; 
 int AM35XX_IPSS_ICK_MASK ; 
 int /*<<< orphan*/  memcpy (struct clk_omap_reg*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void am35xx_clk_find_companion(struct clk_hw_omap *clk,
				      struct clk_omap_reg *other_reg,
				      u8 *other_bit)
{
	memcpy(other_reg, &clk->enable_reg, sizeof(*other_reg));
	if (clk->enable_bit & AM35XX_IPSS_ICK_MASK)
		*other_bit = clk->enable_bit + AM35XX_IPSS_ICK_FCK_OFFSET;
	else
	*other_bit = clk->enable_bit - AM35XX_IPSS_ICK_FCK_OFFSET;
}
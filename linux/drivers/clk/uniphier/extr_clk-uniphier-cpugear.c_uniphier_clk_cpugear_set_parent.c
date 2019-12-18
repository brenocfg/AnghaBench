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
typedef  unsigned int u8 ;
struct uniphier_clk_cpugear {unsigned int mask; scalar_t__ regbase; int /*<<< orphan*/  regmap; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ UNIPHIER_CLK_CPUGEAR_SET ; 
 scalar_t__ UNIPHIER_CLK_CPUGEAR_UPD ; 
 unsigned int UNIPHIER_CLK_CPUGEAR_UPD_BIT ; 
 int regmap_read_poll_timeout (int /*<<< orphan*/ ,scalar_t__,unsigned int,int,int /*<<< orphan*/ ,int) ; 
 int regmap_write_bits (int /*<<< orphan*/ ,scalar_t__,unsigned int,unsigned int) ; 
 struct uniphier_clk_cpugear* to_uniphier_clk_cpugear (struct clk_hw*) ; 

__attribute__((used)) static int uniphier_clk_cpugear_set_parent(struct clk_hw *hw, u8 index)
{
	struct uniphier_clk_cpugear *gear = to_uniphier_clk_cpugear(hw);
	int ret;
	unsigned int val;

	ret = regmap_write_bits(gear->regmap,
				gear->regbase + UNIPHIER_CLK_CPUGEAR_SET,
				gear->mask, index);
	if (ret)
		return ret;

	ret = regmap_write_bits(gear->regmap,
				gear->regbase + UNIPHIER_CLK_CPUGEAR_UPD,
				UNIPHIER_CLK_CPUGEAR_UPD_BIT,
				UNIPHIER_CLK_CPUGEAR_UPD_BIT);
	if (ret)
		return ret;

	return regmap_read_poll_timeout(gear->regmap,
				gear->regbase + UNIPHIER_CLK_CPUGEAR_UPD,
				val, !(val & UNIPHIER_CLK_CPUGEAR_UPD_BIT),
				0, 1);
}
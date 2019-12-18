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
typedef  unsigned int u32 ;
struct sprd_clk_common {int reg; int /*<<< orphan*/  regmap; } ;
struct sprd_pll {int regs_num; struct sprd_clk_common common; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int regmap_read (int /*<<< orphan*/ ,unsigned int,unsigned int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static inline void
sprd_pll_write(const struct sprd_pll *pll, u8 index,
				  u32 msk, u32 val)
{
	const struct sprd_clk_common *common = &pll->common;
	unsigned int offset, reg;
	int ret = 0;

	if (WARN_ON(index >= pll->regs_num))
		return;

	offset = common->reg + index * 4;
	ret = regmap_read(common->regmap, offset, &reg);
	if (!ret)
		regmap_write(common->regmap, offset, (reg & ~msk) | val);
}
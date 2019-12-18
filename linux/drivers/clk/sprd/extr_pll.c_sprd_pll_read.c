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
struct sprd_clk_common {scalar_t__ reg; int /*<<< orphan*/  regmap; } ;
struct sprd_pll {int regs_num; struct sprd_clk_common common; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,scalar_t__,unsigned int*) ; 

__attribute__((used)) static inline unsigned int
sprd_pll_read(const struct sprd_pll *pll, u8 index)
{
	const struct sprd_clk_common *common = &pll->common;
	unsigned int val = 0;

	if (WARN_ON(index >= pll->regs_num))
		return 0;

	regmap_read(common->regmap, common->reg + index * 4, &val);

	return val;
}
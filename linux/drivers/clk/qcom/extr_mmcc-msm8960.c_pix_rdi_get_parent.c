#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  regmap; } ;
struct clk_pix_rdi {int s2_mask; int s_mask; int /*<<< orphan*/  s_reg; TYPE_1__ clkr; int /*<<< orphan*/  s2_reg; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 struct clk_pix_rdi* to_clk_pix_rdi (struct clk_hw*) ; 

__attribute__((used)) static u8 pix_rdi_get_parent(struct clk_hw *hw)
{
	u32 val;
	struct clk_pix_rdi *rdi = to_clk_pix_rdi(hw);


	regmap_read(rdi->clkr.regmap, rdi->s2_reg, &val);
	if (val & rdi->s2_mask)
		return 2;

	regmap_read(rdi->clkr.regmap, rdi->s_reg, &val);
	if (val & rdi->s_mask)
		return 1;

	return 0;
}
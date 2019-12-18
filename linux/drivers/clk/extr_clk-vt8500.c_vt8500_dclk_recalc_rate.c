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
typedef  int u32 ;
struct clk_hw {int dummy; } ;
struct clk_device {int div_mask; int /*<<< orphan*/  div_reg; } ;

/* Variables and functions */
 int BIT (int) ; 
 int readl (int /*<<< orphan*/ ) ; 
 struct clk_device* to_clk_device (struct clk_hw*) ; 

__attribute__((used)) static unsigned long vt8500_dclk_recalc_rate(struct clk_hw *hw,
				unsigned long parent_rate)
{
	struct clk_device *cdev = to_clk_device(hw);
	u32 div = readl(cdev->div_reg) & cdev->div_mask;

	/* Special case for SDMMC devices */
	if ((cdev->div_mask == 0x3F) && (div & BIT(5)))
		div = 64 * (div & 0x1f);

	/* div == 0 is actually the highest divisor */
	if (div == 0)
		div = (cdev->div_mask + 1);

	return parent_rate / div;
}
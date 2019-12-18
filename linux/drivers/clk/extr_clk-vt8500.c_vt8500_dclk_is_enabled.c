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
struct clk_device {int /*<<< orphan*/  en_bit; int /*<<< orphan*/  en_reg; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int readl (int /*<<< orphan*/ ) ; 
 struct clk_device* to_clk_device (struct clk_hw*) ; 

__attribute__((used)) static int vt8500_dclk_is_enabled(struct clk_hw *hw)
{
	struct clk_device *cdev = to_clk_device(hw);
	u32 en_val = (readl(cdev->en_reg) & BIT(cdev->en_bit));

	return en_val ? 1 : 0;
}
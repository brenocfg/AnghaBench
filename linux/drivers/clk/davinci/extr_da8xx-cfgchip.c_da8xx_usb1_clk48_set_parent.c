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
struct da8xx_usb1_clk48 {int /*<<< orphan*/  regmap; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFGCHIP (int) ; 
 int /*<<< orphan*/  CFGCHIP2_USB1PHYCLKMUX ; 
 int regmap_write_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct da8xx_usb1_clk48* to_da8xx_usb1_clk48 (struct clk_hw*) ; 

__attribute__((used)) static int da8xx_usb1_clk48_set_parent(struct clk_hw *hw, u8 index)
{
	struct da8xx_usb1_clk48 *usb1 = to_da8xx_usb1_clk48(hw);

	return regmap_write_bits(usb1->regmap, CFGCHIP(2),
				 CFGCHIP2_USB1PHYCLKMUX,
				 index ? CFGCHIP2_USB1PHYCLKMUX : 0);
}
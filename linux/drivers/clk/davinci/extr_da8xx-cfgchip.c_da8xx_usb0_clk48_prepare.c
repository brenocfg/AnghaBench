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
struct da8xx_usb0_clk48 {int /*<<< orphan*/  fck; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int clk_prepare (int /*<<< orphan*/ ) ; 
 struct da8xx_usb0_clk48* to_da8xx_usb0_clk48 (struct clk_hw*) ; 

__attribute__((used)) static int da8xx_usb0_clk48_prepare(struct clk_hw *hw)
{
	struct da8xx_usb0_clk48 *usb0 = to_da8xx_usb0_clk48(hw);

	/* The USB 2.0 PSC clock is only needed temporarily during the USB 2.0
	 * PHY clock enable, but since clk_prepare() can't be called in an
	 * atomic context (i.e. in clk_enable()), we have to prepare it here.
	 */
	return clk_prepare(usb0->fck);
}
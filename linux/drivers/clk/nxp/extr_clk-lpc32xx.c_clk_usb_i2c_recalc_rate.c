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
struct clk_hw {int dummy; } ;

/* Variables and functions */
 size_t LPC32XX_CLK_PERIPH ; 
 int /*<<< orphan*/ * clk ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long clk_usb_i2c_recalc_rate(struct clk_hw *hw,
					     unsigned long parent_rate)
{
	return clk_get_rate(clk[LPC32XX_CLK_PERIPH]);
}
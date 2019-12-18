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
struct clk_hw {int dummy; } ;
struct at91sam9x5_clk_usb {int /*<<< orphan*/  usbs_mask; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_PMC_USB ; 
 int EINVAL ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct at91sam9x5_clk_usb* to_at91sam9x5_clk_usb (struct clk_hw*) ; 

__attribute__((used)) static int at91sam9x5_clk_usb_set_parent(struct clk_hw *hw, u8 index)
{
	struct at91sam9x5_clk_usb *usb = to_at91sam9x5_clk_usb(hw);

	if (index > 1)
		return -EINVAL;

	regmap_update_bits(usb->regmap, AT91_PMC_USB, usb->usbs_mask, index);

	return 0;
}
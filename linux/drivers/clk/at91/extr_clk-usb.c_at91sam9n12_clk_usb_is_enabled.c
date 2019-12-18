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
struct at91sam9x5_clk_usb {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_PMC_USB ; 
 unsigned int AT91_PMC_USBS ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 struct at91sam9x5_clk_usb* to_at91sam9x5_clk_usb (struct clk_hw*) ; 

__attribute__((used)) static int at91sam9n12_clk_usb_is_enabled(struct clk_hw *hw)
{
	struct at91sam9x5_clk_usb *usb = to_at91sam9x5_clk_usb(hw);
	unsigned int usbr;

	regmap_read(usb->regmap, AT91_PMC_USB, &usbr);

	return usbr & AT91_PMC_USBS;
}
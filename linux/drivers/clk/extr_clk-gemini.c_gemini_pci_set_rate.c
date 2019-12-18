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
struct clk_gemini_pci {int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GEMINI_GLOBAL_MISC_CONTROL ; 
 int /*<<< orphan*/  PCI_CLK_66MHZ ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct clk_gemini_pci* to_pciclk (struct clk_hw*) ; 

__attribute__((used)) static int gemini_pci_set_rate(struct clk_hw *hw, unsigned long rate,
			       unsigned long parent_rate)
{
	struct clk_gemini_pci *pciclk = to_pciclk(hw);

	if (rate == 33000000)
		return regmap_update_bits(pciclk->map,
					  GEMINI_GLOBAL_MISC_CONTROL,
					  PCI_CLK_66MHZ, 0);
	if (rate == 66000000)
		return regmap_update_bits(pciclk->map,
					  GEMINI_GLOBAL_MISC_CONTROL,
					  0, PCI_CLK_66MHZ);
	return -EINVAL;
}
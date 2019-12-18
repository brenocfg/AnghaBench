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
typedef  int /*<<< orphan*/  u8 ;
struct si5351_driver_data {scalar_t__ variant; } ;
typedef  enum si5351_pll_src { ____Placeholder_si5351_pll_src } si5351_pll_src ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SI5351_PLLA_SOURCE ; 
 int /*<<< orphan*/  SI5351_PLLB_SOURCE ; 
 int /*<<< orphan*/  SI5351_PLL_INPUT_SOURCE ; 
 int SI5351_PLL_SRC_DEFAULT ; 
 int SI5351_PLL_SRC_XTAL ; 
 scalar_t__ SI5351_VARIANT_C ; 
 int /*<<< orphan*/  si5351_set_bits (struct si5351_driver_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _si5351_pll_reparent(struct si5351_driver_data *drvdata,
				int num, enum si5351_pll_src parent)
{
	u8 mask = (num == 0) ? SI5351_PLLA_SOURCE : SI5351_PLLB_SOURCE;

	if (parent == SI5351_PLL_SRC_DEFAULT)
		return 0;

	if (num > 2)
		return -EINVAL;

	if (drvdata->variant != SI5351_VARIANT_C &&
	    parent != SI5351_PLL_SRC_XTAL)
		return -EINVAL;

	si5351_set_bits(drvdata, SI5351_PLL_INPUT_SOURCE, mask,
			(parent == SI5351_PLL_SRC_XTAL) ? 0 : mask);
	return 0;
}
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
typedef  scalar_t__ u32 ;
struct regmap {int dummy; } ;
struct clk_alpha_pll {int dummy; } ;
struct alpha_pll_config {scalar_t__ post_div_val; scalar_t__ post_div_mask; scalar_t__ config_ctl_val; scalar_t__ alpha; scalar_t__ l; } ;

/* Variables and functions */
 int /*<<< orphan*/  PLL_CONFIG_CTL (struct clk_alpha_pll*) ; 
 int /*<<< orphan*/  PLL_FRAC (struct clk_alpha_pll*) ; 
 int /*<<< orphan*/  PLL_L_VAL (struct clk_alpha_pll*) ; 
 int /*<<< orphan*/  PLL_MODE (struct clk_alpha_pll*) ; 
 scalar_t__ PLL_RESET_N ; 
 scalar_t__ PLL_UPDATE_BYPASS ; 
 int /*<<< orphan*/  PLL_USER_CTL (struct clk_alpha_pll*) ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,int /*<<< orphan*/ ,scalar_t__) ; 

void clk_fabia_pll_configure(struct clk_alpha_pll *pll, struct regmap *regmap,
			     const struct alpha_pll_config *config)
{
	u32 val, mask;

	if (config->l)
		regmap_write(regmap, PLL_L_VAL(pll), config->l);

	if (config->alpha)
		regmap_write(regmap, PLL_FRAC(pll), config->alpha);

	if (config->config_ctl_val)
		regmap_write(regmap, PLL_CONFIG_CTL(pll),
						config->config_ctl_val);

	if (config->post_div_mask) {
		mask = config->post_div_mask;
		val = config->post_div_val;
		regmap_update_bits(regmap, PLL_USER_CTL(pll), mask, val);
	}

	regmap_update_bits(regmap, PLL_MODE(pll), PLL_UPDATE_BYPASS,
							PLL_UPDATE_BYPASS);

	regmap_update_bits(regmap, PLL_MODE(pll), PLL_RESET_N, PLL_RESET_N);
}
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
typedef  int /*<<< orphan*/  u32 ;
struct regmap {int dummy; } ;
struct clk_alpha_pll {int flags; } ;
struct alpha_pll_config {int /*<<< orphan*/  vco_mask; int /*<<< orphan*/  post_div_mask; int /*<<< orphan*/  pre_div_mask; int /*<<< orphan*/  early_output_mask; int /*<<< orphan*/  aux2_output_mask; int /*<<< orphan*/  aux_output_mask; int /*<<< orphan*/  main_output_mask; int /*<<< orphan*/  alpha_mode_mask; int /*<<< orphan*/  alpha_en_mask; int /*<<< orphan*/  vco_val; int /*<<< orphan*/  post_div_val; int /*<<< orphan*/  pre_div_val; int /*<<< orphan*/  alpha_hi; int /*<<< orphan*/  config_ctl_hi_val; int /*<<< orphan*/  config_ctl_val; int /*<<< orphan*/  alpha; int /*<<< orphan*/  l; } ;

/* Variables and functions */
 int /*<<< orphan*/  PLL_ALPHA_VAL (struct clk_alpha_pll*) ; 
 int /*<<< orphan*/  PLL_ALPHA_VAL_U (struct clk_alpha_pll*) ; 
 int /*<<< orphan*/  PLL_CONFIG_CTL (struct clk_alpha_pll*) ; 
 int /*<<< orphan*/  PLL_CONFIG_CTL_U (struct clk_alpha_pll*) ; 
 int /*<<< orphan*/  PLL_L_VAL (struct clk_alpha_pll*) ; 
 int /*<<< orphan*/  PLL_MODE (struct clk_alpha_pll*) ; 
 int /*<<< orphan*/  PLL_USER_CTL (struct clk_alpha_pll*) ; 
 int SUPPORTS_FSM_MODE ; 
 int pll_alpha_width (struct clk_alpha_pll*) ; 
 scalar_t__ pll_has_64bit_config (struct clk_alpha_pll*) ; 
 int /*<<< orphan*/  qcom_pll_set_fsm_mode (struct regmap*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void clk_alpha_pll_configure(struct clk_alpha_pll *pll, struct regmap *regmap,
			     const struct alpha_pll_config *config)
{
	u32 val, mask;

	regmap_write(regmap, PLL_L_VAL(pll), config->l);
	regmap_write(regmap, PLL_ALPHA_VAL(pll), config->alpha);
	regmap_write(regmap, PLL_CONFIG_CTL(pll), config->config_ctl_val);

	if (pll_has_64bit_config(pll))
		regmap_write(regmap, PLL_CONFIG_CTL_U(pll),
			     config->config_ctl_hi_val);

	if (pll_alpha_width(pll) > 32)
		regmap_write(regmap, PLL_ALPHA_VAL_U(pll), config->alpha_hi);

	val = config->main_output_mask;
	val |= config->aux_output_mask;
	val |= config->aux2_output_mask;
	val |= config->early_output_mask;
	val |= config->pre_div_val;
	val |= config->post_div_val;
	val |= config->vco_val;
	val |= config->alpha_en_mask;
	val |= config->alpha_mode_mask;

	mask = config->main_output_mask;
	mask |= config->aux_output_mask;
	mask |= config->aux2_output_mask;
	mask |= config->early_output_mask;
	mask |= config->pre_div_mask;
	mask |= config->post_div_mask;
	mask |= config->vco_mask;

	regmap_update_bits(regmap, PLL_USER_CTL(pll), mask, val);

	if (pll->flags & SUPPORTS_FSM_MODE)
		qcom_pll_set_fsm_mode(regmap, PLL_MODE(pll), 6, 0);
}
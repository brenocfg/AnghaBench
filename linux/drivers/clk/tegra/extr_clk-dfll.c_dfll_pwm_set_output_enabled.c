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
struct tegra_dfll {int /*<<< orphan*/  dev; int /*<<< orphan*/  pwm_disable_state; int /*<<< orphan*/  pwm_pin; int /*<<< orphan*/  pwm_rate; int /*<<< orphan*/  ref_rate; int /*<<< orphan*/  pwm_enable_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DFLL_OUTPUT_CFG ; 
 int DFLL_OUTPUT_CFG_PWM_DIV_MASK ; 
 int DFLL_OUTPUT_CFG_PWM_DIV_SHIFT ; 
 int DFLL_OUTPUT_CFG_PWM_ENABLE ; 
 int DIV_ROUND_UP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int dfll_readl (struct tegra_dfll*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dfll_wmb (struct tegra_dfll*) ; 
 int /*<<< orphan*/  dfll_writel (struct tegra_dfll*,int,int /*<<< orphan*/ ) ; 
 int pinctrl_select_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dfll_pwm_set_output_enabled(struct tegra_dfll *td, bool enable)
{
	int ret;
	u32 val, div;

	if (enable) {
		ret = pinctrl_select_state(td->pwm_pin, td->pwm_enable_state);
		if (ret < 0) {
			dev_err(td->dev, "setting enable state failed\n");
			return -EINVAL;
		}
		val = dfll_readl(td, DFLL_OUTPUT_CFG);
		val &= ~DFLL_OUTPUT_CFG_PWM_DIV_MASK;
		div = DIV_ROUND_UP(td->ref_rate, td->pwm_rate);
		val |= (div << DFLL_OUTPUT_CFG_PWM_DIV_SHIFT)
				& DFLL_OUTPUT_CFG_PWM_DIV_MASK;
		dfll_writel(td, val, DFLL_OUTPUT_CFG);
		dfll_wmb(td);

		val |= DFLL_OUTPUT_CFG_PWM_ENABLE;
		dfll_writel(td, val, DFLL_OUTPUT_CFG);
		dfll_wmb(td);
	} else {
		ret = pinctrl_select_state(td->pwm_pin, td->pwm_disable_state);
		if (ret < 0)
			dev_warn(td->dev, "setting disable state failed\n");

		val = dfll_readl(td, DFLL_OUTPUT_CFG);
		val &= ~DFLL_OUTPUT_CFG_PWM_ENABLE;
		dfll_writel(td, val, DFLL_OUTPUT_CFG);
		dfll_wmb(td);
	}

	return 0;
}
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
struct stm32_lptim_cnt {int enabled; int ceiling; int /*<<< orphan*/  regmap; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  STM32_LPTIM_ARR ; 
 int /*<<< orphan*/  STM32_LPTIM_CMP ; 
 int STM32_LPTIM_CMPOKCF_ARROKCF ; 
 int STM32_LPTIM_CMPOK_ARROK ; 
 int /*<<< orphan*/  STM32_LPTIM_CNTSTRT ; 
 int /*<<< orphan*/  STM32_LPTIM_CR ; 
 int /*<<< orphan*/  STM32_LPTIM_ENABLE ; 
 int /*<<< orphan*/  STM32_LPTIM_ICR ; 
 int /*<<< orphan*/  STM32_LPTIM_ISR ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 int regmap_read_poll_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int stm32_lptim_set_enable_state(struct stm32_lptim_cnt *priv,
					int enable)
{
	int ret;
	u32 val;

	val = FIELD_PREP(STM32_LPTIM_ENABLE, enable);
	ret = regmap_write(priv->regmap, STM32_LPTIM_CR, val);
	if (ret)
		return ret;

	if (!enable) {
		clk_disable(priv->clk);
		priv->enabled = false;
		return 0;
	}

	/* LP timer must be enabled before writing CMP & ARR */
	ret = regmap_write(priv->regmap, STM32_LPTIM_ARR, priv->ceiling);
	if (ret)
		return ret;

	ret = regmap_write(priv->regmap, STM32_LPTIM_CMP, 0);
	if (ret)
		return ret;

	/* ensure CMP & ARR registers are properly written */
	ret = regmap_read_poll_timeout(priv->regmap, STM32_LPTIM_ISR, val,
				       (val & STM32_LPTIM_CMPOK_ARROK),
				       100, 1000);
	if (ret)
		return ret;

	ret = regmap_write(priv->regmap, STM32_LPTIM_ICR,
			   STM32_LPTIM_CMPOKCF_ARROKCF);
	if (ret)
		return ret;

	ret = clk_enable(priv->clk);
	if (ret) {
		regmap_write(priv->regmap, STM32_LPTIM_CR, 0);
		return ret;
	}
	priv->enabled = true;

	/* Start LP timer in continuous mode */
	return regmap_update_bits(priv->regmap, STM32_LPTIM_CR,
				  STM32_LPTIM_CNTSTRT, STM32_LPTIM_CNTSTRT);
}
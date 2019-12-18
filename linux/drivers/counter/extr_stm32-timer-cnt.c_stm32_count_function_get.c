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
struct stm32_timer_cnt {int /*<<< orphan*/  regmap; } ;
struct counter_device {struct stm32_timer_cnt* priv; } ;
struct counter_count {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t STM32_COUNT_ENCODER_MODE_1 ; 
 size_t STM32_COUNT_ENCODER_MODE_2 ; 
 size_t STM32_COUNT_ENCODER_MODE_3 ; 
 int /*<<< orphan*/  TIM_SMCR ; 
 int TIM_SMCR_SMS ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int stm32_count_function_get(struct counter_device *counter,
				    struct counter_count *count,
				    size_t *function)
{
	struct stm32_timer_cnt *const priv = counter->priv;
	u32 smcr;

	regmap_read(priv->regmap, TIM_SMCR, &smcr);

	switch (smcr & TIM_SMCR_SMS) {
	case 1:
		*function = STM32_COUNT_ENCODER_MODE_1;
		return 0;
	case 2:
		*function = STM32_COUNT_ENCODER_MODE_2;
		return 0;
	case 3:
		*function = STM32_COUNT_ENCODER_MODE_3;
		return 0;
	}

	return -EINVAL;
}
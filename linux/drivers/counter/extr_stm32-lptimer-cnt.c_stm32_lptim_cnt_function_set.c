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
struct stm32_lptim_cnt {int quadrature_mode; int /*<<< orphan*/  polarity; } ;
struct counter_device {struct stm32_lptim_cnt* priv; } ;
struct counter_count {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
#define  STM32_LPTIM_COUNTER_INCREASE 129 
#define  STM32_LPTIM_ENCODER_BOTH_EDGE 128 
 int /*<<< orphan*/  STM32_LPTIM_SYNAPSE_ACTION_BOTH_EDGES ; 
 scalar_t__ stm32_lptim_is_enabled (struct stm32_lptim_cnt* const) ; 

__attribute__((used)) static int stm32_lptim_cnt_function_set(struct counter_device *counter,
					struct counter_count *count,
					size_t function)
{
	struct stm32_lptim_cnt *const priv = counter->priv;

	if (stm32_lptim_is_enabled(priv))
		return -EBUSY;

	switch (function) {
	case STM32_LPTIM_COUNTER_INCREASE:
		priv->quadrature_mode = 0;
		return 0;
	case STM32_LPTIM_ENCODER_BOTH_EDGE:
		priv->quadrature_mode = 1;
		priv->polarity = STM32_LPTIM_SYNAPSE_ACTION_BOTH_EDGES;
		return 0;
	}

	return -EINVAL;
}
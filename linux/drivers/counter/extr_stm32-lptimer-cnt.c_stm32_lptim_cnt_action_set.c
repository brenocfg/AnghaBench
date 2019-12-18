#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct stm32_lptim_cnt {size_t polarity; } ;
struct counter_synapse {TYPE_1__* signal; } ;
struct counter_device {struct stm32_lptim_cnt* priv; } ;
struct counter_count {TYPE_2__* synapses; } ;
struct TYPE_6__ {scalar_t__ id; } ;
struct TYPE_5__ {TYPE_3__* signal; } ;
struct TYPE_4__ {scalar_t__ id; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 size_t STM32_LPTIM_COUNTER_INCREASE ; 
#define  STM32_LPTIM_SYNAPSE_ACTION_BOTH_EDGES 130 
#define  STM32_LPTIM_SYNAPSE_ACTION_FALLING_EDGE 129 
#define  STM32_LPTIM_SYNAPSE_ACTION_RISING_EDGE 128 
 int stm32_lptim_cnt_function_get (struct counter_device*,struct counter_count*,size_t*) ; 
 scalar_t__ stm32_lptim_is_enabled (struct stm32_lptim_cnt* const) ; 

__attribute__((used)) static int stm32_lptim_cnt_action_set(struct counter_device *counter,
				      struct counter_count *count,
				      struct counter_synapse *synapse,
				      size_t action)
{
	struct stm32_lptim_cnt *const priv = counter->priv;
	size_t function;
	int err;

	if (stm32_lptim_is_enabled(priv))
		return -EBUSY;

	err = stm32_lptim_cnt_function_get(counter, count, &function);
	if (err)
		return err;

	/* only set polarity when in counter mode (on input 1) */
	if (function == STM32_LPTIM_COUNTER_INCREASE
	    && synapse->signal->id == count->synapses[0].signal->id) {
		switch (action) {
		case STM32_LPTIM_SYNAPSE_ACTION_RISING_EDGE:
		case STM32_LPTIM_SYNAPSE_ACTION_FALLING_EDGE:
		case STM32_LPTIM_SYNAPSE_ACTION_BOTH_EDGES:
			priv->polarity = action;
			return 0;
		}
	}

	return -EINVAL;
}
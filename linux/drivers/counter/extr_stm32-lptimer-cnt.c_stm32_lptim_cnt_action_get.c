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
struct counter_synapse {TYPE_2__* signal; } ;
struct counter_device {struct stm32_lptim_cnt* priv; } ;
struct counter_count {TYPE_1__* synapses; } ;
struct TYPE_6__ {int /*<<< orphan*/  id; } ;
struct TYPE_5__ {int /*<<< orphan*/  id; } ;
struct TYPE_4__ {TYPE_3__* signal; } ;

/* Variables and functions */
 int EINVAL ; 
#define  STM32_LPTIM_COUNTER_INCREASE 129 
#define  STM32_LPTIM_ENCODER_BOTH_EDGE 128 
 size_t STM32_LPTIM_SYNAPSE_ACTION_NONE ; 
 int stm32_lptim_cnt_function_get (struct counter_device*,struct counter_count*,size_t*) ; 

__attribute__((used)) static int stm32_lptim_cnt_action_get(struct counter_device *counter,
				      struct counter_count *count,
				      struct counter_synapse *synapse,
				      size_t *action)
{
	struct stm32_lptim_cnt *const priv = counter->priv;
	size_t function;
	int err;

	err = stm32_lptim_cnt_function_get(counter, count, &function);
	if (err)
		return err;

	switch (function) {
	case STM32_LPTIM_COUNTER_INCREASE:
		/* LP Timer acts as up-counter on input 1 */
		if (synapse->signal->id == count->synapses[0].signal->id)
			*action = priv->polarity;
		else
			*action = STM32_LPTIM_SYNAPSE_ACTION_NONE;
		return 0;
	case STM32_LPTIM_ENCODER_BOTH_EDGE:
		*action = priv->polarity;
		return 0;
	}

	return -EINVAL;
}
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
struct counter_synapse {TYPE_3__* signal; } ;
struct counter_device {int dummy; } ;
struct counter_count {TYPE_2__* synapses; } ;
struct TYPE_6__ {int /*<<< orphan*/  id; } ;
struct TYPE_5__ {TYPE_1__* signal; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
#define  STM32_COUNT_ENCODER_MODE_1 130 
#define  STM32_COUNT_ENCODER_MODE_2 129 
#define  STM32_COUNT_ENCODER_MODE_3 128 
 size_t STM32_SYNAPSE_ACTION_BOTH_EDGES ; 
 size_t STM32_SYNAPSE_ACTION_NONE ; 
 int stm32_count_function_get (struct counter_device*,struct counter_count*,size_t*) ; 

__attribute__((used)) static int stm32_action_get(struct counter_device *counter,
			    struct counter_count *count,
			    struct counter_synapse *synapse,
			    size_t *action)
{
	size_t function;
	int err;

	/* Default action mode (e.g. STM32_COUNT_SLAVE_MODE_DISABLED) */
	*action = STM32_SYNAPSE_ACTION_NONE;

	err = stm32_count_function_get(counter, count, &function);
	if (err)
		return 0;

	switch (function) {
	case STM32_COUNT_ENCODER_MODE_1:
		/* counts up/down on TI1FP1 edge depending on TI2FP2 level */
		if (synapse->signal->id == count->synapses[0].signal->id)
			*action = STM32_SYNAPSE_ACTION_BOTH_EDGES;
		break;
	case STM32_COUNT_ENCODER_MODE_2:
		/* counts up/down on TI2FP2 edge depending on TI1FP1 level */
		if (synapse->signal->id == count->synapses[1].signal->id)
			*action = STM32_SYNAPSE_ACTION_BOTH_EDGES;
		break;
	case STM32_COUNT_ENCODER_MODE_3:
		/* counts up/down on both TI1FP1 and TI2FP2 edges */
		*action = STM32_SYNAPSE_ACTION_BOTH_EDGES;
		break;
	}

	return 0;
}
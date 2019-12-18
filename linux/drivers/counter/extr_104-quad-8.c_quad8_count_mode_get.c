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
struct quad8_iio {int* count_mode; } ;
struct counter_device {struct quad8_iio* priv; } ;
struct counter_count {size_t id; } ;

/* Variables and functions */
 size_t COUNTER_COUNT_MODE_MODULO_N ; 
 size_t COUNTER_COUNT_MODE_NON_RECYCLE ; 
 size_t COUNTER_COUNT_MODE_NORMAL ; 
 size_t COUNTER_COUNT_MODE_RANGE_LIMIT ; 

__attribute__((used)) static int quad8_count_mode_get(struct counter_device *counter,
	struct counter_count *count, size_t *cnt_mode)
{
	const struct quad8_iio *const priv = counter->priv;

	/* Map 104-QUAD-8 count mode to Generic Counter count mode */
	switch (priv->count_mode[count->id]) {
	case 0:
		*cnt_mode = COUNTER_COUNT_MODE_NORMAL;
		break;
	case 1:
		*cnt_mode = COUNTER_COUNT_MODE_RANGE_LIMIT;
		break;
	case 2:
		*cnt_mode = COUNTER_COUNT_MODE_NON_RECYCLE;
		break;
	case 3:
		*cnt_mode = COUNTER_COUNT_MODE_MODULO_N;
		break;
	}

	return 0;
}
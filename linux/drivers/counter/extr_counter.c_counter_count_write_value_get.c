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
struct counter_count_write_value {int /*<<< orphan*/  buf; } ;
typedef  enum counter_count_value_type { ____Placeholder_counter_count_value_type } counter_count_value_type ;

/* Variables and functions */
#define  COUNTER_COUNT_POSITION 128 
 int kstrtoul (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void* const) ; 

int counter_count_write_value_get(void *const data,
				  const enum counter_count_value_type type,
				  const struct counter_count_write_value *const val)
{
	int err;

	switch (type) {
	case COUNTER_COUNT_POSITION:
		err = kstrtoul(val->buf, 0, data);
		if (err)
			return err;
		break;
	}

	return 0;
}
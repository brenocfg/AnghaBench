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
struct counter_count_read_value {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
typedef  enum counter_count_value_type { ____Placeholder_counter_count_value_type } counter_count_value_type ;

/* Variables and functions */
#define  COUNTER_COUNT_POSITION 128 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,unsigned long) ; 

void counter_count_read_value_set(struct counter_count_read_value *const val,
				  const enum counter_count_value_type type,
				  void *const data)
{
	switch (type) {
	case COUNTER_COUNT_POSITION:
		val->len = sprintf(val->buf, "%lu\n", *(unsigned long *)data);
		break;
	default:
		val->len = 0;
	}
}
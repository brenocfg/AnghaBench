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
typedef  enum stack_type { ____Placeholder_stack_type } stack_type ;

/* Variables and functions */
#define  STACK_TYPE_IRQ 131 
#define  STACK_TYPE_NODAT 130 
#define  STACK_TYPE_RESTART 129 
#define  STACK_TYPE_TASK 128 

const char *stack_type_name(enum stack_type type)
{
	switch (type) {
	case STACK_TYPE_TASK:
		return "task";
	case STACK_TYPE_IRQ:
		return "irq";
	case STACK_TYPE_NODAT:
		return "nodat";
	case STACK_TYPE_RESTART:
		return "restart";
	default:
		return "unknown";
	}
}
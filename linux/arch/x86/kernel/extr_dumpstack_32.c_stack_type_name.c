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
 int STACK_TYPE_ENTRY ; 
 int STACK_TYPE_IRQ ; 
 int STACK_TYPE_SOFTIRQ ; 

const char *stack_type_name(enum stack_type type)
{
	if (type == STACK_TYPE_IRQ)
		return "IRQ";

	if (type == STACK_TYPE_SOFTIRQ)
		return "SOFTIRQ";

	if (type == STACK_TYPE_ENTRY)
		return "ENTRY_TRAMPOLINE";

	return NULL;
}
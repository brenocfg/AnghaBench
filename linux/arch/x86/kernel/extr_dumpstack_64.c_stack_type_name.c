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
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int N_EXCEPTION_STACKS ; 
 int STACK_TYPE_ENTRY ; 
 int STACK_TYPE_EXCEPTION ; 
 int STACK_TYPE_EXCEPTION_LAST ; 
 int STACK_TYPE_IRQ ; 
 char const** exception_stack_names ; 

const char *stack_type_name(enum stack_type type)
{
	BUILD_BUG_ON(N_EXCEPTION_STACKS != 6);

	if (type == STACK_TYPE_IRQ)
		return "IRQ";

	if (type == STACK_TYPE_ENTRY) {
		/*
		 * On 64-bit, we have a generic entry stack that we
		 * use for all the kernel entry points, including
		 * SYSENTER.
		 */
		return "ENTRY_TRAMPOLINE";
	}

	if (type >= STACK_TYPE_EXCEPTION && type <= STACK_TYPE_EXCEPTION_LAST)
		return exception_stack_names[type - STACK_TYPE_EXCEPTION];

	return NULL;
}
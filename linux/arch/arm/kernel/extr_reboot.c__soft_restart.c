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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  __soft_restart ; 
 int /*<<< orphan*/  call_with_stack (int /*<<< orphan*/ ,void*,void*) ; 
 int /*<<< orphan*/  local_fiq_disable () ; 
 int /*<<< orphan*/  outer_disable () ; 
 int /*<<< orphan*/  raw_local_irq_disable () ; 
 int /*<<< orphan*/ * soft_restart_stack ; 

void _soft_restart(unsigned long addr, bool disable_l2)
{
	u64 *stack = soft_restart_stack + ARRAY_SIZE(soft_restart_stack);

	/* Disable interrupts first */
	raw_local_irq_disable();
	local_fiq_disable();

	/* Disable the L2 if we're the last man standing. */
	if (disable_l2)
		outer_disable();

	/* Change to the new stack and continue with the reset. */
	call_with_stack(__soft_restart, (void *)addr, (void *)stack);

	/* Should never get here. */
	BUG();
}
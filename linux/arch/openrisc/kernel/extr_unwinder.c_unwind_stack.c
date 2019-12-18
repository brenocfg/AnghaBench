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

/* Variables and functions */
 scalar_t__ __kernel_text_address (unsigned long) ; 
 int /*<<< orphan*/  kstack_end (unsigned long*) ; 

void unwind_stack(void *data, unsigned long *stack,
		   void (*trace)(void *data, unsigned long addr, int reliable))
{
	unsigned long addr;

	while (!kstack_end(stack)) {
		addr = *stack++;
		if (__kernel_text_address(addr))
			trace(data, addr, 0);
	}
}
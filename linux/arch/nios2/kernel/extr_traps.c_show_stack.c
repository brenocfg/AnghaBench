#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ ksp; } ;
struct task_struct {TYPE_1__ thread; } ;

/* Variables and functions */
 scalar_t__ PAGE_ALIGN (unsigned long) ; 
 scalar_t__ _etext ; 
 scalar_t__ _stext ; 
 int kstack_depth_to_print ; 
 int /*<<< orphan*/  pr_emerg (char*,...) ; 

void show_stack(struct task_struct *task, unsigned long *stack)
{
	unsigned long *endstack, addr;
	int i;

	if (!stack) {
		if (task)
			stack = (unsigned long *)task->thread.ksp;
		else
			stack = (unsigned long *)&stack;
	}

	addr = (unsigned long) stack;
	endstack = (unsigned long *) PAGE_ALIGN(addr);

	pr_emerg("Stack from %08lx:", (unsigned long)stack);
	for (i = 0; i < kstack_depth_to_print; i++) {
		if (stack + 1 > endstack)
			break;
		if (i % 8 == 0)
			pr_emerg("\n       ");
		pr_emerg(" %08lx", *stack++);
	}

	pr_emerg("\nCall Trace:");
	i = 0;
	while (stack + 1 <= endstack) {
		addr = *stack++;
		/*
		 * If the address is either in the text segment of the
		 * kernel, or in the region which contains vmalloc'ed
		 * memory, it *may* be the address of a calling
		 * routine; if so, print it so that someone tracing
		 * down the cause of the crash will be able to figure
		 * out the call path that was taken.
		 */
		if (((addr >= (unsigned long) _stext) &&
		     (addr <= (unsigned long) _etext))) {
			if (i % 4 == 0)
				pr_emerg("\n       ");
			pr_emerg(" [<%08lx>]", addr);
			i++;
		}
	}
	pr_emerg("\n");
}
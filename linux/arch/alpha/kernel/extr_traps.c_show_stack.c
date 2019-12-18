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
struct task_struct {int dummy; } ;

/* Variables and functions */
 int THREAD_SIZE ; 
 int /*<<< orphan*/  dik_show_trace (unsigned long*) ; 
 int kstack_depth_to_print ; 
 int /*<<< orphan*/  pr_cont (char*,...) ; 
 int /*<<< orphan*/  printk (char*) ; 

void show_stack(struct task_struct *task, unsigned long *sp)
{
	unsigned long *stack;
	int i;

	/*
	 * debugging aid: "show_stack(NULL);" prints the
	 * back trace for this cpu.
	 */
	if(sp==NULL)
		sp=(unsigned long*)&sp;

	stack = sp;
	for(i=0; i < kstack_depth_to_print; i++) {
		if (((long) stack & (THREAD_SIZE-1)) == 0)
			break;
		if ((i % 4) == 0) {
			if (i)
				pr_cont("\n");
			printk("       ");
		} else {
			pr_cont(" ");
		}
		pr_cont("%016lx", *stack++);
	}
	pr_cont("\n");
	dik_show_trace(sp);
}
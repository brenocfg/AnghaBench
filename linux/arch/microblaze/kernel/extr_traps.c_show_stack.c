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
typedef  int u32 ;
struct TYPE_2__ {int r1; } ;
struct thread_info {TYPE_1__ cpu_context; } ;
struct task_struct {scalar_t__ stack; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_PREFIX_ADDRESS ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int THREAD_SIZE ; 
 struct task_struct* current ; 
 int /*<<< orphan*/  debug_show_held_locks (struct task_struct*) ; 
 unsigned long kstack_depth_to_print ; 
 int /*<<< orphan*/  microblaze_unwind (struct task_struct*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  print_hex_dump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,void*,unsigned long,int /*<<< orphan*/ ) ; 

void show_stack(struct task_struct *task, unsigned long *sp)
{
	unsigned long words_to_show;
	u32 fp = (u32) sp;

	if (fp == 0) {
		if (task) {
			fp = ((struct thread_info *)
				(task->stack))->cpu_context.r1;
		} else {
			/* Pick up caller of dump_stack() */
			fp = (u32)&sp - 8;
		}
	}

	words_to_show = (THREAD_SIZE - (fp & (THREAD_SIZE - 1))) >> 2;
	if (kstack_depth_to_print && (words_to_show > kstack_depth_to_print))
		words_to_show = kstack_depth_to_print;

	pr_info("Kernel Stack:\n");

	/*
	 * Make the first line an 'odd' size if necessary to get
	 * remaining lines to start at an address multiple of 0x10
	 */
	if (fp & 0xF) {
		unsigned long line1_words = (0x10 - (fp & 0xF)) >> 2;
		if (line1_words < words_to_show) {
			print_hex_dump(KERN_INFO, "", DUMP_PREFIX_ADDRESS, 32,
				       4, (void *)fp, line1_words << 2, 0);
			fp += line1_words << 2;
			words_to_show -= line1_words;
		}
	}
	print_hex_dump(KERN_INFO, "", DUMP_PREFIX_ADDRESS, 32, 4, (void *)fp,
		       words_to_show << 2, 0);
	pr_info("\n\nCall Trace:\n");
	microblaze_unwind(task, NULL);
	pr_info("\n");

	if (!task)
		task = current;

	debug_show_held_locks(task);
}
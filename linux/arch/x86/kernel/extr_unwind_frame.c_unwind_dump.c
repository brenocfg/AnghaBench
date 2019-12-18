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
struct TYPE_2__ {unsigned long* type; int next_sp; } ;
struct unwind_state {unsigned long stack_mask; void* graph_idx; int /*<<< orphan*/  task; int /*<<< orphan*/  orig_sp; TYPE_1__ stack_info; } ;
struct stack_info {unsigned long* end; int /*<<< orphan*/  next_sp; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int BITS_PER_LONG ; 
 unsigned long* PTR_ALIGN (int /*<<< orphan*/ ,int) ; 
 unsigned long READ_ONCE_NOCHECK (unsigned long) ; 
 scalar_t__ get_stack_info (unsigned long*,int /*<<< orphan*/ ,struct stack_info*,unsigned long*) ; 
 int /*<<< orphan*/  printk_deferred (char*,unsigned long*,int,unsigned long,...) ; 

__attribute__((used)) static void unwind_dump(struct unwind_state *state)
{
	static bool dumped_before = false;
	bool prev_zero, zero = false;
	unsigned long word, *sp;
	struct stack_info stack_info = {0};
	unsigned long visit_mask = 0;

	if (dumped_before)
		return;

	dumped_before = true;

	printk_deferred("unwind stack type:%d next_sp:%p mask:0x%lx graph_idx:%d\n",
			state->stack_info.type, state->stack_info.next_sp,
			state->stack_mask, state->graph_idx);

	for (sp = PTR_ALIGN(state->orig_sp, sizeof(long)); sp;
	     sp = PTR_ALIGN(stack_info.next_sp, sizeof(long))) {
		if (get_stack_info(sp, state->task, &stack_info, &visit_mask))
			break;

		for (; sp < stack_info.end; sp++) {

			word = READ_ONCE_NOCHECK(*sp);

			prev_zero = zero;
			zero = word == 0;

			if (zero) {
				if (!prev_zero)
					printk_deferred("%p: %0*x ...\n",
							sp, BITS_PER_LONG/4, 0);
				continue;
			}

			printk_deferred("%p: %0*lx (%pB)\n",
					sp, BITS_PER_LONG/4, word, (void *)word);
		}
	}
}
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
struct unwind_state {int dummy; } ;
struct task_struct {int dummy; } ;
struct pt_regs {unsigned long ip; } ;
typedef  int /*<<< orphan*/  (* stack_trace_consume_fn ) (void*,unsigned long,int) ;

/* Variables and functions */
 int /*<<< orphan*/  unwind_done (struct unwind_state*) ; 
 unsigned long unwind_get_return_address (struct unwind_state*) ; 
 int /*<<< orphan*/  unwind_next_frame (struct unwind_state*) ; 
 int /*<<< orphan*/  unwind_start (struct unwind_state*,struct task_struct*,struct pt_regs*,int /*<<< orphan*/ *) ; 

void arch_stack_walk(stack_trace_consume_fn consume_entry, void *cookie,
		     struct task_struct *task, struct pt_regs *regs)
{
	struct unwind_state state;
	unsigned long addr;

	if (regs && !consume_entry(cookie, regs->ip, false))
		return;

	for (unwind_start(&state, task, regs, NULL); !unwind_done(&state);
	     unwind_next_frame(&state)) {
		addr = unwind_get_return_address(&state);
		if (!addr || !consume_entry(cookie, addr, false))
			break;
	}
}
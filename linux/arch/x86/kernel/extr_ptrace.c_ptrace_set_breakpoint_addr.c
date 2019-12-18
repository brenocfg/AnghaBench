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
struct thread_struct {struct perf_event** ptrace_bps; } ;
struct task_struct {struct thread_struct thread; } ;
struct perf_event_attr {unsigned long bp_addr; } ;
struct perf_event {struct perf_event_attr attr; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct perf_event*) ; 
 int PTR_ERR (struct perf_event*) ; 
 int /*<<< orphan*/  X86_BREAKPOINT_LEN_1 ; 
 int /*<<< orphan*/  X86_BREAKPOINT_WRITE ; 
 int modify_user_hw_breakpoint (struct perf_event*,struct perf_event_attr*) ; 
 struct perf_event* ptrace_register_breakpoint (struct task_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int) ; 

__attribute__((used)) static int ptrace_set_breakpoint_addr(struct task_struct *tsk, int nr,
				      unsigned long addr)
{
	struct thread_struct *t = &tsk->thread;
	struct perf_event *bp = t->ptrace_bps[nr];
	int err = 0;

	if (!bp) {
		/*
		 * Put stub len and type to create an inactive but correct bp.
		 *
		 * CHECKME: the previous code returned -EIO if the addr wasn't
		 * a valid task virtual addr. The new one will return -EINVAL in
		 *  this case.
		 * -EINVAL may be what we want for in-kernel breakpoints users,
		 * but -EIO looks better for ptrace, since we refuse a register
		 * writing for the user. And anyway this is the previous
		 * behaviour.
		 */
		bp = ptrace_register_breakpoint(tsk,
				X86_BREAKPOINT_LEN_1, X86_BREAKPOINT_WRITE,
				addr, true);
		if (IS_ERR(bp))
			err = PTR_ERR(bp);
		else
			t->ptrace_bps[nr] = bp;
	} else {
		struct perf_event_attr attr = bp->attr;

		attr.bp_addr = addr;
		err = modify_user_hw_breakpoint(bp, &attr);
	}

	return err;
}
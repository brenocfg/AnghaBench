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
typedef  int /*<<< orphan*/  RtldLockState ;

/* Variables and functions */
 int PF_X ; 
 int PROT_EXEC ; 
 scalar_t__ get_program_var_addr (char*,int /*<<< orphan*/ *) ; 
 int max_stack_flags ; 
 int stack_prot ; 

__attribute__((used)) static void
map_stacks_exec(RtldLockState *lockstate)
{
	void (*thr_map_stacks_exec)(void);

	if ((max_stack_flags & PF_X) == 0 || (stack_prot & PROT_EXEC) != 0)
		return;
	thr_map_stacks_exec = (void (*)(void))(uintptr_t)
	    get_program_var_addr("__pthread_map_stacks_exec", lockstate);
	if (thr_map_stacks_exec != NULL) {
		stack_prot |= PROT_EXEC;
		thr_map_stacks_exec();
	}
}
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
struct stack_info {int dummy; } ;
struct unwind_state {unsigned long stack_mask; int /*<<< orphan*/  task; struct stack_info stack_info; } ;
struct stack_frame {int dummy; } ;

/* Variables and functions */
 scalar_t__ get_stack_info (unsigned long,int /*<<< orphan*/ ,struct stack_info*,unsigned long*) ; 
 int /*<<< orphan*/  on_stack (struct stack_info*,unsigned long,int) ; 

__attribute__((used)) static bool update_stack_info(struct unwind_state *state, unsigned long sp)
{
	struct stack_info *info = &state->stack_info;
	unsigned long *mask = &state->stack_mask;

	/* New stack pointer leaves the current stack */
	if (get_stack_info(sp, state->task, info, mask) != 0 ||
	    !on_stack(info, sp, sizeof(struct stack_frame)))
		/* 'sp' does not point to a valid stack */
		return false;
	return true;
}
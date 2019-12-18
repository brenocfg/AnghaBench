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
struct unwind_state {int /*<<< orphan*/  stack_mask; int /*<<< orphan*/  task; struct stack_info stack_info; } ;

/* Variables and functions */
 scalar_t__ get_stack_info (void*,int /*<<< orphan*/ ,struct stack_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  on_stack (struct stack_info*,void*,size_t) ; 

__attribute__((used)) static bool stack_access_ok(struct unwind_state *state, unsigned long _addr,
			    size_t len)
{
	struct stack_info *info = &state->stack_info;
	void *addr = (void *)_addr;

	if (!on_stack(info, addr, len) &&
	    (get_stack_info(addr, state->task, info, &state->stack_mask)))
		return false;

	return true;
}
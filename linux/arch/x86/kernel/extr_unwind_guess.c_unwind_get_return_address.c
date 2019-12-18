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
struct unwind_state {int /*<<< orphan*/ * sp; int /*<<< orphan*/  graph_idx; int /*<<< orphan*/  task; } ;

/* Variables and functions */
 unsigned long READ_ONCE_NOCHECK (int /*<<< orphan*/ ) ; 
 unsigned long ftrace_graph_ret_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ *) ; 
 scalar_t__ unwind_done (struct unwind_state*) ; 

unsigned long unwind_get_return_address(struct unwind_state *state)
{
	unsigned long addr;

	if (unwind_done(state))
		return 0;

	addr = READ_ONCE_NOCHECK(*state->sp);

	return ftrace_graph_ret_addr(state->task, &state->graph_idx,
				     addr, state->sp);
}
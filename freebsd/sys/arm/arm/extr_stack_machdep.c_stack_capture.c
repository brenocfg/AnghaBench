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
struct unwind_state {int /*<<< orphan*/ * registers; } ;
struct stack {int dummy; } ;

/* Variables and functions */
 size_t PC ; 
 int stack_put (struct stack*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stack_zero (struct stack*) ; 
 scalar_t__ unwind_stack_one (struct unwind_state*,int) ; 

__attribute__((used)) static void
stack_capture(struct stack *st, struct unwind_state *state)
{

	stack_zero(st);
	while (unwind_stack_one(state, 1) == 0) {
		if (stack_put(st, state->registers[PC]) == -1)
			break;
	}
}
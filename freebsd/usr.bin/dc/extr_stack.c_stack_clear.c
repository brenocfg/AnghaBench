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
struct stack {scalar_t__ sp; int /*<<< orphan*/ * stack; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stack_free_value (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stack_init (struct stack*) ; 

void
stack_clear(struct stack *stack)
{

	while (stack->sp >= 0)
		stack_free_value(&stack->stack[stack->sp--]);
	free(stack->stack);
	stack_init(stack);
}
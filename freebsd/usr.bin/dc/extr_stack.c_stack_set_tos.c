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
struct value {int /*<<< orphan*/ * array; } ;
struct stack {int sp; struct value* stack; } ;

/* Variables and functions */
 int /*<<< orphan*/ * array_dup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stack_free_value (struct value*) ; 
 int /*<<< orphan*/  stack_push (struct stack*,struct value*) ; 

void
stack_set_tos(struct stack *stack, struct value *v)
{

	if (stack->sp == -1)
		stack_push(stack, v);
	else {
		stack_free_value(&stack->stack[stack->sp]);
		stack->stack[stack->sp] = *v;
		stack->stack[stack->sp].array = v->array == NULL ?
		    NULL : array_dup(v->array);
	}
}
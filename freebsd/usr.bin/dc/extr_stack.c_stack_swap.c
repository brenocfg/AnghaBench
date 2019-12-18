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
struct value {int dummy; } ;
struct stack {int sp; struct value* stack; } ;

/* Variables and functions */
 int /*<<< orphan*/  warnx (char*) ; 

void
stack_swap(struct stack *stack)
{
	struct value copy;

	if (stack->sp < 1) {
		warnx("stack empty");
		return;
	}
	copy = stack->stack[stack->sp];
	stack->stack[stack->sp] = stack->stack[stack->sp-1];
	stack->stack[stack->sp-1] = copy;
}
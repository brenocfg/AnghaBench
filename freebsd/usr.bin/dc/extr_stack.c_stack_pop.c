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
struct stack {int /*<<< orphan*/  sp; struct value* stack; } ;

/* Variables and functions */
 scalar_t__ stack_empty (struct stack*) ; 

struct value *
stack_pop(struct stack *stack)
{

	if (stack_empty(stack))
		return (NULL);
	return &stack->stack[stack->sp--];
}
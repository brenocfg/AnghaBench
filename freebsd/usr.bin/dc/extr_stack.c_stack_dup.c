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
struct stack {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  stack_dup_value (struct value*,struct value*) ; 
 int /*<<< orphan*/  stack_push (struct stack*,int /*<<< orphan*/ ) ; 
 struct value* stack_tos (struct stack*) ; 
 int /*<<< orphan*/  warnx (char*) ; 

void
stack_dup(struct stack *stack)
{
	struct value *value;
	struct value copy;

	value = stack_tos(stack);
	if (value == NULL) {
		warnx("stack empty");
		return;
	}
	stack_push(stack, stack_dup_value(value, &copy));
}
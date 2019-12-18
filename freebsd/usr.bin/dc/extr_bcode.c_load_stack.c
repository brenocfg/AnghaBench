#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct value {int dummy; } ;
struct stack {int dummy; } ;
struct TYPE_2__ {struct stack* reg; } ;

/* Variables and functions */
 TYPE_1__ bmachine ; 
 int /*<<< orphan*/  push (struct value*) ; 
 int readreg () ; 
 struct value* stack_pop (struct stack*) ; 
 scalar_t__ stack_size (struct stack*) ; 
 int /*<<< orphan*/  warnx (char*,int,int) ; 

__attribute__((used)) static void
load_stack(void)
{
	struct stack *stack;
	struct value *value;
	int idx;

	idx = readreg();
	if (idx >= 0) {
		stack = &bmachine.reg[idx];
		value = NULL;
		if (stack_size(stack) > 0) {
			value = stack_pop(stack);
		}
		if (value != NULL)
			push(value);
		else
			warnx("stack register '%c' (0%o) is empty",
			    idx, idx);
	}
}
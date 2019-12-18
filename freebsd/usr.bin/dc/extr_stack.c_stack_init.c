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
struct stack {int sp; int /*<<< orphan*/ * stack; scalar_t__ size; } ;

/* Variables and functions */

void
stack_init(struct stack *stack)
{

	stack->size = 0;
	stack->sp = -1;
	stack->stack = NULL;
}
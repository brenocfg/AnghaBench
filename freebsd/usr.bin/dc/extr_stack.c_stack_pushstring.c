#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct stack {size_t sp; TYPE_2__* stack; } ;
struct TYPE_3__ {char* string; } ;
struct TYPE_4__ {int /*<<< orphan*/ * array; TYPE_1__ u; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCODE_STRING ; 
 int /*<<< orphan*/  stack_grow (struct stack*) ; 

void
stack_pushstring(struct stack *stack, char *string)
{

	stack_grow(stack);
	stack->stack[stack->sp].type = BCODE_STRING;
	stack->stack[stack->sp].u.string = string;
	stack->stack[stack->sp].array = NULL;
}
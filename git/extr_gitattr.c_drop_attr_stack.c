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
struct attr_stack {struct attr_stack* prev; } ;

/* Variables and functions */
 int /*<<< orphan*/  attr_stack_free (struct attr_stack*) ; 

__attribute__((used)) static void drop_attr_stack(struct attr_stack **stack)
{
	while (*stack) {
		struct attr_stack *elem = *stack;
		*stack = elem->prev;
		attr_stack_free(elem);
	}
}
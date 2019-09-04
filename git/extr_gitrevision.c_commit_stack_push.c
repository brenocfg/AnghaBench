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
struct commit_stack {scalar_t__ nr; struct commit** items; int /*<<< orphan*/  alloc; } ;
struct commit {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (struct commit**,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void commit_stack_push(struct commit_stack *stack, struct commit *commit)
{
	ALLOC_GROW(stack->items, stack->nr + 1, stack->alloc);
	stack->items[stack->nr++] = commit;
}
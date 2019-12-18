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
struct commit_stack {scalar_t__ alloc; scalar_t__ nr; int /*<<< orphan*/  items; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE_AND_NULL (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void commit_stack_clear(struct commit_stack *stack)
{
	FREE_AND_NULL(stack->items);
	stack->nr = stack->alloc = 0;
}
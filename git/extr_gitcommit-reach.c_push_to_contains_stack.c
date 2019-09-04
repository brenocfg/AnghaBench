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
struct contains_stack {int nr; TYPE_1__* contains_stack; int /*<<< orphan*/  alloc; } ;
struct commit {int /*<<< orphan*/  parents; } ;
struct TYPE_2__ {int /*<<< orphan*/  parents; struct commit* commit; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (TYPE_1__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void push_to_contains_stack(struct commit *candidate, struct contains_stack *contains_stack)
{
	ALLOC_GROW(contains_stack->contains_stack, contains_stack->nr + 1, contains_stack->alloc);
	contains_stack->contains_stack[contains_stack->nr].commit = candidate;
	contains_stack->contains_stack[contains_stack->nr++].parents = candidate->parents;
}
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
struct ref_formatting_stack {int /*<<< orphan*/  output; struct ref_formatting_stack* prev; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct ref_formatting_stack*) ; 
 int /*<<< orphan*/  strbuf_addbuf (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pop_stack_element(struct ref_formatting_stack **stack)
{
	struct ref_formatting_stack *current = *stack;
	struct ref_formatting_stack *prev = current->prev;

	if (prev)
		strbuf_addbuf(&prev->output, &current->output);
	strbuf_release(&current->output);
	free(current);
	*stack = prev;
}
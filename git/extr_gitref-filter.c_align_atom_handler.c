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
struct strbuf {int dummy; } ;
struct ref_formatting_state {struct ref_formatting_stack* stack; } ;
struct ref_formatting_stack {int /*<<< orphan*/ * at_end_data; int /*<<< orphan*/  at_end; } ;
struct atom_value {TYPE_2__* atom; } ;
struct TYPE_3__ {int /*<<< orphan*/  align; } ;
struct TYPE_4__ {TYPE_1__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  end_align_handler ; 
 int /*<<< orphan*/  push_stack_element (struct ref_formatting_stack**) ; 

__attribute__((used)) static int align_atom_handler(struct atom_value *atomv, struct ref_formatting_state *state,
			      struct strbuf *unused_err)
{
	struct ref_formatting_stack *new_stack;

	push_stack_element(&state->stack);
	new_stack = state->stack;
	new_stack->at_end = end_align_handler;
	new_stack->at_end_data = &atomv->atom->u.align;
	return 0;
}
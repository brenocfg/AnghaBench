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
struct strbuf {int dummy; } ;
struct ref_formatting_state {struct ref_formatting_stack* stack; } ;
struct ref_formatting_stack {scalar_t__ at_end; scalar_t__ at_end_data; } ;
struct if_then_else {int else_atom_seen; int /*<<< orphan*/  then_atom_seen; } ;
struct atom_value {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ if_then_else_handler ; 
 int /*<<< orphan*/  push_stack_element (struct ref_formatting_stack**) ; 
 int strbuf_addf_ret (struct strbuf*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int else_atom_handler(struct atom_value *atomv, struct ref_formatting_state *state,
			     struct strbuf *err)
{
	struct ref_formatting_stack *prev = state->stack;
	struct if_then_else *if_then_else = NULL;

	if (prev->at_end == if_then_else_handler)
		if_then_else = (struct if_then_else *)prev->at_end_data;
	if (!if_then_else)
		return strbuf_addf_ret(err, -1, _("format: %%(else) atom used without an %%(if) atom"));
	if (!if_then_else->then_atom_seen)
		return strbuf_addf_ret(err, -1, _("format: %%(else) atom used without a %%(then) atom"));
	if (if_then_else->else_atom_seen)
		return strbuf_addf_ret(err, -1, _("format: %%(else) atom used more than once"));
	if_then_else->else_atom_seen = 1;
	push_stack_element(&state->stack);
	state->stack->at_end_data = prev->at_end_data;
	state->stack->at_end = prev->at_end;
	return 0;
}
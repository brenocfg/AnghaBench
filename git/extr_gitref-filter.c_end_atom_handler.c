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
struct ref_formatting_state {struct ref_formatting_stack* stack; int /*<<< orphan*/  quote_style; } ;
struct TYPE_4__ {int /*<<< orphan*/  buf; } ;
struct ref_formatting_stack {TYPE_2__ output; TYPE_1__* prev; int /*<<< orphan*/  (* at_end ) (struct ref_formatting_stack**) ;} ;
struct atom_value {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  prev; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  pop_stack_element (struct ref_formatting_stack**) ; 
 int /*<<< orphan*/  quote_formatting (struct strbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strbuf_addf_ret (struct strbuf*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_swap (TYPE_2__*,struct strbuf*) ; 
 int /*<<< orphan*/  stub1 (struct ref_formatting_stack**) ; 

__attribute__((used)) static int end_atom_handler(struct atom_value *atomv, struct ref_formatting_state *state,
			    struct strbuf *err)
{
	struct ref_formatting_stack *current = state->stack;
	struct strbuf s = STRBUF_INIT;

	if (!current->at_end)
		return strbuf_addf_ret(err, -1, _("format: %%(end) atom used without corresponding atom"));
	current->at_end(&state->stack);

	/*  Stack may have been popped within at_end(), hence reset the current pointer */
	current = state->stack;

	/*
	 * Perform quote formatting when the stack element is that of
	 * a supporting atom. If nested then perform quote formatting
	 * only on the topmost supporting atom.
	 */
	if (!current->prev->prev) {
		quote_formatting(&s, current->output.buf, state->quote_style);
		strbuf_swap(&current->output, &s);
	}
	strbuf_release(&s);
	pop_stack_element(&state->stack);
	return 0;
}
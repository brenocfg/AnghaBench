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
struct strbuf {int dummy; } ;
struct ref_formatting_state {TYPE_1__* stack; int /*<<< orphan*/  quote_style; } ;
struct atom_value {int /*<<< orphan*/  s; } ;
struct TYPE_2__ {int /*<<< orphan*/  output; int /*<<< orphan*/  prev; } ;

/* Variables and functions */
 int /*<<< orphan*/  quote_formatting (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int append_atom(struct atom_value *v, struct ref_formatting_state *state,
		       struct strbuf *unused_err)
{
	/*
	 * Quote formatting is only done when the stack has a single
	 * element. Otherwise quote formatting is done on the
	 * element's entire output strbuf when the %(end) atom is
	 * encountered.
	 */
	if (!state->stack->prev)
		quote_formatting(&state->stack->output, v->s, state->quote_style);
	else
		strbuf_addstr(&state->stack->output, v->s);
	return 0;
}
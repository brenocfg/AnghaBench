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
struct option {struct apply_state* value; } ;
struct apply_state {int /*<<< orphan*/  root; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON_OPT_NEG (int) ; 
 int /*<<< orphan*/  strbuf_addstr (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  strbuf_complete (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  strbuf_reset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int apply_option_parse_directory(const struct option *opt,
					const char *arg, int unset)
{
	struct apply_state *state = opt->value;

	BUG_ON_OPT_NEG(unset);

	strbuf_reset(&state->root);
	strbuf_addstr(&state->root, arg);
	strbuf_complete(&state->root, '/');
	return 0;
}
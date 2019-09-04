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
struct apply_state {int /*<<< orphan*/  ws_ignore_action; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON_OPT_ARG (char const*) ; 
 int /*<<< orphan*/  ignore_ws_change ; 
 int /*<<< orphan*/  ignore_ws_none ; 

__attribute__((used)) static int apply_option_parse_space_change(const struct option *opt,
					   const char *arg, int unset)
{
	struct apply_state *state = opt->value;

	BUG_ON_OPT_ARG(arg);

	if (unset)
		state->ws_ignore_action = ignore_ws_none;
	else
		state->ws_ignore_action = ignore_ws_change;
	return 0;
}
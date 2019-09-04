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
struct apply_state {int /*<<< orphan*/  ws_ignore_action; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int error (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  ignore_ws_change ; 
 int /*<<< orphan*/  ignore_ws_none ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int parse_ignorewhitespace_option(struct apply_state *state,
						 const char *option)
{
	if (!option || !strcmp(option, "no") ||
	    !strcmp(option, "false") || !strcmp(option, "never") ||
	    !strcmp(option, "none")) {
		state->ws_ignore_action = ignore_ws_none;
		return 0;
	}
	if (!strcmp(option, "change")) {
		state->ws_ignore_action = ignore_ws_change;
		return 0;
	}
	return error(_("unrecognized whitespace ignore option '%s'"), option);
}
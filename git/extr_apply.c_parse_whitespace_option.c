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
struct apply_state {void* ws_error_action; scalar_t__ squelch_whitespace_errors; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 void* correct_ws_error ; 
 void* die_on_ws_error ; 
 int error (int /*<<< orphan*/ ,char const*) ; 
 void* nowarn_ws_error ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 void* warn_on_ws_error ; 

__attribute__((used)) static int parse_whitespace_option(struct apply_state *state, const char *option)
{
	if (!option) {
		state->ws_error_action = warn_on_ws_error;
		return 0;
	}
	if (!strcmp(option, "warn")) {
		state->ws_error_action = warn_on_ws_error;
		return 0;
	}
	if (!strcmp(option, "nowarn")) {
		state->ws_error_action = nowarn_ws_error;
		return 0;
	}
	if (!strcmp(option, "error")) {
		state->ws_error_action = die_on_ws_error;
		return 0;
	}
	if (!strcmp(option, "error-all")) {
		state->ws_error_action = die_on_ws_error;
		state->squelch_whitespace_errors = 0;
		return 0;
	}
	if (!strcmp(option, "strip") || !strcmp(option, "fix")) {
		state->ws_error_action = correct_ws_error;
		return 0;
	}
	/*
	 * Please update $__git_whitespacelist in git-completion.bash
	 * when you add new options.
	 */
	return error(_("unrecognized whitespace option '%s'"), option);
}
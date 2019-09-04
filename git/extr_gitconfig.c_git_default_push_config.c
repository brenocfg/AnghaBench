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

/* Variables and functions */
 int /*<<< orphan*/  PUSH_DEFAULT_CURRENT ; 
 int /*<<< orphan*/  PUSH_DEFAULT_MATCHING ; 
 int /*<<< orphan*/  PUSH_DEFAULT_NOTHING ; 
 int /*<<< orphan*/  PUSH_DEFAULT_SIMPLE ; 
 int /*<<< orphan*/  PUSH_DEFAULT_UPSTREAM ; 
 int /*<<< orphan*/  _ (char*) ; 
 int config_error_nonbool (char const*) ; 
 int error (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  push_default ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int git_default_push_config(const char *var, const char *value)
{
	if (!strcmp(var, "push.default")) {
		if (!value)
			return config_error_nonbool(var);
		else if (!strcmp(value, "nothing"))
			push_default = PUSH_DEFAULT_NOTHING;
		else if (!strcmp(value, "matching"))
			push_default = PUSH_DEFAULT_MATCHING;
		else if (!strcmp(value, "simple"))
			push_default = PUSH_DEFAULT_SIMPLE;
		else if (!strcmp(value, "upstream"))
			push_default = PUSH_DEFAULT_UPSTREAM;
		else if (!strcmp(value, "tracking")) /* deprecated */
			push_default = PUSH_DEFAULT_UPSTREAM;
		else if (!strcmp(value, "current"))
			push_default = PUSH_DEFAULT_CURRENT;
		else {
			error(_("malformed value for %s: %s"), var, value);
			return error(_("must be one of nothing, matching, simple, "
				       "upstream or current"));
		}
		return 0;
	}

	/* Add other config variables here and to Documentation/config.txt. */
	return 0;
}
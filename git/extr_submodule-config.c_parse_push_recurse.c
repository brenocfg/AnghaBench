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
 int RECURSE_SUBMODULES_CHECK ; 
 int RECURSE_SUBMODULES_ERROR ; 
 int RECURSE_SUBMODULES_OFF ; 
 int RECURSE_SUBMODULES_ONLY ; 
 int RECURSE_SUBMODULES_ON_DEMAND ; 
 int /*<<< orphan*/  die (char*,char const*,char const*) ; 
 int git_parse_maybe_bool (char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int parse_push_recurse(const char *opt, const char *arg,
			       int die_on_error)
{
	switch (git_parse_maybe_bool(arg)) {
	case 1:
		/* There's no simple "on" value when pushing */
		if (die_on_error)
			die("bad %s argument: %s", opt, arg);
		else
			return RECURSE_SUBMODULES_ERROR;
	case 0:
		return RECURSE_SUBMODULES_OFF;
	default:
		if (!strcmp(arg, "on-demand"))
			return RECURSE_SUBMODULES_ON_DEMAND;
		else if (!strcmp(arg, "check"))
			return RECURSE_SUBMODULES_CHECK;
		else if (!strcmp(arg, "only"))
			return RECURSE_SUBMODULES_ONLY;
		/*
		 * Please update $__git_push_recurse_submodules in
		 * git-completion.bash when you add new modes.
		 */
		else if (die_on_error)
			die("bad %s argument: %s", opt, arg);
		else
			return RECURSE_SUBMODULES_ERROR;
	}
}
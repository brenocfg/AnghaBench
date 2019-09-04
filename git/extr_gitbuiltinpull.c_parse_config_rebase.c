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
typedef  enum rebase_type { ____Placeholder_rebase_type } rebase_type ;

/* Variables and functions */
 int REBASE_FALSE ; 
 int REBASE_INTERACTIVE ; 
 int REBASE_INVALID ; 
 int REBASE_MERGES ; 
 int REBASE_PRESERVE ; 
 int REBASE_TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,char const*,char const*) ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ,char const*,char const*) ; 
 int git_parse_maybe_bool (char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static enum rebase_type parse_config_rebase(const char *key, const char *value,
		int fatal)
{
	int v = git_parse_maybe_bool(value);

	if (!v)
		return REBASE_FALSE;
	else if (v > 0)
		return REBASE_TRUE;
	else if (!strcmp(value, "preserve") || !strcmp(value, "p"))
		return REBASE_PRESERVE;
	else if (!strcmp(value, "merges") || !strcmp(value, "m"))
		return REBASE_MERGES;
	else if (!strcmp(value, "interactive") || !strcmp(value, "i"))
		return REBASE_INTERACTIVE;
	/*
	 * Please update _git_config() in git-completion.bash when you
	 * add new rebase modes.
	 */

	if (fatal)
		die(_("Invalid value for %s: %s"), key, value);
	else
		error(_("Invalid value for %s: %s"), key, value);

	return REBASE_INVALID;
}
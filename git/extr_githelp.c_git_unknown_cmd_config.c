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
 int /*<<< orphan*/  add_cmdname (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aliases ; 
 int /*<<< orphan*/  autocorrect ; 
 int /*<<< orphan*/  git_config_int (char const*,char const*) ; 
 int git_default_config (char const*,char const*,void*) ; 
 scalar_t__ skip_prefix (char const*,char*,char const**) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static int git_unknown_cmd_config(const char *var, const char *value, void *cb)
{
	const char *p;

	if (!strcmp(var, "help.autocorrect"))
		autocorrect = git_config_int(var,value);
	/* Also use aliases for command lookup */
	if (skip_prefix(var, "alias.", &p))
		add_cmdname(&aliases, p, strlen(p));

	return git_default_config(var, value, cb);
}
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
 scalar_t__ XDL_MERGE_DIFF3 ; 
 int /*<<< orphan*/  die (char*,char const*,...) ; 
 int git_default_config (char const*,char const*,void*) ; 
 scalar_t__ git_xmerge_style ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

int git_xmerge_config(const char *var, const char *value, void *cb)
{
	if (!strcmp(var, "merge.conflictstyle")) {
		if (!value)
			die("'%s' is not a boolean", var);
		if (!strcmp(value, "diff3"))
			git_xmerge_style = XDL_MERGE_DIFF3;
		else if (!strcmp(value, "merge"))
			git_xmerge_style = 0;
		/*
		 * Please update _git_checkout() in
		 * git-completion.bash when you add new merge config
		 */
		else
			die("unknown style '%s' given for '%s'",
			    value, var);
		return 0;
	}
	return git_default_config(var, value, cb);
}
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
 int /*<<< orphan*/  diff_indent_heuristic ; 
 int /*<<< orphan*/  git_config_bool (char const*,char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

int git_diff_heuristic_config(const char *var, const char *value, void *cb)
{
	if (!strcmp(var, "diff.indentheuristic"))
		diff_indent_heuristic = git_config_bool(var, value);
	return 0;
}
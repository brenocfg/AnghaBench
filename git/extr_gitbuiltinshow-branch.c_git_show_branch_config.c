#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  argc; } ;

/* Variables and functions */
 int /*<<< orphan*/  argv_array_push (TYPE_1__*,char const*) ; 
 int config_error_nonbool (char const*) ; 
 TYPE_1__ default_args ; 
 int git_color_default_config (char const*,char const*,void*) ; 
 int /*<<< orphan*/  git_config_colorbool (char const*,char const*) ; 
 int /*<<< orphan*/  showbranch_use_color ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int git_show_branch_config(const char *var, const char *value, void *cb)
{
	if (!strcmp(var, "showbranch.default")) {
		if (!value)
			return config_error_nonbool(var);
		/*
		 * default_arg is now passed to parse_options(), so we need to
		 * mimic the real argv a bit better.
		 */
		if (!default_args.argc)
			argv_array_push(&default_args, "show-branch");
		argv_array_push(&default_args, value);
		return 0;
	}

	if (!strcmp(var, "color.showbranch")) {
		showbranch_use_color = git_config_colorbool(var, value);
		return 0;
	}

	return git_color_default_config(var, value, cb);
}
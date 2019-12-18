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
struct checkout_opts {int /*<<< orphan*/  diff_options; } ;

/* Variables and functions */
 int git_default_submodule_config (char const*,char const*,int /*<<< orphan*/ *) ; 
 int git_xmerge_config (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  handle_ignore_submodules_arg (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ starts_with (char const*,char*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int git_checkout_config(const char *var, const char *value, void *cb)
{
	if (!strcmp(var, "diff.ignoresubmodules")) {
		struct checkout_opts *opts = cb;
		handle_ignore_submodules_arg(&opts->diff_options, value);
		return 0;
	}

	if (starts_with(var, "submodule."))
		return git_default_submodule_config(var, value, NULL);

	return git_xmerge_config(var, value, NULL);
}
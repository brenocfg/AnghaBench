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
struct pathspec {int dummy; } ;
struct option {int dummy; } ;
struct module_list {int dummy; } ;
struct init_cb {char const* prefix; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 struct init_cb INIT_CB_INIT ; 
 struct module_list MODULE_LIST_INIT ; 
 char const* N_ (char*) ; 
 struct option OPT_END () ; 
 int /*<<< orphan*/  OPT_QUIET ; 
 struct option OPT__QUIET (int*,char const*) ; 
 int /*<<< orphan*/  for_each_listed_submodule (struct module_list*,int /*<<< orphan*/ ,struct init_cb*) ; 
 scalar_t__ git_config_get_value_multi (char*) ; 
 int /*<<< orphan*/  init_submodule_cb ; 
 int /*<<< orphan*/  module_list_active (struct module_list*) ; 
 scalar_t__ module_list_compute (int,char const**,char const*,struct pathspec*,struct module_list*) ; 
 int parse_options (int,char const**,char const*,struct option*,char const* const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int module_init(int argc, const char **argv, const char *prefix)
{
	struct init_cb info = INIT_CB_INIT;
	struct pathspec pathspec;
	struct module_list list = MODULE_LIST_INIT;
	int quiet = 0;

	struct option module_init_options[] = {
		OPT__QUIET(&quiet, N_("Suppress output for initializing a submodule")),
		OPT_END()
	};

	const char *const git_submodule_helper_usage[] = {
		N_("git submodule--helper init [<options>] [<path>]"),
		NULL
	};

	argc = parse_options(argc, argv, prefix, module_init_options,
			     git_submodule_helper_usage, 0);

	if (module_list_compute(argc, argv, prefix, &pathspec, &list) < 0)
		return 1;

	/*
	 * If there are no path args and submodule.active is set then,
	 * by default, only initialize 'active' modules.
	 */
	if (!argc && git_config_get_value_multi("submodule.active"))
		module_list_active(&list);

	info.prefix = prefix;
	if (quiet)
		info.flags |= OPT_QUIET;

	for_each_listed_submodule(&list, init_submodule_cb, &info);

	return 0;
}
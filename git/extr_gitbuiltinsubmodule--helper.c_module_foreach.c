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
struct cb_foreach {int argc; char const** argv; char const* prefix; int /*<<< orphan*/  recursive; int /*<<< orphan*/  quiet; } ;

/* Variables and functions */
 struct cb_foreach CB_FOREACH_INIT ; 
 struct module_list MODULE_LIST_INIT ; 
 char const* N_ (char*) ; 
 struct option OPT_BOOL (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,char const*) ; 
 struct option OPT_END () ; 
 struct option OPT__QUIET (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  for_each_listed_submodule (struct module_list*,int /*<<< orphan*/ ,struct cb_foreach*) ; 
 scalar_t__ module_list_compute (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,struct pathspec*,struct module_list*) ; 
 int parse_options (int,char const**,char const*,struct option*,char const* const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  runcommand_in_submodule_cb ; 

__attribute__((used)) static int module_foreach(int argc, const char **argv, const char *prefix)
{
	struct cb_foreach info = CB_FOREACH_INIT;
	struct pathspec pathspec;
	struct module_list list = MODULE_LIST_INIT;

	struct option module_foreach_options[] = {
		OPT__QUIET(&info.quiet, N_("Suppress output of entering each submodule command")),
		OPT_BOOL(0, "recursive", &info.recursive,
			 N_("Recurse into nested submodules")),
		OPT_END()
	};

	const char *const git_submodule_helper_usage[] = {
		N_("git submodule--helper foreach [--quiet] [--recursive] [--] <command>"),
		NULL
	};

	argc = parse_options(argc, argv, prefix, module_foreach_options,
			     git_submodule_helper_usage, 0);

	if (module_list_compute(0, NULL, prefix, &pathspec, &list) < 0)
		return 1;

	info.argc = argc;
	info.argv = argv;
	info.prefix = prefix;

	for_each_listed_submodule(&list, runcommand_in_submodule_cb, &info);

	return 0;
}
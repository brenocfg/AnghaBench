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
struct deinit_cb {char const* prefix; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 struct deinit_cb DEINIT_CB_INIT ; 
 struct module_list MODULE_LIST_INIT ; 
 char const* N_ (char*) ; 
 struct option OPT_BOOL (int /*<<< orphan*/ ,char*,int*,char const*) ; 
 struct option OPT_END () ; 
 int /*<<< orphan*/  OPT_FORCE ; 
 int /*<<< orphan*/  OPT_QUIET ; 
 struct option OPT__FORCE (int*,char const*,int /*<<< orphan*/ ) ; 
 struct option OPT__QUIET (int*,char const*) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  deinit_submodule_cb ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  for_each_listed_submodule (struct module_list*,int /*<<< orphan*/ ,struct deinit_cb*) ; 
 scalar_t__ module_list_compute (int,char const**,char const*,struct pathspec*,struct module_list*) ; 
 int parse_options (int,char const**,char const*,struct option*,char const* const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage_with_options (char const* const*,struct option*) ; 

__attribute__((used)) static int module_deinit(int argc, const char **argv, const char *prefix)
{
	struct deinit_cb info = DEINIT_CB_INIT;
	struct pathspec pathspec;
	struct module_list list = MODULE_LIST_INIT;
	int quiet = 0;
	int force = 0;
	int all = 0;

	struct option module_deinit_options[] = {
		OPT__QUIET(&quiet, N_("Suppress submodule status output")),
		OPT__FORCE(&force, N_("Remove submodule working trees even if they contain local changes"), 0),
		OPT_BOOL(0, "all", &all, N_("Unregister all submodules")),
		OPT_END()
	};

	const char *const git_submodule_helper_usage[] = {
		N_("git submodule deinit [--quiet] [-f | --force] [--all | [--] [<path>...]]"),
		NULL
	};

	argc = parse_options(argc, argv, prefix, module_deinit_options,
			     git_submodule_helper_usage, 0);

	if (all && argc) {
		error("pathspec and --all are incompatible");
		usage_with_options(git_submodule_helper_usage,
				   module_deinit_options);
	}

	if (!argc && !all)
		die(_("Use '--all' if you really want to deinitialize all submodules"));

	if (module_list_compute(argc, argv, prefix, &pathspec, &list) < 0)
		return 1;

	info.prefix = prefix;
	if (quiet)
		info.flags |= OPT_QUIET;
	if (force)
		info.flags |= OPT_FORCE;

	for_each_listed_submodule(&list, deinit_submodule_cb, &info);

	return 0;
}
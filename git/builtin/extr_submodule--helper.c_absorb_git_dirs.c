#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pathspec {int dummy; } ;
struct option {int dummy; } ;
struct module_list {int nr; TYPE_1__** entries; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 unsigned int ABSORB_GITDIR_RECURSE_SUBMODULES ; 
 struct module_list MODULE_LIST_INIT ; 
 char const* N_ (char*) ; 
 struct option OPT_BIT (int /*<<< orphan*/ ,char*,unsigned int*,char const*,unsigned int) ; 
 struct option OPT_END () ; 
 struct option OPT_STRING (int /*<<< orphan*/ ,char*,char const**,char const*,char const*) ; 
 int /*<<< orphan*/  absorb_git_dir_into_superproject (int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ module_list_compute (int,char const**,char const*,struct pathspec*,struct module_list*) ; 
 int parse_options (int,char const**,char const*,struct option*,char const* const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int absorb_git_dirs(int argc, const char **argv, const char *prefix)
{
	int i;
	struct pathspec pathspec;
	struct module_list list = MODULE_LIST_INIT;
	unsigned flags = ABSORB_GITDIR_RECURSE_SUBMODULES;

	struct option embed_gitdir_options[] = {
		OPT_STRING(0, "prefix", &prefix,
			   N_("path"),
			   N_("path into the working tree")),
		OPT_BIT(0, "--recursive", &flags, N_("recurse into submodules"),
			ABSORB_GITDIR_RECURSE_SUBMODULES),
		OPT_END()
	};

	const char *const git_submodule_helper_usage[] = {
		N_("git submodule--helper absorb-git-dirs [<options>] [<path>...]"),
		NULL
	};

	argc = parse_options(argc, argv, prefix, embed_gitdir_options,
			     git_submodule_helper_usage, 0);

	if (module_list_compute(argc, argv, prefix, &pathspec, &list) < 0)
		return 1;

	for (i = 0; i < list.nr; i++)
		absorb_git_dir_into_superproject(list.entries[i]->name, flags);

	return 0;
}
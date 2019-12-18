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
struct submodule_update_clone {char const* recursive_prefix; char const* depth; char const* prefix; int warn_if_uninitialized; int /*<<< orphan*/  list; int /*<<< orphan*/  update; int /*<<< orphan*/  max_jobs; int /*<<< orphan*/  progress; int /*<<< orphan*/  quiet; int /*<<< orphan*/  recommend_shallow; int /*<<< orphan*/  dissociate; int /*<<< orphan*/  references; } ;
struct pathspec {scalar_t__ nr; } ;
struct option {int dummy; } ;

/* Variables and functions */
 char const* N_ (char*) ; 
 struct option OPT_BOOL (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,char const*) ; 
 struct option OPT_END () ; 
 struct option OPT_INTEGER (char,char*,int /*<<< orphan*/ *,char const*) ; 
 struct option OPT_STRING (int /*<<< orphan*/ ,char*,char const**,char*,char const*) ; 
 struct option OPT_STRING_LIST (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,char const*,char const*) ; 
 struct option OPT__QUIET (int /*<<< orphan*/ *,char const*) ; 
 struct submodule_update_clone SUBMODULE_UPDATE_CLONE_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_update_clone_config ; 
 scalar_t__ module_list_compute (int,char const**,char const*,struct pathspec*,int /*<<< orphan*/ *) ; 
 int parse_options (int,char const**,char const*,struct option*,char const* const*,int /*<<< orphan*/ ) ; 
 scalar_t__ parse_submodule_update_strategy (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_clone_config_from_gitmodules (int /*<<< orphan*/ *) ; 
 int update_submodules (struct submodule_update_clone*) ; 

__attribute__((used)) static int update_clone(int argc, const char **argv, const char *prefix)
{
	const char *update = NULL;
	struct pathspec pathspec;
	struct submodule_update_clone suc = SUBMODULE_UPDATE_CLONE_INIT;

	struct option module_update_clone_options[] = {
		OPT_STRING(0, "prefix", &prefix,
			   N_("path"),
			   N_("path into the working tree")),
		OPT_STRING(0, "recursive-prefix", &suc.recursive_prefix,
			   N_("path"),
			   N_("path into the working tree, across nested "
			      "submodule boundaries")),
		OPT_STRING(0, "update", &update,
			   N_("string"),
			   N_("rebase, merge, checkout or none")),
		OPT_STRING_LIST(0, "reference", &suc.references, N_("repo"),
			   N_("reference repository")),
		OPT_BOOL(0, "dissociate", &suc.dissociate,
			   N_("use --reference only while cloning")),
		OPT_STRING(0, "depth", &suc.depth, "<depth>",
			   N_("Create a shallow clone truncated to the "
			      "specified number of revisions")),
		OPT_INTEGER('j', "jobs", &suc.max_jobs,
			    N_("parallel jobs")),
		OPT_BOOL(0, "recommend-shallow", &suc.recommend_shallow,
			    N_("whether the initial clone should follow the shallow recommendation")),
		OPT__QUIET(&suc.quiet, N_("don't print cloning progress")),
		OPT_BOOL(0, "progress", &suc.progress,
			    N_("force cloning progress")),
		OPT_END()
	};

	const char *const git_submodule_helper_usage[] = {
		N_("git submodule--helper update-clone [--prefix=<path>] [<path>...]"),
		NULL
	};
	suc.prefix = prefix;

	update_clone_config_from_gitmodules(&suc.max_jobs);
	git_config(git_update_clone_config, &suc.max_jobs);

	argc = parse_options(argc, argv, prefix, module_update_clone_options,
			     git_submodule_helper_usage, 0);

	if (update)
		if (parse_submodule_update_strategy(update, &suc.update) < 0)
			die(_("bad value for update parameter"));

	if (module_list_compute(argc, argv, prefix, &pathspec, &suc.list) < 0)
		return 1;

	if (pathspec.nr)
		suc.warn_if_uninitialized = 1;

	return update_submodules(&suc);
}
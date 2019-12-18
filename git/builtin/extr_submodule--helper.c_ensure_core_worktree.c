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
struct submodule {int dummy; } ;
struct strbuf {int dummy; } ;
struct repository {int /*<<< orphan*/  gitdir; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 char* absolute_pathdup (char const*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  git_config_set_in_file (char*,char*,char const*) ; 
 int /*<<< orphan*/  null_oid ; 
 char* relative_path (char*,int /*<<< orphan*/ ,struct strbuf*) ; 
 int /*<<< orphan*/  repo_config_get_string (struct repository*,char*,char**) ; 
 char* repo_git_path (struct repository*,char*) ; 
 scalar_t__ repo_submodule_init (struct repository*,int /*<<< orphan*/ ,struct submodule const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 struct submodule* submodule_from_path (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static int ensure_core_worktree(int argc, const char **argv, const char *prefix)
{
	const struct submodule *sub;
	const char *path;
	char *cw;
	struct repository subrepo;

	if (argc != 2)
		BUG("submodule--helper ensure-core-worktree <path>");

	path = argv[1];

	sub = submodule_from_path(the_repository, &null_oid, path);
	if (!sub)
		BUG("We could get the submodule handle before?");

	if (repo_submodule_init(&subrepo, the_repository, sub))
		die(_("could not get a repository handle for submodule '%s'"), path);

	if (!repo_config_get_string(&subrepo, "core.worktree", &cw)) {
		char *cfg_file, *abs_path;
		const char *rel_path;
		struct strbuf sb = STRBUF_INIT;

		cfg_file = repo_git_path(&subrepo, "config");

		abs_path = absolute_pathdup(path);
		rel_path = relative_path(abs_path, subrepo.gitdir, &sb);

		git_config_set_in_file(cfg_file, "core.worktree", rel_path);

		free(cfg_file);
		free(abs_path);
		strbuf_release(&sb);
	}

	return 0;
}
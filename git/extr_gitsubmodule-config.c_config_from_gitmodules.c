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
struct repository {scalar_t__ submodule_prefix; scalar_t__ worktree; } ;
struct object_id {int dummy; } ;
struct git_config_source {char* file; void* blob; int /*<<< orphan*/  member_0; } ;
struct config_options {int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  config_fn_t ;

/* Variables and functions */
 int /*<<< orphan*/  GITMODULES_FILE ; 
 void* GITMODULES_HEAD ; 
 void* GITMODULES_INDEX ; 
 int /*<<< orphan*/  config_with_options (int /*<<< orphan*/ ,void*,struct git_config_source*,struct config_options const*) ; 
 scalar_t__ file_exists (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ get_oid (void*,struct object_id*) ; 
 char* repo_worktree_path (struct repository*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warning (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void config_from_gitmodules(config_fn_t fn, struct repository *repo, void *data)
{
	if (repo->worktree) {
		struct git_config_source config_source = { 0 };
		const struct config_options opts = { 0 };
		struct object_id oid;
		char *file;

		file = repo_worktree_path(repo, GITMODULES_FILE);
		if (file_exists(file)) {
			config_source.file = file;
		} else if (repo->submodule_prefix) {
			/*
			 * When get_oid and config_with_options, used below,
			 * become able to work on a specific repository, this
			 * warning branch can be removed.
			 */
			warning("nested submodules without %s in the working tree are not supported yet",
				GITMODULES_FILE);
			goto out;
		} else if (get_oid(GITMODULES_INDEX, &oid) >= 0) {
			config_source.blob = GITMODULES_INDEX;
		} else if (get_oid(GITMODULES_HEAD, &oid) >= 0) {
			config_source.blob = GITMODULES_HEAD;
		} else {
			goto out;
		}

		config_with_options(fn, data, &config_source, &opts);

out:
		free(file);
	}
}
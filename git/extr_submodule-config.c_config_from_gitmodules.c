#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct repository {TYPE_2__* objects; scalar_t__ worktree; } ;
struct object_id {int dummy; } ;
struct git_config_source {char* file; char* blob; int /*<<< orphan*/  member_0; } ;
struct config_options {int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  config_fn_t ;
struct TYPE_4__ {TYPE_1__* odb; } ;
struct TYPE_3__ {int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int /*<<< orphan*/  GITMODULES_FILE ; 
 int /*<<< orphan*/  GITMODULES_HEAD ; 
 int /*<<< orphan*/  GITMODULES_INDEX ; 
 int /*<<< orphan*/  add_to_alternates_memory (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  config_with_options (int /*<<< orphan*/ ,void*,struct git_config_source*,struct config_options const*) ; 
 scalar_t__ file_exists (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  oid_to_hex (struct object_id*) ; 
 scalar_t__ repo_get_oid (struct repository*,int /*<<< orphan*/ ,struct object_id*) ; 
 char* repo_worktree_path (struct repository*,int /*<<< orphan*/ ) ; 
 struct repository* the_repository ; 
 char* xstrdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void config_from_gitmodules(config_fn_t fn, struct repository *repo, void *data)
{
	if (repo->worktree) {
		struct git_config_source config_source = { 0 };
		const struct config_options opts = { 0 };
		struct object_id oid;
		char *file;
		char *oidstr = NULL;

		file = repo_worktree_path(repo, GITMODULES_FILE);
		if (file_exists(file)) {
			config_source.file = file;
		} else if (repo_get_oid(repo, GITMODULES_INDEX, &oid) >= 0 ||
			   repo_get_oid(repo, GITMODULES_HEAD, &oid) >= 0) {
			config_source.blob = oidstr = xstrdup(oid_to_hex(&oid));
			if (repo != the_repository)
				add_to_alternates_memory(repo->objects->odb->path);
		} else {
			goto out;
		}

		config_with_options(fn, data, &config_source, &opts);

out:
		free(oidstr);
		free(file);
	}
}
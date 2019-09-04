#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ contents; int /*<<< orphan*/  length; } ;
typedef  TYPE_1__ git_vector ;
struct TYPE_8__ {char** strings; int /*<<< orphan*/  count; } ;
typedef  TYPE_2__ git_strarray ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_remote ;

/* Variables and functions */
 TYPE_1__ GIT_VECTOR_INIT ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int ensure_remote_doesnot_exist (int /*<<< orphan*/ *,char const*) ; 
 int ensure_remote_name_is_valid (char const*) ; 
 int /*<<< orphan*/  git_remote_free (int /*<<< orphan*/ *) ; 
 int git_remote_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  git_vector_free (TYPE_1__*) ; 
 int rename_fetch_refspecs (TYPE_1__*,int /*<<< orphan*/ *,char const*) ; 
 int rename_remote_config_section (int /*<<< orphan*/ *,char const*,char const*) ; 
 int rename_remote_references (int /*<<< orphan*/ *,char const*,char const*) ; 
 int update_branch_remote_config_entry (int /*<<< orphan*/ *,char const*,char const*) ; 

int git_remote_rename(git_strarray *out, git_repository *repo, const char *name, const char *new_name)
{
	int error;
	git_vector problem_refspecs = GIT_VECTOR_INIT;
	git_remote *remote = NULL;

	assert(out && repo && name && new_name);

	if ((error = git_remote_lookup(&remote, repo, name)) < 0)
		return error;

	if ((error = ensure_remote_name_is_valid(new_name)) < 0)
		goto cleanup;

	if ((error = ensure_remote_doesnot_exist(repo, new_name)) < 0)
		goto cleanup;

	if ((error = rename_remote_config_section(repo, name, new_name)) < 0)
		goto cleanup;

	if ((error = update_branch_remote_config_entry(repo, name, new_name)) < 0)
		goto cleanup;

	if ((error = rename_remote_references(repo, name, new_name)) < 0)
		goto cleanup;

	if ((error = rename_fetch_refspecs(&problem_refspecs, remote, new_name)) < 0)
		goto cleanup;

	out->count = problem_refspecs.length;
	out->strings = (char **) problem_refspecs.contents;

cleanup:
	if (error < 0)
		git_vector_free(&problem_refspecs);

	git_remote_free(remote);
	return error;
}
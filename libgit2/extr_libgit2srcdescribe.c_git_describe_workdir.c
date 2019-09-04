#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_status_options ;
typedef  int /*<<< orphan*/  git_status_list ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_object ;
struct TYPE_5__ {int dirty; } ;
typedef  TYPE_1__ git_describe_result ;
typedef  int /*<<< orphan*/  git_describe_options ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_HEAD_FILE ; 
 int /*<<< orphan*/  GIT_OBJECT_COMMIT ; 
 int /*<<< orphan*/  GIT_STATUS_OPTIONS_INIT ; 
 int git_describe_commit (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_describe_result_free (TYPE_1__*) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int git_object_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int git_reference_name_to_id (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ git_status_list_entrycount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_status_list_free (int /*<<< orphan*/ *) ; 
 int git_status_list_new (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int git_describe_workdir(
	git_describe_result **out,
	git_repository *repo,
	git_describe_options *opts)
{
	int error;
	git_oid current_id;
	git_status_list *status = NULL;
	git_status_options status_opts = GIT_STATUS_OPTIONS_INIT;
	git_describe_result *result = NULL;
	git_object *commit;

	if ((error = git_reference_name_to_id(&current_id, repo, GIT_HEAD_FILE)) < 0)
		return error;

	if ((error = git_object_lookup(&commit, repo, &current_id, GIT_OBJECT_COMMIT)) < 0)
		return error;

	/* The first step is to perform a describe of HEAD, so we can leverage this */
	if ((error = git_describe_commit(&result, commit, opts)) < 0)
		goto out;

	if ((error = git_status_list_new(&status, repo, &status_opts)) < 0)
		goto out;


	if (git_status_list_entrycount(status) > 0)
		result->dirty = 1;

out:
	git_object_free(commit);
	git_status_list_free(status);

	if (error < 0)
		git_describe_result_free(result);
	else
		*out = result;

	return error;
}
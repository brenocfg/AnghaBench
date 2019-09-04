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
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_object ;
typedef  int /*<<< orphan*/  git_annotated_commit ;

/* Variables and functions */
 int GIT_OK ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_annotated_commit_from_ref (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int git_annotated_commit_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_object_id (int /*<<< orphan*/ *) ; 
 int git_reference_dwim (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int git_revparse_single (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*) ; 

int resolve_refish(git_annotated_commit **commit, git_repository *repo, const char *refish)
{
	git_reference *ref;
	git_object *obj;
	int err = 0;

	assert(commit != NULL);

	err = git_reference_dwim(&ref, repo, refish);
	if (err == GIT_OK) {
		git_annotated_commit_from_ref(commit, repo, ref);
		git_reference_free(ref);
		return 0;
	}

	err = git_revparse_single(&obj, repo, refish);
	if (err == GIT_OK) {
		err = git_annotated_commit_lookup(commit, repo, git_object_id(obj));
		git_object_free(obj);
	}

	return err;
}
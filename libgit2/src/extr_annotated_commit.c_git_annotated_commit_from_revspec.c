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
typedef  int /*<<< orphan*/  git_object ;
typedef  int /*<<< orphan*/  git_commit ;
typedef  int /*<<< orphan*/  git_annotated_commit ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_OBJECT_COMMIT ; 
 int annotated_commit_init (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int git_object_peel (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int git_revparse_single (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*) ; 

int git_annotated_commit_from_revspec(
	git_annotated_commit **out,
	git_repository *repo,
	const char *revspec)
{
	git_object *obj, *commit;
	int error;

	assert(out && repo && revspec);

	if ((error = git_revparse_single(&obj, repo, revspec)) < 0)
		return error;

	if ((error = git_object_peel(&commit, obj, GIT_OBJECT_COMMIT))) {
		git_object_free(obj);
		return error;
	}

	error = annotated_commit_init(out, (git_commit *)commit, revspec);

	git_object_free(obj);
	git_object_free(commit);

	return error;
}
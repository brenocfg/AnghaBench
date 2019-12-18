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
typedef  int /*<<< orphan*/  git_object ;
typedef  int /*<<< orphan*/  git_commit ;

/* Variables and functions */
 int GIT_EAMBIGUOUS ; 
 int GIT_EINVALIDSPEC ; 
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_OBJECT_COMMIT ; 
 int git_commit_nth_gen_ancestor (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int git_object_peel (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int handle_linear_syntax(git_object **out, git_object *obj, int n)
{
	git_object *temp_commit = NULL;
	int error;

	if ((error = git_object_peel(&temp_commit, obj, GIT_OBJECT_COMMIT)) < 0)
		return (error == GIT_EAMBIGUOUS || error == GIT_ENOTFOUND) ?
			GIT_EINVALIDSPEC : error;

	error = git_commit_nth_gen_ancestor((git_commit **)out, (git_commit*)temp_commit, n);

	git_object_free(temp_commit);
	return error;
}
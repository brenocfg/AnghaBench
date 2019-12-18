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
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_index ;
typedef  int /*<<< orphan*/  git_annotated_commit ;

/* Variables and functions */
 int /*<<< orphan*/  check_status (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_rmfile (char*) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_annotated_commit_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_annotated_commit_from_ref (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_add_all (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_merge (int /*<<< orphan*/ ,int /*<<< orphan*/  const**,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

void test_index_addall__removes_deleted_conflicted_files(void)
{
	git_index *index;
	git_reference *ref;
	git_annotated_commit *annotated;

	g_repo = cl_git_sandbox_init("merge-resolve");
	cl_git_pass(git_repository_index(&index, g_repo));

	check_status(g_repo, 0, 0, 0, 0, 0, 0, 0, 0);

	cl_git_pass(git_reference_lookup(&ref, g_repo, "refs/heads/branch"));
	cl_git_pass(git_annotated_commit_from_ref(&annotated, g_repo, ref));

	cl_git_pass(git_merge(g_repo, (const git_annotated_commit**)&annotated, 1, NULL, NULL));
	check_status(g_repo, 0, 1, 2, 0, 0, 0, 0, 1);

	cl_git_rmfile("merge-resolve/conflicting.txt");

	cl_git_pass(git_index_add_all(index, NULL, 0, NULL, NULL));
	cl_git_pass(git_index_write(index));
	check_status(g_repo, 0, 2, 2, 0, 0, 0, 0, 0);

	git_annotated_commit_free(annotated);
	git_reference_free(ref);
	git_index_free(index);
}
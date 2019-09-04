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
typedef  int /*<<< orphan*/  git_indexwriter ;
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ELOCKED ; 
 int /*<<< orphan*/  GIT_INDEXWRITER_INIT ; 
 int /*<<< orphan*/  cl_git_fail_with (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_cleanup () ; 
 int /*<<< orphan*/ * cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_indexwriter_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_indexwriter_commit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_indexwriter_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

void test_index_tests__can_lock_index(void)
{
	git_repository *repo;
	git_index *index;
	git_indexwriter one = GIT_INDEXWRITER_INIT,
		two = GIT_INDEXWRITER_INIT;

	repo = cl_git_sandbox_init("testrepo.git");

	cl_git_pass(git_repository_index(&index, repo));
	cl_git_pass(git_indexwriter_init(&one, index));

	cl_git_fail_with(GIT_ELOCKED, git_indexwriter_init(&two, index));
	cl_git_fail_with(GIT_ELOCKED, git_index_write(index));

	cl_git_pass(git_indexwriter_commit(&one));

	cl_git_pass(git_index_write(index));

	git_indexwriter_cleanup(&one);
	git_indexwriter_cleanup(&two);
	git_index_free(index);
	cl_git_sandbox_cleanup();
}
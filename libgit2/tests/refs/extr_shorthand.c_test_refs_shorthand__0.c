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

/* Variables and functions */
 int /*<<< orphan*/  assert_shorthand (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  cl_fixture (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_open (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

void test_refs_shorthand__0(void)
{
	git_repository *repo;

	cl_git_pass(git_repository_open(&repo, cl_fixture("testrepo.git")));


	assert_shorthand(repo, "refs/heads/master", "master");
	assert_shorthand(repo, "refs/tags/test", "test");
	assert_shorthand(repo, "refs/remotes/test/master", "test/master");
	assert_shorthand(repo, "refs/notes/fanout", "notes/fanout");

	git_repository_free(repo);
}
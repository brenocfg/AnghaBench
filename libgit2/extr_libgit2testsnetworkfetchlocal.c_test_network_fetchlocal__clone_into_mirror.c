#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_reference ;
struct TYPE_4__ {int bare; int /*<<< orphan*/  remote_cb; } ;
typedef  TYPE_1__ git_clone_options ;

/* Variables and functions */
 TYPE_1__ GIT_CLONE_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_REFERENCE_SYMBOLIC ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_fixture_cleanup (char*) ; 
 int /*<<< orphan*/  cl_git_fixture_url (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_clone (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_reference_symbolic_target (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remote_mirror_cb ; 

void test_network_fetchlocal__clone_into_mirror(void)
{
	git_clone_options opts = GIT_CLONE_OPTIONS_INIT;
	git_repository *repo;
	git_reference *ref;

	opts.bare = true;
	opts.remote_cb = remote_mirror_cb;
	cl_git_pass(git_clone(&repo, cl_git_fixture_url("testrepo.git"), "./foo.git", &opts));

	cl_git_pass(git_reference_lookup(&ref, repo, "HEAD"));
	cl_assert_equal_i(GIT_REFERENCE_SYMBOLIC, git_reference_type(ref));
	cl_assert_equal_s("refs/heads/master", git_reference_symbolic_target(ref));

	git_reference_free(ref);
	cl_git_pass(git_reference_lookup(&ref, repo, "refs/remotes/test/master"));

	git_reference_free(ref);
	git_repository_free(repo);
	cl_fixture_cleanup("./foo.git");
}
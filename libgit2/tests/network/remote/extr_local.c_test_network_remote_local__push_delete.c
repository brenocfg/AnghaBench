#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char** member_0; int member_1; char** strings; } ;
typedef  TYPE_1__ git_strarray ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_remote ;
typedef  int /*<<< orphan*/  git_reference ;

/* Variables and functions */
 int /*<<< orphan*/  cl_fixture_cleanup (char*) ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_cleanup () ; 
 int /*<<< orphan*/ * cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_remote_create (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  git_remote_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_push (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_init (int /*<<< orphan*/ **,char*,int) ; 

void test_network_remote_local__push_delete(void)
{
	git_repository *src_repo;
	git_repository *dst_repo;
	git_remote *remote;
	git_reference *ref;
	char *spec_push[] = { "refs/heads/master" };
	char *spec_delete[] = { ":refs/heads/master" };
	git_strarray specs = {
		spec_push,
		1,
	};

	src_repo = cl_git_sandbox_init("testrepo.git");
	cl_git_pass(git_repository_init(&dst_repo, "target.git", 1));

	cl_git_pass(git_remote_create(&remote, src_repo, "origin", "./target.git"));

	/* Push the master branch and verify it's there */
	cl_git_pass(git_remote_push(remote, &specs, NULL));
	cl_git_pass(git_reference_lookup(&ref, dst_repo, "refs/heads/master"));
	git_reference_free(ref);

	specs.strings = spec_delete;
	cl_git_pass(git_remote_push(remote, &specs, NULL));
	cl_git_fail(git_reference_lookup(&ref, dst_repo, "refs/heads/master"));

	git_remote_free(remote);
	git_repository_free(dst_repo);
	cl_fixture_cleanup("target.git");
	cl_git_sandbox_cleanup();
}
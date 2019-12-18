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
struct TYPE_4__ {int /*<<< orphan*/  count; } ;
typedef  TYPE_1__ git_strarray ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_remote ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_URL ; 
 int /*<<< orphan*/ * _repo ; 
 int /*<<< orphan*/  cl_assert_equal_sz (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_remote_create (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_remote_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_list (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_open (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_path (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_strarray_free (TYPE_1__*) ; 

void test_remote_list__always_checks_disk_config(void)
{
	git_repository *repo;
	git_strarray remotes;
	git_remote *remote;

	cl_git_pass(git_repository_open(&repo, git_repository_path(_repo)));

	cl_git_pass(git_remote_list(&remotes, _repo));
	cl_assert_equal_sz(remotes.count, 1);
	git_strarray_free(&remotes);

	cl_git_pass(git_remote_create(&remote, _repo, "valid-name", TEST_URL));

	cl_git_pass(git_remote_list(&remotes, _repo));
	cl_assert_equal_sz(remotes.count, 2);
	git_strarray_free(&remotes);

	cl_git_pass(git_remote_list(&remotes, repo));
	cl_assert_equal_sz(remotes.count, 2);
	git_strarray_free(&remotes);

	git_repository_free(repo);
	git_remote_free(remote);
}
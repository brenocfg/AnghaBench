#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ count; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ git_strarray ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_remote ;
struct TYPE_8__ {int /*<<< orphan*/  transfer_progress; } ;
struct TYPE_10__ {TYPE_1__ callbacks; } ;
typedef  TYPE_3__ git_fetch_options ;

/* Variables and functions */
 TYPE_3__ GIT_FETCH_OPTIONS_INIT ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_git_fixture_url (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  git_reference_list (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_fetch (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_remote_set_url (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_strarray_free (TYPE_2__*) ; 
 int /*<<< orphan*/  transfer_cb ; 

void test_network_fetchlocal__multi_remotes(void)
{
	git_repository *repo = cl_git_sandbox_init("testrepo.git");
	git_remote *test, *test2;
	git_strarray refnames = {0};
	git_fetch_options options = GIT_FETCH_OPTIONS_INIT;

	options.callbacks.transfer_progress = transfer_cb;
	cl_git_pass(git_remote_set_url(repo, "test", cl_git_fixture_url("testrepo.git")));
	cl_git_pass(git_remote_lookup(&test, repo, "test"));
	cl_git_pass(git_remote_fetch(test, NULL, &options, NULL));

	cl_git_pass(git_reference_list(&refnames, repo));
	cl_assert_equal_i(33, (int)refnames.count);
	git_strarray_free(&refnames);

	cl_git_pass(git_remote_set_url(repo, "test_with_pushurl", cl_git_fixture_url("testrepo.git")));
	cl_git_pass(git_remote_lookup(&test2, repo, "test_with_pushurl"));
	cl_git_pass(git_remote_fetch(test2, NULL, &options, NULL));

	cl_git_pass(git_reference_list(&refnames, repo));
	cl_assert_equal_i(45, (int)refnames.count);

	git_strarray_free(&refnames);
	git_remote_free(test);
	git_remote_free(test2);
}
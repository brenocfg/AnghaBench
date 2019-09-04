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
struct TYPE_8__ {int* payload; int /*<<< orphan*/  transfer_progress; } ;
struct TYPE_10__ {TYPE_1__ callbacks; } ;
typedef  TYPE_3__ git_fetch_options ;

/* Variables and functions */
 TYPE_3__ GIT_FETCH_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_REMOTE_ORIGIN ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 char* cl_git_fixture_url (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  git_reference_list (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_create (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  git_remote_fetch (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_strarray_free (TYPE_2__*) ; 
 int /*<<< orphan*/  transfer_cb ; 

void test_network_fetchlocal__partial(void)
{
	git_repository *repo = cl_git_sandbox_init("partial-testrepo");
	git_remote *origin;
	int callcount = 0;
	git_strarray refnames = {0};
	const char *url;
	git_fetch_options options = GIT_FETCH_OPTIONS_INIT;

	options.callbacks.transfer_progress = transfer_cb;
	options.callbacks.payload = &callcount;

	cl_git_pass(git_reference_list(&refnames, repo));
	cl_assert_equal_i(1, (int)refnames.count);

	url = cl_git_fixture_url("testrepo.git");
	cl_git_pass(git_remote_create(&origin, repo, GIT_REMOTE_ORIGIN, url));
	cl_git_pass(git_remote_fetch(origin, NULL, &options, NULL));

	git_strarray_free(&refnames);

	cl_git_pass(git_reference_list(&refnames, repo));
	cl_assert_equal_i(20, (int)refnames.count); /* 18 remote + 1 local */
	cl_assert(callcount > 0);

	git_strarray_free(&refnames);
	git_remote_free(origin);
}
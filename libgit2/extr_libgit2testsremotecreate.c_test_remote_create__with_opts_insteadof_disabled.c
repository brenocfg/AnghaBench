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
struct TYPE_4__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  repository; } ;
typedef  TYPE_1__ git_remote_create_options ;
typedef  int /*<<< orphan*/  git_remote ;

/* Variables and functions */
 TYPE_1__ GIT_REMOTE_CREATE_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_REMOTE_CREATE_SKIP_INSTEADOF ; 
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  cl_assert_equal_p (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_remote_create_with_opts (int /*<<< orphan*/ **,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  git_remote_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_pushurl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_url (int /*<<< orphan*/ *) ; 

void test_remote_create__with_opts_insteadof_disabled(void)
{
	git_remote *remote;
	git_remote_create_options opts = GIT_REMOTE_CREATE_OPTIONS_INIT;

	opts.repository = _repo;
	opts.flags = GIT_REMOTE_CREATE_SKIP_INSTEADOF;

	cl_git_pass(git_remote_create_with_opts(&remote, "http://example.com/libgit2/libgit2", &opts));

	cl_assert_equal_s(git_remote_url(remote), "http://example.com/libgit2/libgit2");
	cl_assert_equal_p(git_remote_pushurl(remote), NULL);

	git_remote_free(remote);
}
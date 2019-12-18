#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  count; } ;
typedef  TYPE_1__ git_strarray ;
struct TYPE_8__ {char* name; int /*<<< orphan*/  flags; int /*<<< orphan*/  repository; } ;
typedef  TYPE_2__ git_remote_create_options ;
typedef  int /*<<< orphan*/  git_remote ;

/* Variables and functions */
 TYPE_2__ GIT_REMOTE_CREATE_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_REMOTE_CREATE_SKIP_DEFAULT_FETCHSPEC ; 
 char* TEST_URL ; 
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_remote_create_with_opts (int /*<<< orphan*/ **,char*,TYPE_2__*) ; 
 int /*<<< orphan*/  git_remote_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_get_fetch_refspecs (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_owner (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_url (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_strarray_free (TYPE_1__*) ; 

void test_remote_create__with_opts_named_no_fetchspec(void)
{
	git_remote *remote;
	git_strarray array;
	git_remote_create_options opts = GIT_REMOTE_CREATE_OPTIONS_INIT;

	opts.name = "test-new";
	opts.repository = _repo;
	opts.flags = GIT_REMOTE_CREATE_SKIP_DEFAULT_FETCHSPEC;

	cl_git_pass(git_remote_create_with_opts(&remote, TEST_URL, &opts));
	cl_assert_equal_s(git_remote_name(remote), "test-new");
	cl_assert_equal_s(git_remote_url(remote), TEST_URL);
	cl_assert_equal_p(git_remote_owner(remote), _repo);

	cl_git_pass(git_remote_get_fetch_refspecs(&array, remote));
	cl_assert_equal_i(0, array.count);

	git_strarray_free(&array);
	git_remote_free(remote);
}
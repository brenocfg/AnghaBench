#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_remote ;
struct TYPE_5__ {int /*<<< orphan*/ * ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_DIRECTION_FETCH ; 
 int /*<<< orphan*/  GIT_DIRECTION_PUSH ; 
 int /*<<< orphan*/ * _remote ; 
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_remote__urlfordirection (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * git_remote_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * git_remote_pushurl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * git_remote_url (int /*<<< orphan*/ *) ; 

void test_network_remote_remotes__parsing(void)
{
	git_buf url = GIT_BUF_INIT;
	git_remote *_remote2 = NULL;

	cl_assert_equal_s(git_remote_name(_remote), "test");
	cl_assert_equal_s(git_remote_url(_remote), "git://github.com/libgit2/libgit2");
	cl_assert(git_remote_pushurl(_remote) == NULL);

	cl_git_pass(git_remote__urlfordirection(&url, _remote, GIT_DIRECTION_FETCH, NULL));
	cl_assert_equal_s(url.ptr, "git://github.com/libgit2/libgit2");

	cl_git_pass(git_remote__urlfordirection(&url, _remote, GIT_DIRECTION_PUSH, NULL));
	cl_assert_equal_s(url.ptr, "git://github.com/libgit2/libgit2");

	cl_git_pass(git_remote_lookup(&_remote2, _repo, "test_with_pushurl"));
	cl_assert_equal_s(git_remote_name(_remote2), "test_with_pushurl");
	cl_assert_equal_s(git_remote_url(_remote2), "git://github.com/libgit2/fetchlibgit2");
	cl_assert_equal_s(git_remote_pushurl(_remote2), "git://github.com/libgit2/pushlibgit2");

	cl_git_pass(git_remote__urlfordirection(&url, _remote2, GIT_DIRECTION_FETCH, NULL));
	cl_assert_equal_s(url.ptr, "git://github.com/libgit2/fetchlibgit2");

	cl_git_pass(git_remote__urlfordirection(&url, _remote2, GIT_DIRECTION_PUSH, NULL));
	cl_assert_equal_s(url.ptr, "git://github.com/libgit2/pushlibgit2");

	git_remote_free(_remote2);
	git_buf_dispose(&url);
}
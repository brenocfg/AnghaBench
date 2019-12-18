#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char const* ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_CLONE_LOCAL ; 
 int /*<<< orphan*/  GIT_CLONE_LOCAL_AUTO ; 
 int /*<<< orphan*/  GIT_CLONE_LOCAL_NO_LINKS ; 
 int /*<<< orphan*/  GIT_CLONE_NO_LOCAL ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 char* cl_fixture (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  file_url (TYPE_1__*,char*,char const*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_puts (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  git_buf_shorten (TYPE_1__*,int) ; 
 int /*<<< orphan*/  git_clone__should_clone_local (char const*,int /*<<< orphan*/ ) ; 

void test_clone_local__should_clone_local(void)
{
	git_buf buf = GIT_BUF_INIT;

	/* we use a fixture path because it needs to exist for us to want to clone */
	const char *path = cl_fixture("testrepo.git");

	cl_git_pass(file_url(&buf, "", path));
	cl_assert_equal_i(0, git_clone__should_clone_local(buf.ptr, GIT_CLONE_LOCAL_AUTO));
	cl_assert_equal_i(1,  git_clone__should_clone_local(buf.ptr, GIT_CLONE_LOCAL));
	cl_assert_equal_i(1,  git_clone__should_clone_local(buf.ptr, GIT_CLONE_LOCAL_NO_LINKS));
	cl_assert_equal_i(0, git_clone__should_clone_local(buf.ptr, GIT_CLONE_NO_LOCAL));

	cl_git_pass(file_url(&buf, "localhost", path));
	cl_assert_equal_i(0, git_clone__should_clone_local(buf.ptr, GIT_CLONE_LOCAL_AUTO));
	cl_assert_equal_i(1,  git_clone__should_clone_local(buf.ptr, GIT_CLONE_LOCAL));
	cl_assert_equal_i(1,  git_clone__should_clone_local(buf.ptr, GIT_CLONE_LOCAL_NO_LINKS));
	cl_assert_equal_i(0, git_clone__should_clone_local(buf.ptr, GIT_CLONE_NO_LOCAL));

	cl_git_pass(file_url(&buf, "other-host.mycompany.com", path));
	cl_assert_equal_i(0, git_clone__should_clone_local(buf.ptr, GIT_CLONE_LOCAL_AUTO));
	cl_assert_equal_i(0, git_clone__should_clone_local(buf.ptr, GIT_CLONE_LOCAL));
	cl_assert_equal_i(0, git_clone__should_clone_local(buf.ptr, GIT_CLONE_LOCAL_NO_LINKS));
	cl_assert_equal_i(0, git_clone__should_clone_local(buf.ptr, GIT_CLONE_NO_LOCAL));

	/* Ensure that file:/// urls are percent decoded: .git == %2e%67%69%74 */
	cl_git_pass(file_url(&buf, "", path));
	git_buf_shorten(&buf, 4);
	cl_git_pass(git_buf_puts(&buf, "%2e%67%69%74"));
	cl_assert_equal_i(0, git_clone__should_clone_local(buf.ptr, GIT_CLONE_LOCAL_AUTO));
	cl_assert_equal_i(1,  git_clone__should_clone_local(buf.ptr, GIT_CLONE_LOCAL));
	cl_assert_equal_i(1,  git_clone__should_clone_local(buf.ptr, GIT_CLONE_LOCAL_NO_LINKS));
	cl_assert_equal_i(0, git_clone__should_clone_local(buf.ptr, GIT_CLONE_NO_LOCAL));

	cl_assert_equal_i(1,  git_clone__should_clone_local(path, GIT_CLONE_LOCAL_AUTO));
	cl_assert_equal_i(1,  git_clone__should_clone_local(path, GIT_CLONE_LOCAL));
	cl_assert_equal_i(1,  git_clone__should_clone_local(path, GIT_CLONE_LOCAL_NO_LINKS));
	cl_assert_equal_i(0, git_clone__should_clone_local(path, GIT_CLONE_NO_LOCAL));

	git_buf_dispose(&buf);
}
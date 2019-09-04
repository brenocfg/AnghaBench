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
struct TYPE_5__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_join3 (TYPE_1__*,char,char*,char*,char*) ; 

void test_core_buffer__join3(void)
{
	git_buf a = GIT_BUF_INIT;

	cl_git_pass(git_buf_join3(&a, '/', "test", "string", "join"));
	cl_assert_equal_s("test/string/join", a.ptr);
	cl_git_pass(git_buf_join3(&a, '/', "test/", "string", "join"));
	cl_assert_equal_s("test/string/join", a.ptr);
	cl_git_pass(git_buf_join3(&a, '/', "test/", "/string", "join"));
	cl_assert_equal_s("test/string/join", a.ptr);
	cl_git_pass(git_buf_join3(&a, '/', "test/", "/string/", "join"));
	cl_assert_equal_s("test/string/join", a.ptr);
	cl_git_pass(git_buf_join3(&a, '/', "test/", "/string/", "/join"));
	cl_assert_equal_s("test/string/join", a.ptr);

	cl_git_pass(git_buf_join3(&a, '/', "", "string", "join"));
	cl_assert_equal_s("string/join", a.ptr);
	cl_git_pass(git_buf_join3(&a, '/', "", "string/", "join"));
	cl_assert_equal_s("string/join", a.ptr);
	cl_git_pass(git_buf_join3(&a, '/', "", "string/", "/join"));
	cl_assert_equal_s("string/join", a.ptr);

	cl_git_pass(git_buf_join3(&a, '/', "string", "", "join"));
	cl_assert_equal_s("string/join", a.ptr);
	cl_git_pass(git_buf_join3(&a, '/', "string/", "", "join"));
	cl_assert_equal_s("string/join", a.ptr);
	cl_git_pass(git_buf_join3(&a, '/', "string/", "", "/join"));
	cl_assert_equal_s("string/join", a.ptr);

	git_buf_dispose(&a);
}
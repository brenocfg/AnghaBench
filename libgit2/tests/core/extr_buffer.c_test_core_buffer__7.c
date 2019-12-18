#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {char* ptr; scalar_t__ size; scalar_t__ asize; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char const*,char*) ; 
 int /*<<< orphan*/  git__free (char*) ; 
 char* git__strdup (char const*) ; 
 int /*<<< orphan*/  git_buf_attach (TYPE_1__*,char*,scalar_t__) ; 
 char* git_buf_cstr (TYPE_1__*) ; 
 char* git_buf_detach (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 scalar_t__ git_buf_oom (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_sets (TYPE_1__*,char*) ; 
 scalar_t__ strlen (char const*) ; 

void test_core_buffer__7(void)
{
	const char *fun = "This is fun";
	git_buf a = GIT_BUF_INIT;
	char *b = NULL;

	git_buf_sets(&a, "foo");
	cl_assert(git_buf_oom(&a) == 0);
	cl_assert_equal_s("foo", git_buf_cstr(&a));

	b = git_buf_detach(&a);

	cl_assert_equal_s("foo", b);
	cl_assert_equal_s("", a.ptr);
	git__free(b);

	b = git_buf_detach(&a);

	cl_assert_equal_s(NULL, b);
	cl_assert_equal_s("", a.ptr);

	git_buf_dispose(&a);

	b = git__strdup(fun);
	git_buf_attach(&a, b, 0);

	cl_assert_equal_s(fun, a.ptr);
	cl_assert(a.size == strlen(fun));
	cl_assert(a.asize == strlen(fun) + 1);

	git_buf_dispose(&a);

	b = git__strdup(fun);
	git_buf_attach(&a, b, strlen(fun) + 1);

	cl_assert_equal_s(fun, a.ptr);
	cl_assert(a.size == strlen(fun));
	cl_assert(a.asize == strlen(fun) + 1);

	git_buf_dispose(&a);
}
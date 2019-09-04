#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {char* ptr; int size; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_consume (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  git_buf_cstr (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 scalar_t__ git_buf_oom (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_puts (TYPE_1__*,char*) ; 
 size_t strlen (int /*<<< orphan*/ ) ; 

void test_core_buffer__4(void)
{
	git_buf buf = GIT_BUF_INIT;
	int i;

	for (i = 0; i < 10; ++i) {
		git_buf_puts(&buf, "1234"); /* add 4 */
		cl_assert(git_buf_oom(&buf) == 0);
		git_buf_consume(&buf, buf.ptr + 2); /* eat the first two */
		cl_assert(strlen(git_buf_cstr(&buf)) == (size_t)((i + 1) * 2));
	}
	/* we have appended 1234 10x and removed the first 20 letters */
	cl_assert_equal_s("12341234123412341234", git_buf_cstr(&buf));

	git_buf_consume(&buf, NULL);
	cl_assert_equal_s("12341234123412341234", git_buf_cstr(&buf));

	git_buf_consume(&buf, "invalid pointer");
	cl_assert_equal_s("12341234123412341234", git_buf_cstr(&buf));

	git_buf_consume(&buf, buf.ptr);
	cl_assert_equal_s("12341234123412341234", git_buf_cstr(&buf));

	git_buf_consume(&buf, buf.ptr + 1);
	cl_assert_equal_s("2341234123412341234", git_buf_cstr(&buf));

	git_buf_consume(&buf, buf.ptr + buf.size);
	cl_assert_equal_s("", git_buf_cstr(&buf));

	git_buf_dispose(&buf);
}
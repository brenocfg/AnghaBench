#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  ptr; int /*<<< orphan*/  size; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_sz (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_decode_base85 (TYPE_1__*,char*,int,int) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_puts (TYPE_1__*,char*) ; 

void test_core_buffer__decode_base85_fails_gracefully(void)
{
	git_buf buf = GIT_BUF_INIT;

	git_buf_puts(&buf, "foobar");

	cl_git_fail(git_buf_decode_base85(&buf, "invalid charsZZ", 15, 42));
	cl_git_fail(git_buf_decode_base85(&buf, "invalidchars__ ", 15, 42));
	cl_git_fail(git_buf_decode_base85(&buf, "overflowZZ~~~~~", 15, 42));
	cl_git_fail(git_buf_decode_base85(&buf, "truncated", 9, 42));
	cl_assert_equal_sz(6, buf.size);
	cl_assert_equal_s("foobar", buf.ptr);

	git_buf_dispose(&buf);
}
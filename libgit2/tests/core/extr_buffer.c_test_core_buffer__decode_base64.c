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
struct TYPE_6__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_clear (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_decode_base64 (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 

void test_core_buffer__decode_base64(void)
{
	git_buf buf = GIT_BUF_INIT;

	cl_git_pass(git_buf_decode_base64(&buf, "dGhpcw==", 8));
	cl_assert_equal_s("this", buf.ptr);

	git_buf_clear(&buf);
	cl_git_pass(git_buf_decode_base64(&buf, "dGhpcyE=", 8));
	cl_assert_equal_s("this!", buf.ptr);

	git_buf_clear(&buf);
	cl_git_pass(git_buf_decode_base64(&buf, "dGhpcyEK", 8));
	cl_assert_equal_s("this!\n", buf.ptr);

	cl_git_fail(git_buf_decode_base64(&buf, "This is not a valid base64 string!!!", 36));
	cl_assert_equal_s("this!\n", buf.ptr);

	git_buf_dispose(&buf);
}
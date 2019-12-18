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
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_clear (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_encode_base85 (TYPE_1__*,char*,int) ; 
 int strlen (char*) ; 

void test_core_buffer__encode_base85(void)
{
	git_buf buf = GIT_BUF_INIT;

	cl_git_pass(git_buf_encode_base85(&buf, "this", 4));
	cl_assert_equal_s("bZBXF", buf.ptr);
	git_buf_clear(&buf);

	cl_git_pass(git_buf_encode_base85(&buf, "two rnds", 8));
	cl_assert_equal_s("ba!tca&BaE", buf.ptr);
	git_buf_clear(&buf);

	cl_git_pass(git_buf_encode_base85(&buf, "this is base 85 encoded",
		strlen("this is base 85 encoded")));
	cl_assert_equal_s("bZBXFAZc?TVqtS-AUHK3Wo~0{WMyOk", buf.ptr);
	git_buf_clear(&buf);

	git_buf_dispose(&buf);
}
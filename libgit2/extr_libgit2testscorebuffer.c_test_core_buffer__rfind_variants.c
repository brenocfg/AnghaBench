#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 scalar_t__ git_buf_len (int /*<<< orphan*/ *) ; 
 int git_buf_rfind (int /*<<< orphan*/ *,char) ; 
 int git_buf_rfind_next (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  git_buf_sets (int /*<<< orphan*/ *,char*) ; 

void test_core_buffer__rfind_variants(void)
{
	git_buf a = GIT_BUF_INIT;
	ssize_t len;

	cl_git_pass(git_buf_sets(&a, "/this/is/it/"));

	len = (ssize_t)git_buf_len(&a);

	cl_assert(git_buf_rfind(&a, '/') == len - 1);
	cl_assert(git_buf_rfind_next(&a, '/') == len - 4);

	cl_assert(git_buf_rfind(&a, 'i') == len - 3);
	cl_assert(git_buf_rfind_next(&a, 'i') == len - 3);

	cl_assert(git_buf_rfind(&a, 'h') == 2);
	cl_assert(git_buf_rfind_next(&a, 'h') == 2);

	cl_assert(git_buf_rfind(&a, 'q') == -1);
	cl_assert(git_buf_rfind_next(&a, 'q') == -1);

	git_buf_dispose(&a);
}
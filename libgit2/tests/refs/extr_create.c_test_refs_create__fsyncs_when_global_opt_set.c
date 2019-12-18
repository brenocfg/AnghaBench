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

/* Variables and functions */
 int /*<<< orphan*/  GIT_OPT_ENABLE_FSYNC_GITDIR ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  count_fsyncs (size_t*,size_t*) ; 
 int /*<<< orphan*/  expected_fsyncs_compress ; 
 int /*<<< orphan*/  expected_fsyncs_create ; 
 int /*<<< orphan*/  git_libgit2_opts (int /*<<< orphan*/ ,int) ; 

void test_refs_create__fsyncs_when_global_opt_set(void)
{
	size_t create_count, compress_count;

	cl_git_pass(git_libgit2_opts(GIT_OPT_ENABLE_FSYNC_GITDIR, 1));
	count_fsyncs(&create_count, &compress_count);

	cl_assert_equal_i(expected_fsyncs_create, create_count);
	cl_assert_equal_i(expected_fsyncs_compress, compress_count);
}
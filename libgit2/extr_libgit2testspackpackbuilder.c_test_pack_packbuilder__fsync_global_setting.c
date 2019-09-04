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
 int /*<<< orphan*/  _packbuilder ; 
 int /*<<< orphan*/  cl_assert_equal_sz (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expected_fsyncs ; 
 int /*<<< orphan*/  git_libgit2_opts (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  git_packbuilder_write (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ p_fsync__cnt ; 
 int /*<<< orphan*/  seed_packbuilder () ; 

void test_pack_packbuilder__fsync_global_setting(void)
{
	cl_git_pass(git_libgit2_opts(GIT_OPT_ENABLE_FSYNC_GITDIR, 1));
	p_fsync__cnt = 0;
	seed_packbuilder();
	git_packbuilder_write(_packbuilder, ".", 0666, NULL, NULL);
	cl_assert_equal_sz(expected_fsyncs, p_fsync__cnt);
}
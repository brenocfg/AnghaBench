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
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_libgit2_opts (int /*<<< orphan*/ ,int) ; 
 scalar_t__ p_fsync__cnt ; 
 int /*<<< orphan*/  write_object_to_loose_odb (int /*<<< orphan*/ ) ; 

void test_odb_loose__fsync_obeys_global_setting(void)
{
	cl_git_pass(git_libgit2_opts(GIT_OPT_ENABLE_FSYNC_GITDIR, 1));
	write_object_to_loose_odb(0);
	cl_assert(p_fsync__cnt > 0);
}
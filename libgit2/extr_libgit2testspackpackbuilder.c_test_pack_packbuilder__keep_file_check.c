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
 int /*<<< orphan*/  GIT_OPT_DISABLE_PACK_KEEP_FILE_CHECKS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int git_disable_pack_keep_file_checks ; 
 int /*<<< orphan*/  git_libgit2_opts (int /*<<< orphan*/ ,int) ; 

void test_pack_packbuilder__keep_file_check(void)
{
	assert(!git_disable_pack_keep_file_checks);
	cl_git_pass(git_libgit2_opts(GIT_OPT_DISABLE_PACK_KEEP_FILE_CHECKS, true));
	assert(git_disable_pack_keep_file_checks);
}
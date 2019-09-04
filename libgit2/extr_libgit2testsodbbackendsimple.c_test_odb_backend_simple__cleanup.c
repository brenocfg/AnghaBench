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
 int /*<<< orphan*/  GIT_OPT_ENABLE_STRICT_HASH_VERIFICATION ; 
 int /*<<< orphan*/  _obj ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_cleanup () ; 
 int /*<<< orphan*/  git_libgit2_opts (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  git_odb_object_free (int /*<<< orphan*/ ) ; 

void test_odb_backend_simple__cleanup(void)
{
	git_odb_object_free(_obj);
	cl_git_sandbox_cleanup();
	cl_git_pass(git_libgit2_opts(GIT_OPT_ENABLE_STRICT_HASH_VERIFICATION, 1));
}
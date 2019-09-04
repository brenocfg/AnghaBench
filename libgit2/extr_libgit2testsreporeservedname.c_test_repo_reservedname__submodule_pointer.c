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

void test_repo_reservedname__submodule_pointer(void)
{
#ifdef GIT_WIN32
	git_repository *super_repo, *sub_repo;
	git_submodule *sub;
	git_buf *sub_reserved;
	size_t sub_reserved_len;

	if (!cl_sandbox_supports_8dot3())
		clar__skip();

	super_repo = setup_fixture_submod2();

	assert_submodule_exists(super_repo, "sm_unchanged");

	cl_git_pass(git_submodule_lookup(&sub, super_repo, "sm_unchanged"));
	cl_git_pass(git_submodule_open(&sub_repo, sub));

	cl_assert(git_repository__reserved_names(&sub_reserved, &sub_reserved_len, sub_repo, true));

	cl_assert_equal_i(2, sub_reserved_len);
	cl_assert_equal_s(".git", sub_reserved[0].ptr);
	cl_assert_equal_s("GIT~1", sub_reserved[1].ptr);

	git_submodule_free(sub);
	git_repository_free(sub_repo);
#endif
}
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

void test_repo_reservedname__custom_shortname_recognized(void)
{
#ifdef GIT_WIN32
	git_repository *repo;
	git_buf *reserved;
	size_t reserved_len;

	if (!cl_sandbox_supports_8dot3())
		clar__skip();

	repo = cl_git_sandbox_init("nasty");

	cl_must_pass(p_rename("nasty/.git", "nasty/_temp"));
	cl_git_write2file("nasty/git~1", "", 0, O_RDWR|O_CREAT, 0666);
	cl_must_pass(p_rename("nasty/_temp", "nasty/.git"));

	cl_assert(git_repository__reserved_names(&reserved, &reserved_len, repo, true));

	cl_assert_equal_i(3, reserved_len);
	cl_assert_equal_s(".git", reserved[0].ptr);
	cl_assert_equal_s("GIT~1", reserved[1].ptr);
	cl_assert_equal_s("GIT~2", reserved[2].ptr);
#endif
}
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
typedef  int /*<<< orphan*/  git_remote ;

/* Variables and functions */
 size_t ARRAY_SIZE (char const**) ; 
 int /*<<< orphan*/  GIT_EINVALIDSPEC ; 
 int /*<<< orphan*/  TEST_URL ; 
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  cl_assert_equal_p (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_git_fail_with (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_with_name (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

void test_remote_create__with_opts_invalid_name(void)
{
	const char *names[] = {
		"Inv@{id",
		"",
		"/",
		"//",
		".lock",
		"a.lock",
	};
	size_t i;

	for (i = 0; i < ARRAY_SIZE(names); i++) {
		git_remote *remote = NULL;
		cl_git_fail_with(GIT_EINVALIDSPEC, create_with_name(&remote, _repo, names[i], TEST_URL));
		cl_assert_equal_p(remote, NULL);
	}
}
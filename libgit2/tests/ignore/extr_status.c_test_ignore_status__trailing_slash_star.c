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
 int /*<<< orphan*/  assert_is_ignored (char*) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  make_test_data (char*,char const**) ; 
 int /*<<< orphan*/  refute_is_ignored (char*) ; 

void test_ignore_status__trailing_slash_star(void)
{
	static const char *test_files[] = {
		"empty_standard_repo/file",
		"empty_standard_repo/subdir/file",
		"empty_standard_repo/subdir/sub2/sub3/file",
		NULL
	};

	make_test_data("empty_standard_repo", test_files);
	cl_git_mkfile(
		"empty_standard_repo/subdir/.gitignore", "/**/*\n");

	refute_is_ignored("file");
	assert_is_ignored("subdir/sub2/sub3/file");
	assert_is_ignored("subdir/file");
}
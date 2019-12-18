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

void test_ignore_status__subdir_ignore_all_toplevel_dirs_include_files(void)
{
	static const char *test_files[] = {
		"empty_standard_repo/project/README.md",
		"empty_standard_repo/project/src/main.c",
		"empty_standard_repo/project/src/foo/foo.c",
		"empty_standard_repo/project/dist/foo.o",
		"empty_standard_repo/project/dist/main.o",
		NULL
	};

	make_test_data("empty_standard_repo", test_files);
	cl_git_mkfile(
		"empty_standard_repo/project/.gitignore",
		"/*/\n"
		"!/src\n");

	assert_is_ignored("project/dist/foo.o");
	assert_is_ignored("project/dist/main.o");

	refute_is_ignored("project/src/foo.c");
	refute_is_ignored("project/src/foo/foo.c");
	refute_is_ignored("project/README.md");
}
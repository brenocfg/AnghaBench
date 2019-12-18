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

void test_ignore_status__ignore_all_toplevel_dirs_include_files(void)
{
	static const char *test_files[] = {
		"empty_standard_repo/README.md",
		"empty_standard_repo/src/main.c",
		"empty_standard_repo/src/foo/foo.c",
		"empty_standard_repo/dist/foo.o",
		"empty_standard_repo/dist/main.o",
		NULL
	};

	make_test_data("empty_standard_repo", test_files);
	cl_git_mkfile(
		"empty_standard_repo/.gitignore",
		"/*/\n"
		"!/src\n");

	assert_is_ignored("dist/foo.o");
	assert_is_ignored("dist/main.o");

	refute_is_ignored("README.md");
	refute_is_ignored("src/foo.c");
	refute_is_ignored("src/foo/foo.c");
}
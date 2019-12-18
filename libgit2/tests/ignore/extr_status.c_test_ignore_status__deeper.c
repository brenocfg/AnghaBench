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

void test_ignore_status__deeper(void)
{
	const char *test_files[] = {
		"empty_standard_repo/foo.data",
		"empty_standard_repo/bar.data",
		"empty_standard_repo/dont_ignore/foo.data",
		"empty_standard_repo/dont_ignore/bar.data",
		NULL
	};

	make_test_data("empty_standard_repo", test_files);
	cl_git_mkfile("empty_standard_repo/.gitignore",
		"*.data\n"
		"!dont_ignore/*.data\n");

	assert_is_ignored("foo.data");
	assert_is_ignored("bar.data");

	refute_is_ignored("dont_ignore/foo.data");
	refute_is_ignored("dont_ignore/bar.data");
}
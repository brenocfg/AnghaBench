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

void test_ignore_status__skips_bom(void)
{
	static const char *test_files[] = {
		"empty_standard_repo/a.test",
		"empty_standard_repo/b.test",
		"empty_standard_repo/c.test",
		"empty_standard_repo/foo.txt",
		"empty_standard_repo/bar.txt",
		NULL
	};

	make_test_data("empty_standard_repo", test_files);
	cl_git_mkfile(
		"empty_standard_repo/.gitignore",
		"\xEF\xBB\xBF*.test\n");

	assert_is_ignored("a.test");
	assert_is_ignored("b.test");
	assert_is_ignored("c.test");
	refute_is_ignored("foo.txt");
	refute_is_ignored("bar.txt");
}
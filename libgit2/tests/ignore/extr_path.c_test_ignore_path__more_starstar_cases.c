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
 int /*<<< orphan*/  assert_is_ignored (int,char*) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_must_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_unlink (char*) ; 

void test_ignore_path__more_starstar_cases(void)
{
	cl_must_pass(p_unlink("attr/.gitignore"));
	cl_git_mkfile(
		"attr/dir/.gitignore",
		"sub/**/*.html\n");

	assert_is_ignored(false, "aaa.html");
	assert_is_ignored(false, "dir");
	assert_is_ignored(false, "dir/sub");
	assert_is_ignored(true,  "dir/sub/sub2/aaa.html");
	assert_is_ignored(true,  "dir/sub/aaa.html");
	assert_is_ignored(false, "dir/aaa.html");
	assert_is_ignored(false, "sub");
	assert_is_ignored(false, "sub/aaa.html");
	assert_is_ignored(false, "sub/sub2/aaa.html");
}
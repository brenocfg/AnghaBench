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
 int /*<<< orphan*/  cl_git_rewritefile (char*,char*) ; 

void test_ignore_path__globs_and_path_delimiters(void)
{
	cl_git_rewritefile("attr/.gitignore", "foo/bar/**");
	assert_is_ignored(true, "foo/bar/baz");
	assert_is_ignored(true, "foo/bar/baz/quux");

	cl_git_rewritefile("attr/.gitignore", "_*/");
	assert_is_ignored(true, "sub/_test/a/file");
	assert_is_ignored(false, "test_folder/file");
	assert_is_ignored(true, "_test/file");
	assert_is_ignored(true, "_test/a/file");

	cl_git_rewritefile("attr/.gitignore", "**/_*/");
	assert_is_ignored(true, "sub/_test/a/file");
	assert_is_ignored(false, "test_folder/file");
	assert_is_ignored(true, "_test/file");
	assert_is_ignored(true, "_test/a/file");

	cl_git_rewritefile("attr/.gitignore", "**/_*/foo/bar/*ux");

	assert_is_ignored(true, "sub/_test/foo/bar/qux/file");
	assert_is_ignored(true, "_test/foo/bar/qux/file");
	assert_is_ignored(true, "_test/foo/bar/crux/file");
	assert_is_ignored(false, "_test/foo/bar/code/file");
}
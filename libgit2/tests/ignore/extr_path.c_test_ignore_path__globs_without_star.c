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

void test_ignore_path__globs_without_star(void)
{
	cl_git_rewritefile(
		"attr/.gitignore",
		"*.foo\n"
		"**.bar\n"
	);

	assert_is_ignored(true, ".foo");
	assert_is_ignored(true, "xyz.foo");
	assert_is_ignored(true, ".bar");
	assert_is_ignored(true, "x.bar");
	assert_is_ignored(true, "xyz.bar");

	assert_is_ignored(true, "test/.foo");
	assert_is_ignored(true, "test/x.foo");
	assert_is_ignored(true, "test/xyz.foo");
	assert_is_ignored(true, "test/.bar");
	assert_is_ignored(true, "test/x.bar");
	assert_is_ignored(true, "test/xyz.bar");
}
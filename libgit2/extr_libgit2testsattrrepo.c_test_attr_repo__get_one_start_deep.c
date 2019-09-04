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
struct attr_expected {int /*<<< orphan*/  attr; int /*<<< orphan*/  expected_str; int /*<<< orphan*/  expected; int /*<<< orphan*/  path; } ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (struct attr_expected*) ; 
 int /*<<< orphan*/  GIT_ATTR_FILE__FROM_FILE ; 
 int /*<<< orphan*/  attr_check_expected (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 struct attr_expected* get_one_test_cases ; 
 int /*<<< orphan*/  git_attr_cache__is_cached (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_attr_get (char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void test_attr_repo__get_one_start_deep(void)
{
	int i;

	for (i = (int)ARRAY_SIZE(get_one_test_cases) - 1; i >= 0; --i) {
		struct attr_expected *scan = &get_one_test_cases[i];
		const char *value;

		cl_git_pass(git_attr_get(&value, g_repo, 0, scan->path, scan->attr));
		attr_check_expected(
			scan->expected, scan->expected_str, scan->attr, value);
	}

	cl_assert(git_attr_cache__is_cached(
		g_repo, GIT_ATTR_FILE__FROM_FILE, ".git/info/attributes"));
	cl_assert(git_attr_cache__is_cached(
		g_repo, GIT_ATTR_FILE__FROM_FILE, ".gitattributes"));
	cl_assert(git_attr_cache__is_cached(
		g_repo, GIT_ATTR_FILE__FROM_FILE, "sub/.gitattributes"));
}
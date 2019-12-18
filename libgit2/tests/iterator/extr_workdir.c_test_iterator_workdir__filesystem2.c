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
typedef  int /*<<< orphan*/  git_iterator ;

/* Variables and functions */
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  expect_iterator_items (int /*<<< orphan*/ *,int,char const**,int,char const**) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_iterator_for_filesystem (int /*<<< orphan*/ **,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_iterator_free (int /*<<< orphan*/ *) ; 

void test_iterator_workdir__filesystem2(void)
{
	git_iterator *i;
	static const char *expect_base[] = {
		"heads/br2",
		"heads/dir",
		"heads/executable",
		"heads/ident",
		"heads/long-file-name",
		"heads/master",
		"heads/merge-conflict",
		"heads/packed-test",
		"heads/subtrees",
		"heads/test",
		"heads/testrepo-worktree",
		"tags/e90810b",
		"tags/foo/bar",
		"tags/foo/foo/bar",
		"tags/point_to_blob",
		"tags/test",
		NULL,
	};

	g_repo = cl_git_sandbox_init("testrepo");

	cl_git_pass(git_iterator_for_filesystem(
		&i, "testrepo/.git/refs", NULL));
	expect_iterator_items(i, 16, expect_base, 16, expect_base);
	git_iterator_free(i);
}
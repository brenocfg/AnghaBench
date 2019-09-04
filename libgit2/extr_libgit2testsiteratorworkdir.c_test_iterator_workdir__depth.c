#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ git_iterator_options ;
typedef  int /*<<< orphan*/  git_iterator ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ITERATOR_INCLUDE_TREES ; 
 TYPE_1__ GIT_ITERATOR_OPTIONS_INIT ; 
 int /*<<< orphan*/  build_workdir_tree (char*,int,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  expect_iterator_items (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_iterator_for_workdir (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_iterator_free (int /*<<< orphan*/ *) ; 

void test_iterator_workdir__depth(void)
{
	git_iterator *iter;
	git_iterator_options iter_opts = GIT_ITERATOR_OPTIONS_INIT;

	g_repo = cl_git_sandbox_init("icase");

	build_workdir_tree("icase", 10, 10);
	build_workdir_tree("icase/DIR01/sUB01", 50, 0);
	build_workdir_tree("icase/dir02/sUB01", 50, 0);

	/* auto expand with no tree entries */
	cl_git_pass(git_iterator_for_workdir(&iter, g_repo, NULL, NULL, &iter_opts));
	expect_iterator_items(iter, 125, NULL, 125, NULL);
	git_iterator_free(iter);

	/* auto expand with tree entries (empty dirs silently skipped) */
	iter_opts.flags = GIT_ITERATOR_INCLUDE_TREES;
	cl_git_pass(git_iterator_for_workdir(&iter, g_repo, NULL, NULL, &iter_opts));
	expect_iterator_items(iter, 337, NULL, 337, NULL);
	git_iterator_free(iter);
}
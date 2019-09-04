#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  length; scalar_t__ contents; } ;
typedef  TYPE_2__ git_vector ;
typedef  int /*<<< orphan*/  git_tree ;
struct TYPE_10__ {char** strings; int /*<<< orphan*/  count; } ;
struct TYPE_12__ {TYPE_1__ pathlist; int /*<<< orphan*/  flags; } ;
typedef  TYPE_3__ git_iterator_options ;
typedef  int /*<<< orphan*/  git_iterator ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ITERATOR_DONT_IGNORE_CASE ; 
 TYPE_3__ GIT_ITERATOR_OPTIONS_INIT ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  expect_iterator_items (int /*<<< orphan*/ *,size_t,char const**,size_t,char const**) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git__strcmp_cb ; 
 int /*<<< orphan*/  git_iterator_for_tree (int /*<<< orphan*/ **,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  git_iterator_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_head_tree (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_vector_clear (TYPE_2__*) ; 
 int /*<<< orphan*/  git_vector_free (TYPE_2__*) ; 
 int /*<<< orphan*/  git_vector_init (TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_vector_insert (TYPE_2__*,char*) ; 

void test_iterator_tree__pathlist_with_directory(void)
{
	git_iterator *i;
	git_iterator_options i_opts = GIT_ITERATOR_OPTIONS_INIT;
	git_vector filelist;
	git_tree *tree;

	const char *expected[] = { "subdir/README", "subdir/new.txt",
		"subdir/subdir2/README", "subdir/subdir2/new.txt" };
	size_t expected_len = 4;

	const char *expected2[] = { "subdir/subdir2/README", "subdir/subdir2/new.txt" };
	size_t expected_len2 = 2;

	g_repo = cl_git_sandbox_init("testrepo2");
	git_repository_head_tree(&tree, g_repo);

	cl_git_pass(git_vector_init(&filelist, 100, &git__strcmp_cb));
	cl_git_pass(git_vector_insert(&filelist, "subdir"));

	i_opts.pathlist.strings = (char **)filelist.contents;
	i_opts.pathlist.count = filelist.length;
	i_opts.flags |= GIT_ITERATOR_DONT_IGNORE_CASE;

	cl_git_pass(git_iterator_for_tree(&i, tree, &i_opts));
	expect_iterator_items(i, expected_len, expected, expected_len, expected);
	git_iterator_free(i);

	git_vector_clear(&filelist);
	cl_git_pass(git_vector_insert(&filelist, "subdir/"));

	i_opts.pathlist.strings = (char **)filelist.contents;
	i_opts.pathlist.count = filelist.length;

	cl_git_pass(git_iterator_for_tree(&i, tree, &i_opts));
	expect_iterator_items(i, expected_len, expected, expected_len, expected);
	git_iterator_free(i);

	git_vector_clear(&filelist);
	cl_git_pass(git_vector_insert(&filelist, "subdir/subdir2"));

	i_opts.pathlist.strings = (char **)filelist.contents;
	i_opts.pathlist.count = filelist.length;

	cl_git_pass(git_iterator_for_tree(&i, tree, &i_opts));
	expect_iterator_items(i, expected_len2, expected2, expected_len2, expected2);
	git_iterator_free(i);

	git_tree_free(tree);
	git_vector_free(&filelist);
}
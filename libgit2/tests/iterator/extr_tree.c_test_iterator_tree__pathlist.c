#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  length; scalar_t__ contents; } ;
typedef  TYPE_2__ git_vector ;
typedef  int /*<<< orphan*/  git_tree ;
struct TYPE_9__ {char** strings; int /*<<< orphan*/  count; } ;
struct TYPE_11__ {char* start; char* end; TYPE_1__ pathlist; } ;
typedef  TYPE_3__ git_iterator_options ;
typedef  int /*<<< orphan*/  git_iterator ;

/* Variables and functions */
 TYPE_3__ GIT_ITERATOR_OPTIONS_INIT ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  expect_iterator_items (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git__strcmp_cb ; 
 int /*<<< orphan*/  git_iterator_for_tree (int /*<<< orphan*/ **,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  git_iterator_free (int /*<<< orphan*/ *) ; 
 int git_iterator_ignore_case (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_head_tree (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_vector_free (TYPE_2__*) ; 
 int /*<<< orphan*/  git_vector_init (TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_vector_insert (TYPE_2__*,char*) ; 

void test_iterator_tree__pathlist(void)
{
	git_iterator *i;
	git_iterator_options i_opts = GIT_ITERATOR_OPTIONS_INIT;
	git_vector filelist;
	git_tree *tree;
	bool default_icase;
	int expect;

	cl_git_pass(git_vector_init(&filelist, 100, &git__strcmp_cb));
	cl_git_pass(git_vector_insert(&filelist, "a"));
	cl_git_pass(git_vector_insert(&filelist, "B"));
	cl_git_pass(git_vector_insert(&filelist, "c"));
	cl_git_pass(git_vector_insert(&filelist, "D"));
	cl_git_pass(git_vector_insert(&filelist, "e"));
	cl_git_pass(git_vector_insert(&filelist, "k.a"));
	cl_git_pass(git_vector_insert(&filelist, "k.b"));
	cl_git_pass(git_vector_insert(&filelist, "k/1"));
	cl_git_pass(git_vector_insert(&filelist, "k/a"));
	cl_git_pass(git_vector_insert(&filelist, "kZZZZZZZ"));
	cl_git_pass(git_vector_insert(&filelist, "L/1"));

	g_repo = cl_git_sandbox_init("icase");
	git_repository_head_tree(&tree, g_repo);

	/* All indexfilelist iterator tests are "autoexpand with no tree entries" */
	/* In this test we DO NOT force a case on the iterators and verify default behavior. */

	i_opts.pathlist.strings = (char **)filelist.contents;
	i_opts.pathlist.count = filelist.length;

	cl_git_pass(git_iterator_for_tree(&i, tree, &i_opts));
	expect_iterator_items(i, 8, NULL, 8, NULL);
	git_iterator_free(i);

	i_opts.start = "c";
	i_opts.end = NULL;
	cl_git_pass(git_iterator_for_tree(&i, tree, &i_opts));
	default_icase = git_iterator_ignore_case(i);
	/* (c D e k/1 k/a L ==> 6) vs (c e k/1 k/a ==> 4) */
	expect = ((default_icase) ? 6 : 4);
	expect_iterator_items(i, expect, NULL, expect, NULL);
	git_iterator_free(i);

	i_opts.start = NULL;
	i_opts.end = "e";
	cl_git_pass(git_iterator_for_tree(&i, tree, &i_opts));
	default_icase = git_iterator_ignore_case(i);
	/* (a B c D e ==> 5) vs (B D L/1 a c e ==> 6) */
	expect = ((default_icase) ? 5 : 6);
	expect_iterator_items(i, expect, NULL, expect, NULL);
	git_iterator_free(i);

	git_vector_free(&filelist);
	git_tree_free(tree);
}
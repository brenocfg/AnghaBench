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
struct TYPE_11__ {scalar_t__ length; scalar_t__ contents; } ;
typedef  TYPE_2__ git_vector ;
typedef  int /*<<< orphan*/  git_tree ;
struct TYPE_10__ {char** strings; scalar_t__ count; } ;
struct TYPE_12__ {char* start; char* end; void* flags; TYPE_1__ pathlist; } ;
typedef  TYPE_3__ git_iterator_options ;
typedef  int /*<<< orphan*/  git_iterator ;
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 void* GIT_ITERATOR_DONT_IGNORE_CASE ; 
 TYPE_3__ GIT_ITERATOR_OPTIONS_INIT ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expect_iterator_items (int /*<<< orphan*/ *,size_t,char const**,size_t,char const**) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_iterator_for_workdir (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  git_iterator_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_head_tree (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_vector_clear (TYPE_2__*) ; 
 int /*<<< orphan*/  git_vector_free (TYPE_2__*) ; 
 int /*<<< orphan*/  git_vector_init (TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_vector_insert (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  setup_fixture_submod2 () ; 

void test_iterator_workdir__bounded_submodules(void)
{
	git_iterator *i;
	git_iterator_options i_opts = GIT_ITERATOR_OPTIONS_INIT;
	git_vector filelist;
	git_index *index;
	git_tree *head;

	cl_git_pass(git_vector_init(&filelist, 5, NULL));

	g_repo = setup_fixture_submod2();
	cl_git_pass(git_repository_index(&index, g_repo));
	cl_git_pass(git_repository_head_tree(&head, g_repo));

	/* Test that a submodule matches */
	{
		const char *expected[] = { "sm_changed_head" };
		size_t expected_len = 1;

		git_vector_clear(&filelist);
		cl_git_pass(git_vector_insert(&filelist, "sm_changed_head"));

		i_opts.pathlist.strings = (char **)filelist.contents;
		i_opts.pathlist.count = filelist.length;
		i_opts.flags = GIT_ITERATOR_DONT_IGNORE_CASE;

		cl_git_pass(git_iterator_for_workdir(&i, g_repo, index, head, &i_opts));
		expect_iterator_items(i, expected_len, expected, expected_len, expected);
		git_iterator_free(i);
	}

	/* Test that a submodule still matches when suffixed with a '/' */
	{
		const char *expected[] = { "sm_changed_head" };
		size_t expected_len = 1;

		git_vector_clear(&filelist);
		cl_git_pass(git_vector_insert(&filelist, "sm_changed_head/"));

		i_opts.pathlist.strings = (char **)filelist.contents;
		i_opts.pathlist.count = filelist.length;
		i_opts.flags = GIT_ITERATOR_DONT_IGNORE_CASE;

		cl_git_pass(git_iterator_for_workdir(&i, g_repo, index, head, &i_opts));
		expect_iterator_items(i, expected_len, expected, expected_len, expected);
		git_iterator_free(i);
	}

	/* Test that start/end work with a submodule */
	{
		const char *expected[] = { "sm_changed_head", "sm_changed_index" };
		size_t expected_len = 2;

		i_opts.start = "sm_changed_head";
		i_opts.end = "sm_changed_index";
		i_opts.pathlist.strings = NULL;
		i_opts.pathlist.count = 0;
		i_opts.flags = GIT_ITERATOR_DONT_IGNORE_CASE;

		cl_git_pass(git_iterator_for_workdir(&i, g_repo, index, head, &i_opts));
		expect_iterator_items(i, expected_len, expected, expected_len, expected);
		git_iterator_free(i);
	}

	/* Test that start and end allow '/' suffixes of submodules */
	{
		const char *expected[] = { "sm_changed_head", "sm_changed_index" };
		size_t expected_len = 2;

		i_opts.start = "sm_changed_head";
		i_opts.end = "sm_changed_index";
		i_opts.pathlist.strings = NULL;
		i_opts.pathlist.count = 0;
		i_opts.flags = GIT_ITERATOR_DONT_IGNORE_CASE;

		cl_git_pass(git_iterator_for_workdir(&i, g_repo, index, head, &i_opts));
		expect_iterator_items(i, expected_len, expected, expected_len, expected);
		git_iterator_free(i);
	}

	git_vector_free(&filelist);
	git_index_free(index);
	git_tree_free(head);
}
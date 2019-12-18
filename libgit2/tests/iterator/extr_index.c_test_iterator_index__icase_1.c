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
struct TYPE_4__ {char* start; char* end; void* flags; } ;
typedef  TYPE_1__ git_iterator_options ;
typedef  int /*<<< orphan*/  git_iterator ;
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 int GIT_INDEX_CAPABILITY_IGNORE_CASE ; 
 void* GIT_ITERATOR_DONT_AUTOEXPAND ; 
 void* GIT_ITERATOR_INCLUDE_TREES ; 
 TYPE_1__ GIT_ITERATOR_OPTIONS_INIT ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  expect_iterator_items (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_repo ; 
 int git_index_caps (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_set_caps (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  git_iterator_for_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_iterator_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

void test_iterator_index__icase_1(void)
{
	git_iterator *i;
	git_iterator_options i_opts = GIT_ITERATOR_OPTIONS_INIT;
	git_index *index;
	int caps;

	g_repo = cl_git_sandbox_init("icase");

	cl_git_pass(git_repository_index(&index, g_repo));
	caps = git_index_caps(index);

	/* force case sensitivity */
	cl_git_pass(git_index_set_caps(index, caps & ~GIT_INDEX_CAPABILITY_IGNORE_CASE));

	/* autoexpand with no tree entries over range */
	i_opts.start = "c";
	i_opts.end = "k/D";
	cl_git_pass(git_iterator_for_index(&i, g_repo, index, &i_opts));
	expect_iterator_items(i, 7, NULL, 7, NULL);
	git_iterator_free(i);

	i_opts.start = "k";
	i_opts.end = "k/Z";
	cl_git_pass(git_iterator_for_index(&i, g_repo, index, &i_opts));
	expect_iterator_items(i, 3, NULL, 3, NULL);
	git_iterator_free(i);

	/* auto expand with tree entries */
	i_opts.flags = GIT_ITERATOR_INCLUDE_TREES;

	i_opts.start = "c";
	i_opts.end = "k/D";
	cl_git_pass(git_iterator_for_index(&i, g_repo, index, &i_opts));
	expect_iterator_items(i, 8, NULL, 8, NULL);
	git_iterator_free(i);

	i_opts.start = "k";
	i_opts.end = "k/Z";
	cl_git_pass(git_iterator_for_index(&i, g_repo, index, &i_opts));
	expect_iterator_items(i, 4, NULL, 4, NULL);
	git_iterator_free(i);

	/* no auto expand (implies trees included) */
	i_opts.flags = GIT_ITERATOR_DONT_AUTOEXPAND;

	i_opts.start = "c";
	i_opts.end = "k/D";
	cl_git_pass(git_iterator_for_index(&i, g_repo, index, &i_opts));
	expect_iterator_items(i, 5, NULL, 8, NULL);
	git_iterator_free(i);

	i_opts.start = "k";
	i_opts.end = "k/Z";
	cl_git_pass(git_iterator_for_index(&i, g_repo, index, &i_opts));
	expect_iterator_items(i, 1, NULL, 4, NULL);
	git_iterator_free(i);

	/* force case insensitivity */
	cl_git_pass(git_index_set_caps(index, caps | GIT_INDEX_CAPABILITY_IGNORE_CASE));

	/* autoexpand with no tree entries over range */
	i_opts.flags = 0;

	i_opts.start = "c";
	i_opts.end = "k/D";
	cl_git_pass(git_iterator_for_index(&i, g_repo, index, &i_opts));
	expect_iterator_items(i, 13, NULL, 13, NULL);
	git_iterator_free(i);

	i_opts.start = "k";
	i_opts.end = "k/Z";
	cl_git_pass(git_iterator_for_index(&i, g_repo, index, &i_opts));
	expect_iterator_items(i, 5, NULL, 5, NULL);
	git_iterator_free(i);

	/* auto expand with tree entries */
	i_opts.flags = GIT_ITERATOR_INCLUDE_TREES;

	i_opts.start = "c";
	i_opts.end = "k/D";
	cl_git_pass(git_iterator_for_index(&i, g_repo, index, &i_opts));
	expect_iterator_items(i, 14, NULL, 14, NULL);
	git_iterator_free(i);

	i_opts.start = "k";
	i_opts.end = "k/Z";
	cl_git_pass(git_iterator_for_index(&i, g_repo, index, &i_opts));
	expect_iterator_items(i, 6, NULL, 6, NULL);
	git_iterator_free(i);

	/* no auto expand (implies trees included) */
	i_opts.flags = GIT_ITERATOR_DONT_AUTOEXPAND;

	i_opts.start = "c";
	i_opts.end = "k/D";
	cl_git_pass(git_iterator_for_index(&i, g_repo, index, &i_opts));
	expect_iterator_items(i, 9, NULL, 14, NULL);
	git_iterator_free(i);

	i_opts.start = "k";
	i_opts.end = "k/Z";
	cl_git_pass(git_iterator_for_index(&i, g_repo, index, &i_opts));
	expect_iterator_items(i, 1, NULL, 6, NULL);
	git_iterator_free(i);

	cl_git_pass(git_index_set_caps(index, caps));
	git_index_free(index);
}
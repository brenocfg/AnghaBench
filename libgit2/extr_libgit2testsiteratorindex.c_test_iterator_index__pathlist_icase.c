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
struct TYPE_9__ {char** strings; int /*<<< orphan*/  count; } ;
struct TYPE_11__ {char* start; char* end; TYPE_1__ pathlist; } ;
typedef  TYPE_3__ git_iterator_options ;
typedef  int /*<<< orphan*/  git_iterator ;
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 int GIT_INDEX_CAPABILITY_IGNORE_CASE ; 
 TYPE_3__ GIT_ITERATOR_OPTIONS_INIT ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  expect_iterator_items (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git__strcmp_cb ; 
 int git_index_caps (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_set_caps (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  git_iterator_for_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  git_iterator_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_vector_free (TYPE_2__*) ; 
 int /*<<< orphan*/  git_vector_init (TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_vector_insert (TYPE_2__*,char*) ; 

void test_iterator_index__pathlist_icase(void)
{
	git_iterator *i;
	git_iterator_options i_opts = GIT_ITERATOR_OPTIONS_INIT;
	git_index *index;
	int caps;
	git_vector filelist;

	cl_git_pass(git_vector_init(&filelist, 100, &git__strcmp_cb));
	cl_git_pass(git_vector_insert(&filelist, "a"));
	cl_git_pass(git_vector_insert(&filelist, "B"));
	cl_git_pass(git_vector_insert(&filelist, "c"));
	cl_git_pass(git_vector_insert(&filelist, "D"));
	cl_git_pass(git_vector_insert(&filelist, "e"));
	cl_git_pass(git_vector_insert(&filelist, "k/1"));
	cl_git_pass(git_vector_insert(&filelist, "k/a"));
	cl_git_pass(git_vector_insert(&filelist, "L/1"));

	g_repo = cl_git_sandbox_init("icase");

	cl_git_pass(git_repository_index(&index, g_repo));
	caps = git_index_caps(index);

	/* force case sensitivity */
	cl_git_pass(git_index_set_caps(index, caps & ~GIT_INDEX_CAPABILITY_IGNORE_CASE));

	/* All indexfilelist iterator tests are "autoexpand with no tree entries" */

	i_opts.pathlist.strings = (char **)filelist.contents;
	i_opts.pathlist.count = filelist.length;

	i_opts.start = "c";
	i_opts.end = "k/D";
	cl_git_pass(git_iterator_for_index(&i, g_repo, index, &i_opts));
	expect_iterator_items(i, 3, NULL, 3, NULL);
	git_iterator_free(i);

	i_opts.start = "k";
	i_opts.end = "k/Z";
	cl_git_pass(git_iterator_for_index(&i, g_repo, index, &i_opts));
	expect_iterator_items(i, 1, NULL, 1, NULL);
	git_iterator_free(i);

	/* force case insensitivity */
	cl_git_pass(git_index_set_caps(index, caps | GIT_INDEX_CAPABILITY_IGNORE_CASE));

	i_opts.start = "c";
	i_opts.end = "k/D";
	cl_git_pass(git_iterator_for_index(&i, g_repo, index, &i_opts));
	expect_iterator_items(i, 5, NULL, 5, NULL);
	git_iterator_free(i);

	i_opts.start = "k";
	i_opts.end = "k/Z";
	cl_git_pass(git_iterator_for_index(&i, g_repo, index, &i_opts));
	expect_iterator_items(i, 2, NULL, 2, NULL);
	git_iterator_free(i);

	cl_git_pass(git_index_set_caps(index, caps));
	git_index_free(index);
	git_vector_free(&filelist);
}
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
struct TYPE_10__ {char** strings; int /*<<< orphan*/  count; } ;
struct TYPE_12__ {void* flags; TYPE_1__ pathlist; } ;
typedef  TYPE_3__ git_iterator_options ;
typedef  int /*<<< orphan*/  git_iterator ;
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 void* GIT_ITERATOR_DONT_IGNORE_CASE ; 
 void* GIT_ITERATOR_IGNORE_CASE ; 
 TYPE_3__ GIT_ITERATOR_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_ITEROVER ; 
 int /*<<< orphan*/  cl_git_fail_with (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  expect_iterator_items (int /*<<< orphan*/ *,size_t,char const**,size_t,char const**) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_iterator_advance (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_iterator_for_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  git_iterator_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_vector_clear (TYPE_2__*) ; 
 int /*<<< orphan*/  git_vector_free (TYPE_2__*) ; 
 int /*<<< orphan*/  git_vector_init (TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_vector_insert (TYPE_2__*,char*) ; 

void test_iterator_index__pathlist_with_dirs(void)
{
	git_iterator *i;
	git_iterator_options i_opts = GIT_ITERATOR_OPTIONS_INIT;
	git_index *index;
	git_vector filelist;

	cl_git_pass(git_vector_init(&filelist, 5, NULL));

	g_repo = cl_git_sandbox_init("icase");

	cl_git_pass(git_repository_index(&index, g_repo));

	/* Test that a prefix `k` matches folders, even without trailing slash */
	{
		const char *expected[] = { "k/1", "k/B", "k/D", "k/a", "k/c" };
		size_t expected_len = 5;

		git_vector_clear(&filelist);
		cl_git_pass(git_vector_insert(&filelist, "k"));

		i_opts.pathlist.strings = (char **)filelist.contents;
		i_opts.pathlist.count = filelist.length;
		i_opts.flags = GIT_ITERATOR_DONT_IGNORE_CASE;

		cl_git_pass(git_iterator_for_index(&i, g_repo, index, &i_opts));
		expect_iterator_items(i, expected_len, expected, expected_len, expected);
		git_iterator_free(i);
	}

	/* Test that a `k/` matches a folder */
	{
		const char *expected[] = { "k/1", "k/B", "k/D", "k/a", "k/c" };
		size_t expected_len = 5;

		git_vector_clear(&filelist);
		cl_git_pass(git_vector_insert(&filelist, "k/"));

		i_opts.pathlist.strings = (char **)filelist.contents;
		i_opts.pathlist.count = filelist.length;
		i_opts.flags = GIT_ITERATOR_DONT_IGNORE_CASE;

		cl_git_pass(git_iterator_for_index(&i, g_repo, index, &i_opts));
		expect_iterator_items(i, expected_len, expected, expected_len, expected);
		git_iterator_free(i);
	}

	/* When the iterator is case sensitive, ensure we can't lookup the
	 * directory with the wrong case.
	 */
	{
		git_vector_clear(&filelist);
		cl_git_pass(git_vector_insert(&filelist, "K/"));

		i_opts.pathlist.strings = (char **)filelist.contents;
		i_opts.pathlist.count = filelist.length;
		i_opts.flags = GIT_ITERATOR_DONT_IGNORE_CASE;

		cl_git_pass(git_iterator_for_index(&i, g_repo, index, &i_opts));
		cl_git_fail_with(GIT_ITEROVER, git_iterator_advance(NULL, i));
		git_iterator_free(i);
	}

	/* Test that case insensitive matching works. */
	{
		const char *expected[] = { "k/1", "k/a", "k/B", "k/c", "k/D" };
		size_t expected_len = 5;

		git_vector_clear(&filelist);
		cl_git_pass(git_vector_insert(&filelist, "K/"));

		i_opts.pathlist.strings = (char **)filelist.contents;
		i_opts.pathlist.count = filelist.length;
		i_opts.flags = GIT_ITERATOR_IGNORE_CASE;

		cl_git_pass(git_iterator_for_index(&i, g_repo, index, &i_opts));
		expect_iterator_items(i, expected_len, expected, expected_len, expected);
		git_iterator_free(i);
	}

	/* Test that case insensitive matching works without trailing slash. */
	{
		const char *expected[] = { "k/1", "k/a", "k/B", "k/c", "k/D" };
		size_t expected_len = 5;

		git_vector_clear(&filelist);
		cl_git_pass(git_vector_insert(&filelist, "K"));

		i_opts.pathlist.strings = (char **)filelist.contents;
		i_opts.pathlist.count = filelist.length;
		i_opts.flags = GIT_ITERATOR_IGNORE_CASE;

		cl_git_pass(git_iterator_for_index(&i, g_repo, index, &i_opts));
		expect_iterator_items(i, expected_len, expected, expected_len, expected);
		git_iterator_free(i);
	}

	git_index_free(index);
	git_vector_free(&filelist);
}
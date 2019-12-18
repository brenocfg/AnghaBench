#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  length; scalar_t__ contents; } ;
typedef  TYPE_2__ git_vector ;
struct TYPE_14__ {char** strings; int /*<<< orphan*/  count; } ;
struct TYPE_16__ {void* flags; TYPE_1__ pathlist; } ;
typedef  TYPE_3__ git_iterator_options ;
struct TYPE_17__ {int /*<<< orphan*/  stat_calls; } ;
typedef  TYPE_4__ git_iterator ;

/* Variables and functions */
 void* GIT_ITERATOR_DONT_IGNORE_CASE ; 
 TYPE_3__ GIT_ITERATOR_OPTIONS_INIT ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  create_paths (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  expect_iterator_items (TYPE_4__*,size_t,char const**,size_t,char const**) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_iterator_for_workdir (TYPE_4__**,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  git_iterator_free (TYPE_4__*) ; 
 int /*<<< orphan*/  git_repository_workdir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_vector_clear (TYPE_2__*) ; 
 int /*<<< orphan*/  git_vector_free (TYPE_2__*) ; 
 int /*<<< orphan*/  git_vector_init (TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_vector_insert (TYPE_2__*,char*) ; 

void test_iterator_workdir__pathlist_for_deeply_nested_item(void)
{
	git_iterator *i;
	git_iterator_options i_opts = GIT_ITERATOR_OPTIONS_INIT;
	git_vector filelist;

	cl_git_pass(git_vector_init(&filelist, 5, NULL));

	g_repo = cl_git_sandbox_init("icase");
	create_paths(git_repository_workdir(g_repo), 3);

	/* Ensure that we find the single path we're interested in, and we find
	 * it efficiently, and don't stat the entire world to get there.
	 */
	{
		const char *expected[] = { "item1/item3/item5/item7" };
		size_t expected_len = 1;

		git_vector_clear(&filelist);
		cl_git_pass(git_vector_insert(&filelist, "item1/item3/item5/item7"));

		i_opts.pathlist.strings = (char **)filelist.contents;
		i_opts.pathlist.count = filelist.length;
		i_opts.flags = GIT_ITERATOR_DONT_IGNORE_CASE;

		cl_git_pass(git_iterator_for_workdir(&i, g_repo, NULL, NULL, &i_opts));
		expect_iterator_items(i, expected_len, expected, expected_len, expected);
		cl_assert_equal_i(4, i->stat_calls);
		git_iterator_free(i);
	}

	/* Ensure that we find the single path we're interested in, and we find
	 * it efficiently, and don't stat the entire world to get there.
	 */
	{
		const char *expected[] = {
			"item1/item3/item5/item0", "item1/item3/item5/item1",
			"item1/item3/item5/item2", "item1/item3/item5/item3",
			"item1/item3/item5/item4", "item1/item3/item5/item5",
			"item1/item3/item5/item6", "item1/item3/item5/item7",
		};
		size_t expected_len = 8;

		git_vector_clear(&filelist);
		cl_git_pass(git_vector_insert(&filelist, "item1/item3/item5/"));

		i_opts.pathlist.strings = (char **)filelist.contents;
		i_opts.pathlist.count = filelist.length;
		i_opts.flags = GIT_ITERATOR_DONT_IGNORE_CASE;

		cl_git_pass(git_iterator_for_workdir(&i, g_repo, NULL, NULL, &i_opts));
		expect_iterator_items(i, expected_len, expected, expected_len, expected);
		cl_assert_equal_i(11, i->stat_calls);
		git_iterator_free(i);
	}

	/* Ensure that we find the single path we're interested in, and we find
	 * it efficiently, and don't stat the entire world to get there.
	 */
	{
		const char *expected[] = {
			"item1/item3/item0",
			"item1/item3/item1/item0", "item1/item3/item1/item1",
			"item1/item3/item1/item2", "item1/item3/item1/item3",
			"item1/item3/item1/item4", "item1/item3/item1/item5",
			"item1/item3/item1/item6", "item1/item3/item1/item7",
			"item1/item3/item2",
			"item1/item3/item3/item0", "item1/item3/item3/item1",
			"item1/item3/item3/item2", "item1/item3/item3/item3",
			"item1/item3/item3/item4", "item1/item3/item3/item5",
			"item1/item3/item3/item6", "item1/item3/item3/item7",
			"item1/item3/item4",
			"item1/item3/item5/item0", "item1/item3/item5/item1",
			"item1/item3/item5/item2", "item1/item3/item5/item3",
			"item1/item3/item5/item4", "item1/item3/item5/item5",
			"item1/item3/item5/item6", "item1/item3/item5/item7",
			"item1/item3/item6",
			"item1/item3/item7/item0", "item1/item3/item7/item1",
			"item1/item3/item7/item2", "item1/item3/item7/item3",
			"item1/item3/item7/item4", "item1/item3/item7/item5",
			"item1/item3/item7/item6", "item1/item3/item7/item7",
		};
		size_t expected_len = 36;

		git_vector_clear(&filelist);
		cl_git_pass(git_vector_insert(&filelist, "item1/item3/"));

		i_opts.pathlist.strings = (char **)filelist.contents;
		i_opts.pathlist.count = filelist.length;
		i_opts.flags = GIT_ITERATOR_DONT_IGNORE_CASE;

		cl_git_pass(git_iterator_for_workdir(&i, g_repo, NULL, NULL, &i_opts));
		expect_iterator_items(i, expected_len, expected, expected_len, expected);
		cl_assert_equal_i(42, i->stat_calls);
		git_iterator_free(i);
	}

	/* Ensure that we find the single path we're interested in, and we find
	 * it efficiently, and don't stat the entire world to get there.
	 */
	{
		const char *expected[] = {
			"item0", "item1/item2", "item5/item7/item4", "item6",
			"item7/item3/item1/item6" };
		size_t expected_len = 5;

		git_vector_clear(&filelist);
		cl_git_pass(git_vector_insert(&filelist, "item7/item3/item1/item6"));
		cl_git_pass(git_vector_insert(&filelist, "item6"));
		cl_git_pass(git_vector_insert(&filelist, "item5/item7/item4"));
		cl_git_pass(git_vector_insert(&filelist, "item1/item2"));
		cl_git_pass(git_vector_insert(&filelist, "item0"));

		/* also add some things that don't exist or don't match the right type */
		cl_git_pass(git_vector_insert(&filelist, "item2/"));
		cl_git_pass(git_vector_insert(&filelist, "itemN"));
		cl_git_pass(git_vector_insert(&filelist, "item1/itemA"));
		cl_git_pass(git_vector_insert(&filelist, "item5/item3/item4/"));

		i_opts.pathlist.strings = (char **)filelist.contents;
		i_opts.pathlist.count = filelist.length;
		i_opts.flags = GIT_ITERATOR_DONT_IGNORE_CASE;

		cl_git_pass(git_iterator_for_workdir(&i, g_repo, NULL, NULL, &i_opts));
		expect_iterator_items(i, expected_len, expected, expected_len, expected);
		cl_assert_equal_i(14, i->stat_calls);
		git_iterator_free(i);
	}

	git_vector_free(&filelist);
}
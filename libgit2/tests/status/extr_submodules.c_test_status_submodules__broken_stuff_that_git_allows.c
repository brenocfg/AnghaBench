#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  entry_count; } ;
typedef  TYPE_1__ status_entry_counts ;
struct TYPE_8__ {int flags; } ;
typedef  TYPE_2__ git_status_options ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_RMDIR_REMOVE_FILES ; 
#define  GIT_STATUS_IGNORED 132 
#define  GIT_STATUS_INDEX_DELETED 131 
#define  GIT_STATUS_INDEX_NEW 130 
 TYPE_2__ GIT_STATUS_OPTIONS_INIT ; 
 int GIT_STATUS_OPT_INCLUDE_IGNORED ; 
 int GIT_STATUS_OPT_INCLUDE_UNTRACKED ; 
 int GIT_STATUS_OPT_RECURSE_UNTRACKED_DIRS ; 
#define  GIT_STATUS_WT_MODIFIED 129 
#define  GIT_STATUS_WT_NEW 128 
 int /*<<< orphan*/  cb_status__match ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_append2file (char*,char*) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_must_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_futils_rmdir_r (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_add_bypath (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_init (int /*<<< orphan*/ **,char*,int) ; 
 int /*<<< orphan*/  git_status_foreach_ext (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  p_mkdir (char*,int) ; 
 int /*<<< orphan*/  setup_fixture_submodules () ; 
 int /*<<< orphan*/  status_counts_init (TYPE_1__,char const**,unsigned int*) ; 

void test_status_submodules__broken_stuff_that_git_allows(void)
{
	git_status_options opts = GIT_STATUS_OPTIONS_INIT;
	status_entry_counts counts;
	git_repository *contained;
	static const char *expected_files_with_broken[] = {
		".gitmodules",
		"added",
		"broken/tracked",
		"deleted",
		"ignored",
		"modified",
		"untracked"
	};
	static unsigned int expected_status_with_broken[] = {
		GIT_STATUS_WT_MODIFIED,
		GIT_STATUS_INDEX_NEW,
		GIT_STATUS_INDEX_NEW,
		GIT_STATUS_INDEX_DELETED,
		GIT_STATUS_IGNORED,
		GIT_STATUS_WT_MODIFIED,
		GIT_STATUS_WT_NEW,
	};

	g_repo = setup_fixture_submodules();

	opts.flags = GIT_STATUS_OPT_INCLUDE_UNTRACKED |
		GIT_STATUS_OPT_RECURSE_UNTRACKED_DIRS |
		GIT_STATUS_OPT_INCLUDE_IGNORED;

	/* make a directory and stick a tracked item into the index */
	{
		git_index *idx;
		cl_must_pass(p_mkdir("submodules/broken", 0777));
		cl_git_mkfile("submodules/broken/tracked", "tracked content");
		cl_git_pass(git_repository_index(&idx, g_repo));
		cl_git_pass(git_index_add_bypath(idx, "broken/tracked"));
		cl_git_pass(git_index_write(idx));
		git_index_free(idx);
	}

	status_counts_init(
		counts, expected_files_with_broken, expected_status_with_broken);
	cl_git_pass(git_status_foreach_ext(
		g_repo, &opts, cb_status__match, &counts));
	cl_assert_equal_i(7, counts.entry_count);

	/* directory with tracked items that looks a little bit like a repo */

	cl_must_pass(p_mkdir("submodules/broken/.git", 0777));
	cl_must_pass(p_mkdir("submodules/broken/.git/info", 0777));
	cl_git_mkfile("submodules/broken/.git/info/exclude", "# bogus");

	status_counts_init(
		counts, expected_files_with_broken, expected_status_with_broken);
	cl_git_pass(git_status_foreach_ext(
		g_repo, &opts, cb_status__match, &counts));
	cl_assert_equal_i(7, counts.entry_count);

	/* directory with tracked items that is a repo */

	cl_git_pass(git_futils_rmdir_r(
		"submodules/broken/.git", NULL, GIT_RMDIR_REMOVE_FILES));
	cl_git_pass(git_repository_init(&contained, "submodules/broken", false));
	git_repository_free(contained);

	status_counts_init(
		counts, expected_files_with_broken, expected_status_with_broken);
	cl_git_pass(git_status_foreach_ext(
		g_repo, &opts, cb_status__match, &counts));
	cl_assert_equal_i(7, counts.entry_count);

	/* directory with tracked items that claims to be a submodule but is not */

	cl_git_pass(git_futils_rmdir_r(
		"submodules/broken/.git", NULL, GIT_RMDIR_REMOVE_FILES));
	cl_git_append2file("submodules/.gitmodules",
		"\n[submodule \"broken\"]\n"
		"\tpath = broken\n"
		"\turl = https://github.com/not/used\n\n");

	status_counts_init(
		counts, expected_files_with_broken, expected_status_with_broken);
	cl_git_pass(git_status_foreach_ext(
		g_repo, &opts, cb_status__match, &counts));
	cl_assert_equal_i(7, counts.entry_count);
}
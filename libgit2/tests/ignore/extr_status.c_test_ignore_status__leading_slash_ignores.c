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
struct TYPE_7__ {int expected_entry_count; char const** expected_paths; unsigned int const* expected_statuses; int /*<<< orphan*/  wrong_sorted_path; int /*<<< orphan*/  wrong_status_flags_count; int /*<<< orphan*/  entry_count; } ;
typedef  TYPE_1__ status_entry_counts ;
struct TYPE_8__ {int flags; } ;
typedef  TYPE_2__ git_status_options ;
typedef  int /*<<< orphan*/  git_config ;

/* Variables and functions */
#define  GIT_STATUS_IGNORED 129 
 TYPE_2__ GIT_STATUS_OPTIONS_INIT ; 
 int GIT_STATUS_OPT_DEFAULTS ; 
 int GIT_STATUS_OPT_RECURSE_IGNORED_DIRS ; 
#define  GIT_STATUS_WT_NEW 128 
 int /*<<< orphan*/  cb_status__normal ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_fake_home () ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_rewritefile (char*,char*) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_set_string (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  git_repository_config (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_status_foreach_ext (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  make_test_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  test_files_1 ; 
 int /*<<< orphan*/  test_repo_1 ; 

void test_ignore_status__leading_slash_ignores(void)
{
	git_status_options opts = GIT_STATUS_OPTIONS_INIT;
	status_entry_counts counts;
	static const char *paths_2[] = {
		"dir/.gitignore",
		"dir/a/ignore_me",
		"dir/b/ignore_me",
		"dir/ignore_me",
		"ignore_also/file",
		"ignore_me",
		"test/.gitignore",
		"test/ignore_me/and_me/file",
		"test/ignore_me/file",
		"test/ignore_me/file2",
	};
	static const unsigned int statuses_2[] = {
		GIT_STATUS_WT_NEW,  GIT_STATUS_WT_NEW,  GIT_STATUS_WT_NEW,
		GIT_STATUS_IGNORED, GIT_STATUS_IGNORED, GIT_STATUS_IGNORED,
		GIT_STATUS_WT_NEW, GIT_STATUS_WT_NEW, GIT_STATUS_WT_NEW, GIT_STATUS_WT_NEW,
	};

	make_test_data(test_repo_1, test_files_1);

	cl_fake_home();
	cl_git_mkfile("home/.gitignore", "/ignore_me\n");
	{
		git_config *cfg;
		cl_git_pass(git_repository_config(&cfg, g_repo));
		cl_git_pass(git_config_set_string(
			cfg, "core.excludesfile", "~/.gitignore"));
		git_config_free(cfg);
	}

	cl_git_rewritefile("empty_standard_repo/.git/info/exclude", "/ignore_also\n");
	cl_git_rewritefile("empty_standard_repo/dir/.gitignore", "/ignore_me\n");
	cl_git_rewritefile("empty_standard_repo/test/.gitignore", "/and_me\n");

	memset(&counts, 0x0, sizeof(status_entry_counts));
	counts.expected_entry_count = 10;
	counts.expected_paths = paths_2;
	counts.expected_statuses = statuses_2;

	opts.flags = GIT_STATUS_OPT_DEFAULTS | GIT_STATUS_OPT_RECURSE_IGNORED_DIRS;

	cl_git_pass(git_status_foreach_ext(
		g_repo, &opts, cb_status__normal, &counts));

	cl_assert_equal_i(counts.expected_entry_count, counts.entry_count);
	cl_assert_equal_i(0, counts.wrong_status_flags_count);
	cl_assert_equal_i(0, counts.wrong_sorted_path);
}
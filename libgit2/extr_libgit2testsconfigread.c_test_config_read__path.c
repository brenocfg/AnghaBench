#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_config ;
struct TYPE_13__ {struct TYPE_13__* ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_CONFIG_LEVEL_GLOBAL ; 
 int /*<<< orphan*/  GIT_OPT_GET_SEARCH_PATH ; 
 int /*<<< orphan*/  GIT_OPT_SET_SEARCH_PATH ; 
 int /*<<< orphan*/  cl_assert_equal_s (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_sets (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_get_path (TYPE_1__*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_config_open_ondisk (int /*<<< orphan*/ **,char*) ; 
 int /*<<< orphan*/  git_libgit2_opts (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  git_path_join_unrooted (TYPE_1__*,char*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_path_prettify (TYPE_1__*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p_mkdir (char*,int) ; 

void test_config_read__path(void)
{
	git_config *cfg;
	git_buf path = GIT_BUF_INIT;
	git_buf old_path = GIT_BUF_INIT;
	git_buf home_path = GIT_BUF_INIT;
	git_buf expected_path = GIT_BUF_INIT;

	cl_git_pass(p_mkdir("fakehome", 0777));
	cl_git_pass(git_path_prettify(&home_path, "fakehome", NULL));
	cl_git_pass(git_libgit2_opts(GIT_OPT_GET_SEARCH_PATH, GIT_CONFIG_LEVEL_GLOBAL, &old_path));
	cl_git_pass(git_libgit2_opts(GIT_OPT_SET_SEARCH_PATH, GIT_CONFIG_LEVEL_GLOBAL, home_path.ptr));
	cl_git_mkfile("./testconfig", "[some]\n path = ~/somefile");
	cl_git_pass(git_path_join_unrooted(&expected_path, "somefile", home_path.ptr, NULL));

	cl_git_pass(git_config_open_ondisk(&cfg, "./testconfig"));
	cl_git_pass(git_config_get_path(&path, cfg, "some.path"));
	cl_assert_equal_s(expected_path.ptr, path.ptr);
	git_buf_dispose(&path);

	cl_git_mkfile("./testconfig", "[some]\n path = ~/");
	cl_git_pass(git_path_join_unrooted(&expected_path, "", home_path.ptr, NULL));

	cl_git_pass(git_config_get_path(&path, cfg, "some.path"));
	cl_assert_equal_s(expected_path.ptr, path.ptr);
	git_buf_dispose(&path);

	cl_git_mkfile("./testconfig", "[some]\n path = ~");
	cl_git_pass(git_buf_sets(&expected_path, home_path.ptr));

	cl_git_pass(git_config_get_path(&path, cfg, "some.path"));
	cl_assert_equal_s(expected_path.ptr, path.ptr);
	git_buf_dispose(&path);

	cl_git_mkfile("./testconfig", "[some]\n path = ~user/foo");
	cl_git_fail(git_config_get_path(&path, cfg, "some.path"));

	cl_git_pass(git_libgit2_opts(GIT_OPT_SET_SEARCH_PATH, GIT_CONFIG_LEVEL_GLOBAL, old_path.ptr));
	git_buf_dispose(&old_path);
	git_buf_dispose(&home_path);
	git_buf_dispose(&expected_path);
	git_config_free(cfg);
}
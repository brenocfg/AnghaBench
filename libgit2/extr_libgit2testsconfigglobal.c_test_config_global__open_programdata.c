#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_config ;
struct TYPE_7__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_CONFIG_LEVEL_PROGRAMDATA ; 
 int /*<<< orphan*/  GIT_OPT_GET_SEARCH_PATH ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_fixture_cleanup (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 scalar_t__ cl_is_env_set (char*) ; 
 int /*<<< orphan*/  cl_skip () ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_puts (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_get_string_buf (TYPE_1__*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_config_open_default (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  git_config_open_ondisk (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config_set_string (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  git_libgit2_opts (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  git_path_isdir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_config (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_init (int /*<<< orphan*/ **,char*,int) ; 
 int /*<<< orphan*/  p_mkdir (int /*<<< orphan*/ ,int) ; 

void test_config_global__open_programdata(void)
{
	git_config *cfg;
	git_repository *repo;
	git_buf config_path = GIT_BUF_INIT;
	git_buf var_contents = GIT_BUF_INIT;

	if (cl_is_env_set("GITTEST_INVASIVE_FS_STRUCTURE"))
		cl_skip();

	cl_git_pass(git_libgit2_opts(GIT_OPT_GET_SEARCH_PATH,
		GIT_CONFIG_LEVEL_PROGRAMDATA, &config_path));

	if (!git_path_isdir(config_path.ptr))
		cl_git_pass(p_mkdir(config_path.ptr, 0777));

	cl_git_pass(git_buf_puts(&config_path, "/config"));

	cl_git_pass(git_config_open_ondisk(&cfg, config_path.ptr));
	cl_git_pass(git_config_set_string(cfg, "programdata.var", "even higher level"));

	git_buf_dispose(&config_path);
	git_config_free(cfg);

	git_config_open_default(&cfg);
	cl_git_pass(git_config_get_string_buf(&var_contents, cfg, "programdata.var"));
	cl_assert_equal_s("even higher level", var_contents.ptr);

	git_config_free(cfg);
	git_buf_dispose(&var_contents);

	cl_git_pass(git_repository_init(&repo, "./foo.git", true));
	cl_git_pass(git_repository_config(&cfg, repo));
	cl_git_pass(git_config_get_string_buf(&var_contents, cfg, "programdata.var"));
	cl_assert_equal_s("even higher level", var_contents.ptr);

	git_config_free(cfg);
	git_buf_dispose(&var_contents);
	git_repository_free(repo);
	cl_fixture_cleanup("./foo.git");
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_config ;
struct TYPE_5__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_CONFIG_LEVEL_GLOBAL ; 
 int /*<<< orphan*/  GIT_OPT_SET_SEARCH_PATH ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_must_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_joinpath (TYPE_1__*,char const*,char*) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_open_ondisk (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config_set_string (int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/  git_libgit2_opts (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  p_mkdir (char const*,int) ; 

void create_tmp_global_config(const char *dirname, const char *key, const char *val)
{
	git_buf path = GIT_BUF_INIT;
	git_config *config;

	cl_git_pass(git_libgit2_opts(GIT_OPT_SET_SEARCH_PATH,
		GIT_CONFIG_LEVEL_GLOBAL, dirname));
	cl_must_pass(p_mkdir(dirname, 0777));
	cl_git_pass(git_buf_joinpath(&path, dirname, ".gitconfig"));
	cl_git_pass(git_config_open_ondisk(&config, path.ptr));
	cl_git_pass(git_config_set_string(config, key, val));
	git_config_free(config);
	git_buf_dispose(&path);
}
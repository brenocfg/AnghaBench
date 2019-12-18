#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_config ;

/* Variables and functions */
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 scalar_t__ git_config_get_bool (int*,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  git_error_clear () ; 
 int /*<<< orphan*/  git_repository_config (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

int cl_repo_get_bool(git_repository *repo, const char *cfg)
{
	int val = 0;
	git_config *config;
	cl_git_pass(git_repository_config(&config, repo));
	if (git_config_get_bool(&val, config, cfg) < 0)
		git_error_clear();
	git_config_free(config);
	return val;
}
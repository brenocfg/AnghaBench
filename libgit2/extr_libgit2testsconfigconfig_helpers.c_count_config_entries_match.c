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
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  count_config_entries_cb ; 
 int /*<<< orphan*/  git_config_foreach_match (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_config (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

int count_config_entries_match(git_repository *repo, const char *pattern)
{
	git_config *config;
	int how_many = 0;

	cl_git_pass(git_repository_config(&config, repo));

	cl_assert_equal_i(0, git_config_foreach_match(
		config,	pattern, count_config_entries_cb, &how_many));

	git_config_free(config);

	return how_many;
}
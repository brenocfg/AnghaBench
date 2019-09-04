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
typedef  int /*<<< orphan*/  git_config_entry ;
typedef  int /*<<< orphan*/  git_config ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ENOTFOUND ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cl_git_pass (int) ; 
 int /*<<< orphan*/  git_config_entry_free (int /*<<< orphan*/ *) ; 
 int git_config_get_entry (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*) ; 
 int git_repository_config__weakptr (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

void assert_config_entry_existence(
	git_repository *repo,
	const char *name,
	bool is_supposed_to_exist)
{
	git_config *config;
	git_config_entry *entry = NULL;
	int result;

	cl_git_pass(git_repository_config__weakptr(&config, repo));
	
	result = git_config_get_entry(&entry, config, name);
	git_config_entry_free(entry);

	if (is_supposed_to_exist)
		cl_git_pass(result);
	else
		cl_assert_equal_i(GIT_ENOTFOUND, result);
}
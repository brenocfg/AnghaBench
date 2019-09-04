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
typedef  int /*<<< orphan*/  git_submodule ;
typedef  int /*<<< orphan*/  git_repository ;

/* Variables and functions */
 int /*<<< orphan*/  assert_config_entry_value (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * g_repo ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_submodule_open (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_submodule_url (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void assert_submodule_url_is_synced(
	git_submodule *sm, const char *parent_key, const char *child_key)
{
	git_repository *smrepo;

	assert_config_entry_value(g_repo, parent_key, git_submodule_url(sm));

	cl_git_pass(git_submodule_open(&smrepo, sm));
	assert_config_entry_value(smrepo, child_key,  git_submodule_url(sm));
	git_repository_free(smrepo);
}
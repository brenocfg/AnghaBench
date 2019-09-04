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
typedef  int /*<<< orphan*/  git_config ;

/* Variables and functions */
 int /*<<< orphan*/  assert_no_reflog_update () ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_config_delete_entry (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_config (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

void test_refs_reflog_reflog__logallrefupdates_bare_unset(void)
{
	git_config *config;

	cl_git_pass(git_repository_config(&config, g_repo));
	cl_git_pass(git_config_delete_entry(config, "core.logallrefupdates"));
	git_config_free(config);

	assert_no_reflog_update();
}
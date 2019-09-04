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
 int /*<<< orphan*/  FETCH_HEAD_NO_MERGE_DATA ; 
 int /*<<< orphan*/  FETCH_HEAD_NO_MERGE_DATA2 ; 
 int /*<<< orphan*/  FETCH_HEAD_NO_MERGE_DATA3 ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fetchhead_test_clone () ; 
 int /*<<< orphan*/  fetchhead_test_fetch (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_config_delete_entry (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_config (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_tag_delete (int /*<<< orphan*/ ,char*) ; 

void test_online_fetchhead__no_merges(void)
{
	git_config *config;

	fetchhead_test_clone();

	cl_git_pass(git_repository_config(&config, g_repo));
	cl_git_pass(git_config_delete_entry(config, "branch.master.remote"));
	cl_git_pass(git_config_delete_entry(config, "branch.master.merge"));
	git_config_free(config);

	fetchhead_test_fetch(NULL, FETCH_HEAD_NO_MERGE_DATA2);
	cl_git_pass(git_tag_delete(g_repo, "annotated_tag"));
	cl_git_pass(git_tag_delete(g_repo, "blob"));
	cl_git_pass(git_tag_delete(g_repo, "commit_tree"));
	cl_git_pass(git_tag_delete(g_repo, "nearly-dangling"));
	fetchhead_test_fetch(NULL, FETCH_HEAD_NO_MERGE_DATA);
	cl_git_pass(git_tag_delete(g_repo, "commit_tree"));
	fetchhead_test_fetch(NULL, FETCH_HEAD_NO_MERGE_DATA3);
}
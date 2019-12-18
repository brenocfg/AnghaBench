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
 int /*<<< orphan*/  AUTOMERGEABLE_IDSTR ; 
 int /*<<< orphan*/  TEST_REPO_PATH ; 
 int /*<<< orphan*/  automergeable_id ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_set_bool (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  git_config_set_string (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_config (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  repo ; 
 int /*<<< orphan*/  repo_index ; 
 int /*<<< orphan*/  test_drivers_register () ; 

void test_merge_driver__initialize(void)
{
    git_config *cfg;

    repo = cl_git_sandbox_init(TEST_REPO_PATH);
    git_repository_index(&repo_index, repo);

	git_oid_fromstr(&automergeable_id, AUTOMERGEABLE_IDSTR);

    /* Ensure that the user's merge.conflictstyle doesn't interfere */
    cl_git_pass(git_repository_config(&cfg, repo));

    cl_git_pass(git_config_set_string(cfg, "merge.conflictstyle", "merge"));
    cl_git_pass(git_config_set_bool(cfg, "core.autocrlf", false));

	test_drivers_register();

    git_config_free(cfg);
}
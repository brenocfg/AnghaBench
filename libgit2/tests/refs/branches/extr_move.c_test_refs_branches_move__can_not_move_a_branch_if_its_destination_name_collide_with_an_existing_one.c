#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_config ;
typedef  int /*<<< orphan*/  git_buf ;
struct TYPE_2__ {int /*<<< orphan*/ * message; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_EEXISTS ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,char const*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git__free (char*) ; 
 int /*<<< orphan*/  git_branch_move (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 char* git_buf_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_get_string (char const**,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_config_get_string_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 TYPE_1__* git_error_last () ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_repository_config_snapshot (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  repo ; 

void test_refs_branches_move__can_not_move_a_branch_if_its_destination_name_collide_with_an_existing_one(void)
{
	git_reference *original_ref, *new_ref;
	git_config *config;
	git_buf buf = GIT_BUF_INIT;
	char *original_remote, *original_merge;
	const char *str;

	cl_git_pass(git_repository_config_snapshot(&config, repo));

	cl_git_pass(git_config_get_string_buf(&buf, config, "branch.master.remote"));
	original_remote = git_buf_detach(&buf);
	cl_git_pass(git_config_get_string_buf(&buf, config, "branch.master.merge"));
	original_merge  = git_buf_detach(&buf);
	git_config_free(config);

	cl_git_pass(git_reference_lookup(&original_ref, repo, "refs/heads/br2"));

	cl_assert_equal_i(GIT_EEXISTS,
		git_branch_move(&new_ref, original_ref, "master", 0));

	cl_assert(git_error_last()->message != NULL);

	cl_git_pass(git_repository_config_snapshot(&config, repo));
	cl_git_pass(git_config_get_string(&str, config, "branch.master.remote"));
	cl_assert_equal_s(original_remote, str);
	cl_git_pass(git_config_get_string(&str, config, "branch.master.merge"));
	cl_assert_equal_s(original_merge,  str);
	git_config_free(config);

	cl_assert_equal_i(GIT_EEXISTS,
		git_branch_move(&new_ref, original_ref, "cannot-fetch", 0));

	cl_assert(git_error_last()->message != NULL);

	cl_git_pass(git_repository_config_snapshot(&config, repo));
	cl_git_pass(git_config_get_string(&str, config, "branch.master.remote"));
	cl_assert_equal_s(original_remote, str);
	cl_git_pass(git_config_get_string(&str, config, "branch.master.merge"));
	cl_assert_equal_s(original_merge,  str);
	git_config_free(config);

	git_reference_free(original_ref);
	cl_git_pass(git_reference_lookup(&original_ref, repo, "refs/heads/track-local"));

	cl_assert_equal_i(GIT_EEXISTS,
		git_branch_move(&new_ref, original_ref, "master", 0));

	cl_assert(git_error_last()->message != NULL);

	cl_git_pass(git_repository_config_snapshot(&config, repo));
	cl_git_pass(git_config_get_string(&str, config, "branch.master.remote"));
	cl_assert_equal_s(original_remote, str);
	cl_git_pass(git_config_get_string(&str, config, "branch.master.merge"));
	cl_assert_equal_s(original_merge,  str);

	git__free(original_remote); git__free(original_merge);
	git_reference_free(original_ref);
	git_config_free(config);
}
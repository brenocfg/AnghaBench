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
struct merge_index_entry {int member_0; char* member_1; int member_2; char* member_3; } ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_object ;
typedef  int /*<<< orphan*/  git_config ;
typedef  int /*<<< orphan*/  git_commit ;
struct TYPE_5__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_RESET_HARD ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_commit_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_set_bool (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_futils_readbuffer (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_repository_config (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_revert (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  merge_test_index (int /*<<< orphan*/ ,struct merge_index_entry*,int) ; 
 int /*<<< orphan*/  repo ; 
 int /*<<< orphan*/  repo_index ; 

void test_revert_workdir__again_after_edit_two(void)
{
	git_buf diff_buf = GIT_BUF_INIT;
	git_config *config;
	git_oid head_commit_oid, revert_commit_oid;
	git_commit *head_commit, *revert_commit;

	struct merge_index_entry merge_index_entries[] = {
		{ 0100644, "a8c86221b400b836010567cc3593db6e96c1a83a", 1, "file.txt" },
		{ 0100644, "46ff0854663aeb2182b9838c8da68e33ac23bc1e", 2, "file.txt" },
		{ 0100644, "21a96a98ed84d45866e1de6e266fd3a61a4ae9dc", 3, "file.txt" },
	};

	cl_git_pass(git_repository_config(&config, repo));
	cl_git_pass(git_config_set_bool(config, "core.autocrlf", 0));

	cl_git_pass(git_oid_fromstr(&head_commit_oid, "75ec9929465623f17ff3ad68c0438ea56faba815"));
	cl_git_pass(git_commit_lookup(&head_commit, repo, &head_commit_oid));
	cl_git_pass(git_reset(repo, (git_object *)head_commit, GIT_RESET_HARD, NULL));

	cl_git_pass(git_oid_fromstr(&revert_commit_oid, "97e52d5e81f541080cd6b92829fb85bc4d81d90b"));
	cl_git_pass(git_commit_lookup(&revert_commit, repo, &revert_commit_oid));

	cl_git_pass(git_revert(repo, revert_commit, NULL));

	cl_assert(merge_test_index(repo_index, merge_index_entries, 3));

	cl_git_pass(git_futils_readbuffer(&diff_buf, "revert/file.txt"));
	cl_assert_equal_s(
			"a\n" \
			"<<<<<<< HEAD\n" \
			"=======\n" \
			"a\n" \
			">>>>>>> parent of 97e52d5... Revert me\n" \
			"a\n" \
			"a\n" \
			"a\n" \
			"a\n" \
			"ab",
		diff_buf.ptr);

	git_commit_free(revert_commit);
	git_commit_free(head_commit);
	git_config_free(config);
	git_buf_dispose(&diff_buf);
}
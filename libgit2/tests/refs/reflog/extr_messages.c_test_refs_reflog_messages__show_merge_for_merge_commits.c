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
struct git_commit {int dummy; } ;
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_signature ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_commit ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_HEAD_FILE ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_reflog_check_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_commit_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int,struct git_commit const**) ; 
 int /*<<< orphan*/  git_commit_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_tree (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_tostr_s (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_name_to_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_signature_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_signature_now (int /*<<< orphan*/ **,char*,char*) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 

void test_refs_reflog_messages__show_merge_for_merge_commits(void)
{
	git_oid b1_oid;
	git_oid b2_oid;
	git_oid merge_commit_oid;
	git_commit *b1_commit;
	git_commit *b2_commit;
	git_signature *s;
	git_commit *parent_commits[2];
	git_tree *tree;

	cl_git_pass(git_signature_now(&s, "alice", "alice@example.com"));

	cl_git_pass(git_reference_name_to_id(&b1_oid, g_repo, "HEAD"));
	cl_git_pass(git_reference_name_to_id(&b2_oid, g_repo, "refs/heads/test"));

	cl_git_pass(git_commit_lookup(&b1_commit, g_repo, &b1_oid));
	cl_git_pass(git_commit_lookup(&b2_commit, g_repo, &b2_oid));

	parent_commits[0] = b1_commit;
	parent_commits[1] = b2_commit;

	cl_git_pass(git_commit_tree(&tree, b1_commit));

	cl_git_pass(git_commit_create(&merge_commit_oid,
		g_repo, "HEAD", s, s, NULL,
		"Merge commit", tree,
		2, (const struct git_commit **) parent_commits));

	cl_reflog_check_entry(g_repo, GIT_HEAD_FILE, 0,
		NULL,
		git_oid_tostr_s(&merge_commit_oid),
		NULL, "commit (merge): Merge commit");

	git_tree_free(tree);
	git_commit_free(b1_commit);
	git_commit_free(b2_commit);
	git_signature_free(s);
}
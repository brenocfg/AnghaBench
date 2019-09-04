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
typedef  int /*<<< orphan*/  git_signature ;
typedef  int /*<<< orphan*/  git_object ;
typedef  int /*<<< orphan*/  git_annotated_commit ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_HEAD_FILE ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_reflog_check_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_annotated_commit_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_annotated_commit_from_revspec (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_object_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_set_head (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_repository_set_head_detached (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_set_head_detached_from_annotated (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_revparse_single (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_signature_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_signature_now (int /*<<< orphan*/ **,char*,char*) ; 

void test_refs_reflog_messages__setting_head_updates_reflog(void)
{
	git_object *tag;
	git_signature *sig;
	git_annotated_commit *annotated;

	cl_git_pass(git_signature_now(&sig, "me", "foo@example.com"));

	cl_git_pass(git_repository_set_head(g_repo, "refs/heads/haacked")); /* 4 */
	cl_git_pass(git_repository_set_head(g_repo, "refs/heads/unborn"));
	cl_git_pass(git_revparse_single(&tag, g_repo, "tags/test"));
	cl_git_pass(git_repository_set_head_detached(g_repo, git_object_id(tag))); /* 3 */
	cl_git_pass(git_repository_set_head(g_repo, "refs/heads/haacked"));        /* 2 */
	cl_git_pass(git_repository_set_head(g_repo, "refs/tags/test"));            /* 1 */
	cl_git_pass(git_repository_set_head(g_repo, "refs/remotes/test/master"));  /* 0 */

	cl_reflog_check_entry(g_repo, GIT_HEAD_FILE, 4,
		NULL, "refs/heads/haacked",
		"foo@example.com",
		"checkout: moving from master to haacked");
	cl_reflog_check_entry(g_repo, GIT_HEAD_FILE, 3,
		NULL, "tags/test^{commit}",
		"foo@example.com",
		"checkout: moving from unborn to e90810b8df3e80c413d903f631643c716887138d");
	cl_reflog_check_entry(g_repo, GIT_HEAD_FILE, 2,
		"tags/test^{commit}", "refs/heads/haacked",
		"foo@example.com",
		"checkout: moving from e90810b8df3e80c413d903f631643c716887138d to haacked");
	cl_reflog_check_entry(g_repo, GIT_HEAD_FILE, 1,
		"refs/heads/haacked", "tags/test^{commit}",
		"foo@example.com",
		"checkout: moving from haacked to test");
	cl_reflog_check_entry(g_repo, GIT_HEAD_FILE, 0,
		"tags/test^{commit}", "refs/remotes/test/master",
		"foo@example.com",
		"checkout: moving from e90810b8df3e80c413d903f631643c716887138d to test/master");

	cl_git_pass(git_annotated_commit_from_revspec(&annotated, g_repo, "haacked~0"));
	cl_git_pass(git_repository_set_head_detached_from_annotated(g_repo, annotated));

	cl_reflog_check_entry(g_repo, GIT_HEAD_FILE, 0,
		NULL, "refs/heads/haacked",
		"foo@example.com",
		"checkout: moving from be3563ae3f795b2b4353bcce3a527ad0a4f7f644 to haacked~0");

	git_annotated_commit_free(annotated);
	git_object_free(tag);
	git_signature_free(sig);
}
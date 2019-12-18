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
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_HEAD_FILE ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_reflog_check_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_repository_set_head (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_repository_set_head_detached (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_signature_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_signature_now (int /*<<< orphan*/ **,char*,char*) ; 

void test_refs_reflog_messages__detaching_writes_reflog(void)
{
	git_signature *sig;
	git_oid id;
	const char *msg;

	cl_git_pass(git_signature_now(&sig, "me", "foo@example.com"));

	msg = "checkout: moving from master to e90810b8df3e80c413d903f631643c716887138d";
	git_oid_fromstr(&id, "e90810b8df3e80c413d903f631643c716887138d");
	cl_git_pass(git_repository_set_head_detached(g_repo, &id));
	cl_reflog_check_entry(g_repo, GIT_HEAD_FILE, 0,
		"a65fedf39aefe402d3bb6e24df4d4f5fe4547750",
		"e90810b8df3e80c413d903f631643c716887138d",
		NULL, msg);

	msg = "checkout: moving from e90810b8df3e80c413d903f631643c716887138d to haacked";
	cl_git_pass(git_repository_set_head(g_repo, "refs/heads/haacked"));
	cl_reflog_check_entry(g_repo, GIT_HEAD_FILE, 0,
		"e90810b8df3e80c413d903f631643c716887138d",
		"258f0e2a959a364e40ed6603d5d44fbb24765b10",
		NULL, msg);

	git_signature_free(sig);
}
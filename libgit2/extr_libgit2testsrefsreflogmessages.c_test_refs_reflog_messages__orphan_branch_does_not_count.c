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
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_HEAD_FILE ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_reflog_check_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_repository_set_head (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_repository_set_head_detached (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void test_refs_reflog_messages__orphan_branch_does_not_count(void)
{
	git_oid id;
	const char *msg;

	/* Have something known */
	msg = "checkout: moving from master to e90810b8df3e80c413d903f631643c716887138d";
	git_oid_fromstr(&id, "e90810b8df3e80c413d903f631643c716887138d");
	cl_git_pass(git_repository_set_head_detached(g_repo, &id));
	cl_reflog_check_entry(g_repo, GIT_HEAD_FILE, 0,
		"a65fedf39aefe402d3bb6e24df4d4f5fe4547750",
		"e90810b8df3e80c413d903f631643c716887138d",
		NULL, msg);

	/* Switching to an orphan branch does not write to the reflog */
	cl_git_pass(git_repository_set_head(g_repo, "refs/heads/orphan"));
	cl_reflog_check_entry(g_repo, GIT_HEAD_FILE, 0,
		"a65fedf39aefe402d3bb6e24df4d4f5fe4547750",
		"e90810b8df3e80c413d903f631643c716887138d",
		NULL, msg);

	/* And coming back, we set the source to zero */
	msg = "checkout: moving from orphan to haacked";
	cl_git_pass(git_repository_set_head(g_repo, "refs/heads/haacked"));
	cl_reflog_check_entry(g_repo, GIT_HEAD_FILE, 0,
		"0000000000000000000000000000000000000000",
		"258f0e2a959a364e40ed6603d5d44fbb24765b10",
		NULL, msg);
}
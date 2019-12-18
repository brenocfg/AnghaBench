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
typedef  int /*<<< orphan*/  git_reflog_entry ;
typedef  int /*<<< orphan*/  git_reflog ;
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_REFLOG_DIR ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_rewritefile (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_master_tip ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_join_n (int /*<<< orphan*/ *,char,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  git_futils_readbuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_create (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int,char const*) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * git_reflog_entry_byindex (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reflog_entry_message (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_reflog_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reflog_read (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  git_repository_path (int /*<<< orphan*/ ) ; 
 char* strchr (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/ * strstr (int /*<<< orphan*/ ,char*) ; 

void test_refs_reflog_reflog__reading_a_reflog_with_invalid_format_succeeds(void)
{
	git_reflog *reflog;
	const char *refname = "refs/heads/newline";
	const char *refmessage =
		"Reflog*message with a newline and enough content after it to pass the GIT_REFLOG_SIZE_MIN check inside reflog_parse.";
	const git_reflog_entry *entry;
	git_reference *ref;
	git_oid id;
	git_buf logpath = GIT_BUF_INIT, logcontents = GIT_BUF_INIT;
	char *star;

	/* Create a new branch. */
	cl_git_pass(git_oid_fromstr(&id, current_master_tip));
	cl_git_pass(git_reference_create(&ref, g_repo, refname, &id, 1, refmessage));

	/*
	 * Corrupt the branch reflog by introducing a newline inside the reflog message.
	 * We do this by replacing '*' with '\n'
	 */
	cl_git_pass(git_buf_join_n(&logpath, '/', 3, git_repository_path(g_repo), GIT_REFLOG_DIR, refname));
	cl_git_pass(git_futils_readbuffer(&logcontents, git_buf_cstr(&logpath)));
	cl_assert((star = strchr(git_buf_cstr(&logcontents), '*')) != NULL);
	*star = '\n';
	cl_git_rewritefile(git_buf_cstr(&logpath), git_buf_cstr(&logcontents));

	/*
	 * Confirm that the file was rewritten successfully
	 * and now contains a '\n' in the expected location
	 */
	cl_git_pass(git_futils_readbuffer(&logcontents, git_buf_cstr(&logpath)));
	cl_assert(strstr(git_buf_cstr(&logcontents), "Reflog\nmessage") != NULL);

	cl_git_pass(git_reflog_read(&reflog, g_repo, refname));
	cl_assert(entry = git_reflog_entry_byindex(reflog, 0));
	cl_assert_equal_s(git_reflog_entry_message(entry), "Reflog");

	git_reference_free(ref);
	git_reflog_free(reflog);
	git_buf_dispose(&logpath);
	git_buf_dispose(&logcontents);
}
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
typedef  int /*<<< orphan*/  git_commit ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert_equal_s (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_commit__free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_message (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_message_raw (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_commit (int /*<<< orphan*/ **,char const*) ; 

void test_commit_parse__only_lf(void)
{
	git_commit *commit;
	const char *buffer =
"tree 1810dff58d8a660512d4832e740f692884338ccd\n\
parent e90810b8df3e80c413d903f631643c716887138d\n\
author Vicent Marti <tanoku@gmail.com> 1273848544 +0200\n\
committer Vicent Marti <tanoku@gmail.com> 1273848544 +0200\n\
\n\
\n\
\n";
	const char *message = "";
	const char *raw_message = "\n\n";

	cl_git_pass(parse_commit(&commit, buffer));
	cl_assert_equal_s(message, git_commit_message(commit));
	cl_assert_equal_s(raw_message, git_commit_message_raw(commit));
	git_commit__free(commit);
}
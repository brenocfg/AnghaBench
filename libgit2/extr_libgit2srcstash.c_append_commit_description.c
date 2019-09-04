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
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (char const*) ; 
 scalar_t__ append_abbreviated_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ git_buf_oom (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_putc (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  git_buf_puts (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  git_commit_id (int /*<<< orphan*/ *) ; 
 char* git_commit_summary (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int append_commit_description(git_buf *out, git_commit* commit)
{
	const char *summary = git_commit_summary(commit);
	GIT_ERROR_CHECK_ALLOC(summary);

	if (append_abbreviated_oid(out, git_commit_id(commit)) < 0)
		return -1;

	git_buf_putc(out, ' ');
	git_buf_puts(out, summary);
	git_buf_putc(out, '\n');

	return git_buf_oom(out) ? -1 : 0;
}
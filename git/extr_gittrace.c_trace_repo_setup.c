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

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 char const* get_git_common_dir () ; 
 char const* get_git_dir () ; 
 char* get_git_work_tree () ; 
 int /*<<< orphan*/  quote_crnl (char const*) ; 
 int /*<<< orphan*/  trace_printf_key (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_setup_key ; 
 int /*<<< orphan*/  trace_want (int /*<<< orphan*/ *) ; 
 char* xgetcwd () ; 

void trace_repo_setup(const char *prefix)
{
	const char *git_work_tree;
	char *cwd;

	if (!trace_want(&trace_setup_key))
		return;

	cwd = xgetcwd();

	if (!(git_work_tree = get_git_work_tree()))
		git_work_tree = "(null)";

	if (!prefix)
		prefix = "(null)";

	trace_printf_key(&trace_setup_key, "setup: git_dir: %s\n", quote_crnl(get_git_dir()));
	trace_printf_key(&trace_setup_key, "setup: git_common_dir: %s\n", quote_crnl(get_git_common_dir()));
	trace_printf_key(&trace_setup_key, "setup: worktree: %s\n", quote_crnl(git_work_tree));
	trace_printf_key(&trace_setup_key, "setup: cwd: %s\n", quote_crnl(cwd));
	trace_printf_key(&trace_setup_key, "setup: prefix: %s\n", quote_crnl(prefix));

	free(cwd);
}
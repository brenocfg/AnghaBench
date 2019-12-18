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
struct strbuf {int dummy; } ;
struct child_process {int git_cmd; int no_stdin; int out; char const* dir; int /*<<< orphan*/  env_array; int /*<<< orphan*/  args; } ;
typedef  int ssize_t ;

/* Variables and functions */
 struct child_process CHILD_PROCESS_INIT ; 
 struct strbuf STRBUF_INIT ; 
 unsigned int SUBMODULE_REMOVAL_DIE_ON_ERROR ; 
 unsigned int SUBMODULE_REMOVAL_IGNORE_IGNORED_UNTRACKED ; 
 unsigned int SUBMODULE_REMOVAL_IGNORE_UNTRACKED ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  argv_array_push (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  argv_array_pushl (int /*<<< orphan*/ *,char*,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  file_exists (char const*) ; 
 scalar_t__ finish_command (struct child_process*) ; 
 scalar_t__ is_empty_dir (char const*) ; 
 int /*<<< orphan*/  prepare_submodule_repo_env (int /*<<< orphan*/ *) ; 
 scalar_t__ start_command (struct child_process*) ; 
 int strbuf_read (struct strbuf*,int,int) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  submodule_uses_gitfile (char const*) ; 

int bad_to_remove_submodule(const char *path, unsigned flags)
{
	ssize_t len;
	struct child_process cp = CHILD_PROCESS_INIT;
	struct strbuf buf = STRBUF_INIT;
	int ret = 0;

	if (!file_exists(path) || is_empty_dir(path))
		return 0;

	if (!submodule_uses_gitfile(path))
		return 1;

	argv_array_pushl(&cp.args, "status", "--porcelain",
				   "--ignore-submodules=none", NULL);

	if (flags & SUBMODULE_REMOVAL_IGNORE_UNTRACKED)
		argv_array_push(&cp.args, "-uno");
	else
		argv_array_push(&cp.args, "-uall");

	if (!(flags & SUBMODULE_REMOVAL_IGNORE_IGNORED_UNTRACKED))
		argv_array_push(&cp.args, "--ignored");

	prepare_submodule_repo_env(&cp.env_array);
	cp.git_cmd = 1;
	cp.no_stdin = 1;
	cp.out = -1;
	cp.dir = path;
	if (start_command(&cp)) {
		if (flags & SUBMODULE_REMOVAL_DIE_ON_ERROR)
			die(_("could not start 'git status' in submodule '%s'"),
				path);
		ret = -1;
		goto out;
	}

	len = strbuf_read(&buf, cp.out, 1024);
	if (len > 2)
		ret = 1;
	close(cp.out);

	if (finish_command(&cp)) {
		if (flags & SUBMODULE_REMOVAL_DIE_ON_ERROR)
			die(_("could not run 'git status' in submodule '%s'"),
				path);
		ret = -1;
	}
out:
	strbuf_release(&buf);
	return ret;
}
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
struct worktree {int /*<<< orphan*/  path; } ;
struct child_process {int git_cmd; int out; int /*<<< orphan*/  dir; int /*<<< orphan*/  env; int /*<<< orphan*/  args; } ;
struct argv_array {int /*<<< orphan*/  argv; } ;
typedef  int /*<<< orphan*/  cp ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 struct argv_array ARGV_ARRAY_INIT ; 
 int /*<<< orphan*/  GIT_DIR_ENVIRONMENT ; 
 int /*<<< orphan*/  GIT_WORK_TREE_ENVIRONMENT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  argv_array_pushf (struct argv_array*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  argv_array_pushl (int /*<<< orphan*/ *,char*,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  die_errno (int /*<<< orphan*/ ,char const*,...) ; 
 int finish_command (struct child_process*) ; 
 int /*<<< orphan*/  memset (struct child_process*,int /*<<< orphan*/ ,int) ; 
 int start_command (struct child_process*) ; 
 int /*<<< orphan*/  validate_no_submodules (struct worktree*) ; 
 int xread (int,char*,int) ; 

__attribute__((used)) static void check_clean_worktree(struct worktree *wt,
				 const char *original_path)
{
	struct argv_array child_env = ARGV_ARRAY_INIT;
	struct child_process cp;
	char buf[1];
	int ret;

	/*
	 * Until we sort this out, all submodules are "dirty" and
	 * will abort this function.
	 */
	validate_no_submodules(wt);

	argv_array_pushf(&child_env, "%s=%s/.git",
			 GIT_DIR_ENVIRONMENT, wt->path);
	argv_array_pushf(&child_env, "%s=%s",
			 GIT_WORK_TREE_ENVIRONMENT, wt->path);
	memset(&cp, 0, sizeof(cp));
	argv_array_pushl(&cp.args, "status",
			 "--porcelain", "--ignore-submodules=none",
			 NULL);
	cp.env = child_env.argv;
	cp.git_cmd = 1;
	cp.dir = wt->path;
	cp.out = -1;
	ret = start_command(&cp);
	if (ret)
		die_errno(_("failed to run 'git status' on '%s'"),
			  original_path);
	ret = xread(cp.out, buf, sizeof(buf));
	if (ret)
		die(_("'%s' contains modified or untracked files, use --force to delete it"),
		    original_path);
	close(cp.out);
	ret = finish_command(&cp);
	if (ret)
		die_errno(_("failed to run 'git status' on '%s', code %d"),
			  original_path, ret);
}
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
struct submodule {int /*<<< orphan*/  path; } ;
struct child_process {int git_cmd; int no_stdin; int no_stdout; int /*<<< orphan*/  dir; int /*<<< orphan*/  args; int /*<<< orphan*/  env_array; } ;

/* Variables and functions */
 struct child_process CHILD_PROCESS_INIT ; 
 int /*<<< orphan*/  argv_array_pushl (int /*<<< orphan*/ *,char*,char*,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  die (char*,int /*<<< orphan*/ ) ; 
 int finish_command (struct child_process*) ; 
 int /*<<< orphan*/  prepare_submodule_repo_env (int /*<<< orphan*/ *) ; 
 scalar_t__ start_command (struct child_process*) ; 

__attribute__((used)) static int submodule_has_dirty_index(const struct submodule *sub)
{
	struct child_process cp = CHILD_PROCESS_INIT;

	prepare_submodule_repo_env(&cp.env_array);

	cp.git_cmd = 1;
	argv_array_pushl(&cp.args, "diff-index", "--quiet",
				   "--cached", "HEAD", NULL);
	cp.no_stdin = 1;
	cp.no_stdout = 1;
	cp.dir = sub->path;
	if (start_command(&cp))
		die("could not recurse into submodule '%s'", sub->path);

	return finish_command(&cp);
}
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
struct remote {char const* name; } ;
struct refspec {int raw_nr; char const** raw; } ;
struct child_process {int git_cmd; int no_stdin; int no_stdout; char const* dir; int /*<<< orphan*/  env_array; int /*<<< orphan*/  args; } ;

/* Variables and functions */
 struct child_process CHILD_PROCESS_INIT ; 
 int /*<<< orphan*/  argv_array_push (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  die (char*,char const*) ; 
 int /*<<< orphan*/  prepare_submodule_repo_env (int /*<<< orphan*/ *) ; 
 scalar_t__ run_command (struct child_process*) ; 

__attribute__((used)) static void submodule_push_check(const char *path, const char *head,
				 const struct remote *remote,
				 const struct refspec *rs)
{
	struct child_process cp = CHILD_PROCESS_INIT;
	int i;

	argv_array_push(&cp.args, "submodule--helper");
	argv_array_push(&cp.args, "push-check");
	argv_array_push(&cp.args, head);
	argv_array_push(&cp.args, remote->name);

	for (i = 0; i < rs->raw_nr; i++)
		argv_array_push(&cp.args, rs->raw[i]);

	prepare_submodule_repo_env(&cp.env_array);
	cp.git_cmd = 1;
	cp.no_stdin = 1;
	cp.no_stdout = 1;
	cp.dir = path;

	/*
	 * Simply indicate if 'submodule--helper push-check' failed.
	 * More detailed error information will be provided by the
	 * child process.
	 */
	if (run_command(&cp))
		die("process for submodule '%s' failed", path);
}
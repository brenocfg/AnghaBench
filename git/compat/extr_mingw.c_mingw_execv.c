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
 int /*<<< orphan*/  exit (int) ; 
 int mingw_spawnv (char const*,char const**,int /*<<< orphan*/ ) ; 
 int trace2_exec (char const*,char const**) ; 
 int /*<<< orphan*/  trace2_exec_result (int,int) ; 
 int /*<<< orphan*/  try_shell_exec (char const*,char* const*) ; 
 scalar_t__ waitpid (int,int*,int /*<<< orphan*/ ) ; 

int mingw_execv(const char *cmd, char *const *argv)
{
	/* check if git_command is a shell script */
	if (!try_shell_exec(cmd, argv)) {
		int pid, status;
		int exec_id;

		exec_id = trace2_exec(cmd, (const char **)argv);
		pid = mingw_spawnv(cmd, (const char **)argv, 0);
		if (pid < 0) {
			trace2_exec_result(exec_id, -1);
			return -1;
		}
		if (waitpid(pid, &status, 0) < 0)
			status = 255;
		trace2_exec_result(exec_id, status);
		exit(status);
	}
	return -1;
}
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
struct child_process {int /*<<< orphan*/ * argv; scalar_t__ use_shell; scalar_t__ git_cmd; } ;
struct argv_array {char** argv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 int /*<<< orphan*/  ENOENT ; 
 char* SHELL_PATH ; 
 int /*<<< orphan*/  argv_array_clear (struct argv_array*) ; 
 int /*<<< orphan*/  argv_array_push (struct argv_array*,char*) ; 
 int /*<<< orphan*/  argv_array_pushv (struct argv_array*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (char*) ; 
 char* locate_in_PATH (char*) ; 
 int /*<<< orphan*/  prepare_shell_cmd (struct argv_array*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strchr (char*,char) ; 

__attribute__((used)) static int prepare_cmd(struct argv_array *out, const struct child_process *cmd)
{
	if (!cmd->argv[0])
		BUG("command is empty");

	/*
	 * Add SHELL_PATH so in the event exec fails with ENOEXEC we can
	 * attempt to interpret the command with 'sh'.
	 */
	argv_array_push(out, SHELL_PATH);

	if (cmd->git_cmd) {
		argv_array_push(out, "git");
		argv_array_pushv(out, cmd->argv);
	} else if (cmd->use_shell) {
		prepare_shell_cmd(out, cmd->argv);
	} else {
		argv_array_pushv(out, cmd->argv);
	}

	/*
	 * If there are no '/' characters in the command then perform a path
	 * lookup and use the resolved path as the command to exec.  If there
	 * are '/' characters, we have exec attempt to invoke the command
	 * directly.
	 */
	if (!strchr(out->argv[1], '/')) {
		char *program = locate_in_PATH(out->argv[1]);
		if (program) {
			free((char *)out->argv[1]);
			out->argv[1] = program;
		} else {
			argv_array_clear(out);
			errno = ENOENT;
			return -1;
		}
	}

	return 0;
}
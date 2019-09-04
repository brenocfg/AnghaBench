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
struct child_process {char const** argv; int no_stdin; int git_cmd; int stdout_to_stderr; int silent_exec_failure; int use_shell; int clean_on_exit; char const* dir; char const* const* env; char const* trace2_child_class; } ;

/* Variables and functions */
 struct child_process CHILD_PROCESS_INIT ; 
 int RUN_CLEAN_ON_EXIT ; 
 int RUN_COMMAND_NO_STDIN ; 
 int RUN_COMMAND_STDOUT_TO_STDERR ; 
 int RUN_GIT_CMD ; 
 int RUN_SILENT_EXEC_FAILURE ; 
 int RUN_USING_SHELL ; 
 int run_command (struct child_process*) ; 

int run_command_v_opt_cd_env_tr2(const char **argv, int opt, const char *dir,
				 const char *const *env, const char *tr2_class)
{
	struct child_process cmd = CHILD_PROCESS_INIT;
	cmd.argv = argv;
	cmd.no_stdin = opt & RUN_COMMAND_NO_STDIN ? 1 : 0;
	cmd.git_cmd = opt & RUN_GIT_CMD ? 1 : 0;
	cmd.stdout_to_stderr = opt & RUN_COMMAND_STDOUT_TO_STDERR ? 1 : 0;
	cmd.silent_exec_failure = opt & RUN_SILENT_EXEC_FAILURE ? 1 : 0;
	cmd.use_shell = opt & RUN_USING_SHELL ? 1 : 0;
	cmd.clean_on_exit = opt & RUN_CLEAN_ON_EXIT ? 1 : 0;
	cmd.dir = dir;
	cmd.env = env;
	cmd.trace2_child_class = tr2_class;
	return run_command(&cmd);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  argv; } ;
struct child_process {int clean_on_exit; int wait_after_clean; int silent_exec_failure; char* trace2_child_class; TYPE_1__ args; } ;

/* Variables and functions */
 struct child_process CHILD_PROCESS_INIT ; 
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  argv_array_pushf (TYPE_1__*,char*,char const*) ; 
 int /*<<< orphan*/  argv_array_pushv (TYPE_1__*,char const**) ; 
 int check_pager_config (char const*) ; 
 int /*<<< orphan*/  commit_pager_choice () ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ get_super_prefix () ; 
 int /*<<< orphan*/  is_builtin (char const*) ; 
 int run_command (struct child_process*) ; 
 int /*<<< orphan*/  trace2_cmd_name (char*) ; 
 int /*<<< orphan*/  trace_argv_printf (int /*<<< orphan*/ ,char*) ; 
 int use_pager ; 

__attribute__((used)) static void execv_dashed_external(const char **argv)
{
	struct child_process cmd = CHILD_PROCESS_INIT;
	int status;

	if (get_super_prefix())
		die(_("%s doesn't support --super-prefix"), argv[0]);

	if (use_pager == -1 && !is_builtin(argv[0]))
		use_pager = check_pager_config(argv[0]);
	commit_pager_choice();

	argv_array_pushf(&cmd.args, "git-%s", argv[0]);
	argv_array_pushv(&cmd.args, argv + 1);
	cmd.clean_on_exit = 1;
	cmd.wait_after_clean = 1;
	cmd.silent_exec_failure = 1;
	cmd.trace2_child_class = "dashed";

	trace2_cmd_name("_run_dashed_");

	/*
	 * The code in run_command() logs trace2 child_start/child_exit
	 * events, so we do not need to report exec/exec_result events here.
	 */
	trace_argv_printf(cmd.args.argv, "trace: exec:");

	/*
	 * If we fail because the command is not found, it is
	 * OK to return. Otherwise, we just pass along the status code,
	 * or our usual generic code if we were not even able to exec
	 * the program.
	 */
	status = run_command(&cmd);

	/*
	 * If the child process ran and we are now going to exit, emit a
	 * generic string as our trace2 command verb to indicate that we
	 * launched a dashed command.
	 */
	if (status >= 0)
		exit(status);
	else if (errno != ENOENT)
		exit(128);
}
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
typedef  scalar_t__ DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CW_CYGWIN_PID_TO_WINPID ; 
 scalar_t__ DebugActiveProcess (scalar_t__) ; 
 int /*<<< orphan*/  DebugSetProcessKillOnExit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SE_DEBUG_NAME ; 
 int /*<<< orphan*/  TRUE ; 
 int attach_flag ; 
 scalar_t__ cygwin_internal (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  do_initial_child_stuff (scalar_t__) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  error_no_arg (char*) ; 
 int /*<<< orphan*/  gdb_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stdout ; 
 scalar_t__ get_exec_file (int /*<<< orphan*/ ) ; 
 scalar_t__ has_detach_ability () ; 
 int /*<<< orphan*/  pid_to_ptid (scalar_t__) ; 
 int /*<<< orphan*/  printf_unfiltered (char*,...) ; 
 scalar_t__ saw_create ; 
 scalar_t__ set_process_privilege (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strtoul (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  target_pid_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  target_terminal_ours () ; 

__attribute__((used)) static void
child_attach (char *args, int from_tty)
{
  BOOL ok;
  DWORD pid;

  if (!args)
    error_no_arg ("process-id to attach");

  if (set_process_privilege (SE_DEBUG_NAME, TRUE) < 0)
    {
      printf_unfiltered ("Warning: Failed to get SE_DEBUG_NAME privilege\n");
      printf_unfiltered ("This can cause attach to fail on Windows NT/2K/XP\n");
    }

  pid = strtoul (args, 0, 0);		/* Windows pid */

  ok = DebugActiveProcess (pid);
  saw_create = 0;

  if (!ok)
    {
      /* Try fall back to Cygwin pid */
      pid = cygwin_internal (CW_CYGWIN_PID_TO_WINPID, pid);

      if (pid > 0)
	ok = DebugActiveProcess (pid);

      if (!ok)
	error ("Can't attach to process.");
    }

  if (has_detach_ability ())
    DebugSetProcessKillOnExit (FALSE);

  attach_flag = 1;

  if (from_tty)
    {
      char *exec_file = (char *) get_exec_file (0);

      if (exec_file)
	printf_unfiltered ("Attaching to program `%s', %s\n", exec_file,
			   target_pid_to_str (pid_to_ptid (pid)));
      else
	printf_unfiltered ("Attaching to %s\n",
			   target_pid_to_str (pid_to_ptid (pid)));

      gdb_flush (gdb_stdout);
    }

  do_initial_child_stuff (pid);
  target_terminal_ours ();
}
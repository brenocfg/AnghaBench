#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  dwProcessId; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_CONTINUE ; 
 int /*<<< orphan*/  DebugActiveProcessStop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DebugSetProcessKillOnExit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 char* GetLastError () ; 
 int /*<<< orphan*/  child_continue (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  child_ops ; 
 TYPE_1__ current_event ; 
 int /*<<< orphan*/  delete_command (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gdb_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stdout ; 
 char* get_exec_file (int /*<<< orphan*/ ) ; 
 scalar_t__ has_detach_ability () ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  null_ptid ; 
 int /*<<< orphan*/  printf_unfiltered (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unpush_target (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
child_detach (char *args, int from_tty)
{
  int detached = 1;

  if (has_detach_ability ())
    {
      delete_command (NULL, 0);
      child_continue (DBG_CONTINUE, -1);
      if (!DebugActiveProcessStop (current_event.dwProcessId))
	{
	  error ("Can't detach process %lu (error %lu)",
		 current_event.dwProcessId, GetLastError ());
	  detached = 0;
	}
      DebugSetProcessKillOnExit (FALSE);
    }
  if (detached && from_tty)
    {
      char *exec_file = get_exec_file (0);
      if (exec_file == 0)
	exec_file = "";
      printf_unfiltered ("Detaching from program: %s, Pid %lu\n", exec_file,
			 current_event.dwProcessId);
      gdb_flush (gdb_stdout);
    }
  inferior_ptid = null_ptid;
  unpush_target (&child_ops);
}
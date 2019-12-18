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
struct interp_procs {int dummy; } ;
struct interp {int dummy; } ;
typedef  enum mi_cmd_result { ____Placeholder_mi_cmd_result } mi_cmd_result ;

/* Variables and functions */
 int /*<<< orphan*/  ALL_CLEANUPS ; 
 int MI_CMD_DONE ; 
 int MI_CMD_ERROR ; 
 int /*<<< orphan*/  add_continuation (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_exec_error_cleanups (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs_unfiltered (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ interp_exec (struct interp*,char*) ; 
 int /*<<< orphan*/  interp_exec_p (struct interp*) ; 
 struct interp* interp_lookup (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  mi_error_last_message () ; 
 int /*<<< orphan*/  mi_error_message ; 
 int /*<<< orphan*/  mi_insert_notify_hooks () ; 
 int /*<<< orphan*/  mi_interpreter_exec_continuation ; 
 int /*<<< orphan*/  mi_remove_notify_hooks () ; 
 int /*<<< orphan*/  raw_stdout ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strlen (char*) ; 
 int sync_execution ; 
 scalar_t__ target_can_async_p () ; 
 scalar_t__ target_executing ; 
 int /*<<< orphan*/  xasprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  xfree (char*) ; 
 char* xmalloc (int) ; 

enum mi_cmd_result
mi_cmd_interpreter_exec (char *command, char **argv, int argc)
{
  struct interp *interp_to_use;
  enum mi_cmd_result result = MI_CMD_DONE;
  int i;
  struct interp_procs *procs;

  if (argc < 2)
    {
      xasprintf (&mi_error_message,
		 "mi_cmd_interpreter_exec: Usage: -interpreter-exec interp command");
      return MI_CMD_ERROR;
    }

  interp_to_use = interp_lookup (argv[0]);
  if (interp_to_use == NULL)
    {
      xasprintf (&mi_error_message,
		 "mi_cmd_interpreter_exec: could not find interpreter \"%s\"",
		 argv[0]);
      return MI_CMD_ERROR;
    }

  if (!interp_exec_p (interp_to_use))
    {
      xasprintf (&mi_error_message,
		 "mi_cmd_interpreter_exec: interpreter \"%s\" does not support command execution",
		 argv[0]);
      return MI_CMD_ERROR;
    }

  /* Insert the MI out hooks, making sure to also call the interpreter's hooks
     if it has any. */
  /* KRS: We shouldn't need this... Events should be installed and they should
     just ALWAYS fire something out down the MI channel... */
  mi_insert_notify_hooks ();

  /* Now run the code... */

  for (i = 1; i < argc; i++)
    {
      char *buff = NULL;
      /* Do this in a cleaner way...  We want to force execution to be
         asynchronous for commands that run the target.  */
      if (target_can_async_p () && (strcmp (argv[0], "console") == 0))
	{
	  int len = strlen (argv[i]);
	  buff = xmalloc (len + 2);
	  memcpy (buff, argv[i], len);
	  buff[len] = '&';
	  buff[len + 1] = '\0';
	}

      /* We had to set sync_execution = 0 for the mi (well really for Project
         Builder's use of the mi - particularly so interrupting would work.
         But for console commands to work, we need to initialize it to 1 -
         since that is what the cli expects - before running the command,
         and then set it back to 0 when we are done. */
      sync_execution = 1;
      if (interp_exec (interp_to_use, argv[i]) < 0)
	{
	  mi_error_last_message ();
	  result = MI_CMD_ERROR;
	  break;
	}
      xfree (buff);
      do_exec_error_cleanups (ALL_CLEANUPS);
      sync_execution = 0;
    }

  mi_remove_notify_hooks ();

  /* Okay, now let's see if the command set the inferior going...
     Tricky point - have to do this AFTER resetting the interpreter, since
     changing the interpreter will clear out all the continuations for
     that interpreter... */

  if (target_can_async_p () && target_executing)
    {
      fputs_unfiltered ("^running\n", raw_stdout);
      add_continuation (mi_interpreter_exec_continuation, NULL);
    }

  return result;
}
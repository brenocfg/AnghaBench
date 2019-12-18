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
struct cleanup {int dummy; } ;
typedef  enum mi_cmd_result { ____Placeholder_mi_cmd_result } mi_cmd_result ;

/* Variables and functions */
 int MI_CMD_DONE ; 
 int MI_CMD_QUIET ; 
 int /*<<< orphan*/  add_continuation (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  execute_command (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs_unfiltered (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free ; 
 int /*<<< orphan*/  gdb_flush (int /*<<< orphan*/ ) ; 
 char* last_async_command ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  make_exec_cleanup (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mi_exec_async_cli_cmd_continuation ; 
 int /*<<< orphan*/  mi_out_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mi_out_rewind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_stdout ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 scalar_t__ target_can_async_p () ; 
 int /*<<< orphan*/  uiout ; 
 int /*<<< orphan*/  xasprintf (char**,char*,char*,char*) ; 
 int /*<<< orphan*/  xfree ; 
 scalar_t__ xmalloc (scalar_t__) ; 

enum mi_cmd_result
mi_execute_async_cli_command (char *mi, char *args, int from_tty)
{
  struct cleanup *old_cleanups;
  char *run;
  char *async_args;

  if (target_can_async_p ())
    {
      async_args = (char *) xmalloc (strlen (args) + 2);
      make_exec_cleanup (free, async_args);
      strcpy (async_args, args);
      strcat (async_args, "&");
      xasprintf (&run, "%s %s", mi, async_args);
      make_exec_cleanup (free, run);
      add_continuation (mi_exec_async_cli_cmd_continuation, NULL);
      old_cleanups = NULL;
    }
  else
    {
      xasprintf (&run, "%s %s", mi, args);
      old_cleanups = make_cleanup (xfree, run);
    }

  if (!target_can_async_p ())
    {
      /* NOTE: For synchronous targets asynchronous behavour is faked by
         printing out the GDB prompt before we even try to execute the
         command. */
      if (last_async_command)
	fputs_unfiltered (last_async_command, raw_stdout);
      fputs_unfiltered ("^running\n", raw_stdout);
      fputs_unfiltered ("(gdb) \n", raw_stdout);
      gdb_flush (raw_stdout);
    }
  else
    {
      /* FIXME: cagney/1999-11-29: Printing this message before
         calling execute_command is wrong.  It should only be printed
         once gdb has confirmed that it really has managed to send a
         run command to the target. */
      if (last_async_command)
	fputs_unfiltered (last_async_command, raw_stdout);
      fputs_unfiltered ("^running\n", raw_stdout);
    }

  execute_command ( /*ui */ run, 0 /*from_tty */ );

  if (!target_can_async_p ())
    {
      /* Do this before doing any printing.  It would appear that some
         print code leaves garbage around in the buffer. */
      do_cleanups (old_cleanups);
      /* If the target was doing the operation synchronously we fake
         the stopped message. */
      if (last_async_command)
	fputs_unfiltered (last_async_command, raw_stdout);
      fputs_unfiltered ("*stopped", raw_stdout);
      mi_out_put (uiout, raw_stdout);
      mi_out_rewind (uiout);
      fputs_unfiltered ("\n", raw_stdout);
      return MI_CMD_QUIET;
    }
  return MI_CMD_DONE;
}
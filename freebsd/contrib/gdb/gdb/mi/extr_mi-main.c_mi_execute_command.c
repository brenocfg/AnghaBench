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
struct ui_out {int dummy; } ;
struct mi_parse {char* token; } ;
struct cleanup {int dummy; } ;
struct captured_mi_execute_command_args {scalar_t__ action; struct mi_parse* command; } ;

/* Variables and functions */
 scalar_t__ EXECUTE_COMMAND_DISPLAY_ERROR ; 
 scalar_t__ EXECUTE_COMMAND_SUPRESS_PROMPT ; 
 int /*<<< orphan*/  RETURN_MASK_ALL ; 
 int /*<<< orphan*/  captured_mi_execute_command ; 
 int catch_exceptions (struct ui_out*,int /*<<< orphan*/ ,struct captured_mi_execute_command_args*,char*,int /*<<< orphan*/ ) ; 
 char* error_last_message () ; 
 int /*<<< orphan*/  fputs_unfiltered (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputstr_unfiltered (char*,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_flush (int /*<<< orphan*/ ) ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,char*) ; 
 struct mi_parse* mi_parse (char*) ; 
 int /*<<< orphan*/  mi_parse_free (struct mi_parse*) ; 
 int /*<<< orphan*/  quit_force (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  raw_stdout ; 
 struct ui_out* uiout ; 
 int /*<<< orphan*/  xfree ; 

void
mi_execute_command (char *cmd, int from_tty)
{
  struct mi_parse *command;
  struct captured_mi_execute_command_args args;
  struct ui_out *saved_uiout = uiout;
  int result;

  /* This is to handle EOF (^D). We just quit gdb. */
  /* FIXME: we should call some API function here. */
  if (cmd == 0)
    quit_force (NULL, from_tty);

  command = mi_parse (cmd);

  if (command != NULL)
    {
      /* FIXME: cagney/1999-11-04: Can this use of catch_exceptions either
         be pushed even further down or even eliminated? */
      args.command = command;
      result = catch_exceptions (uiout, captured_mi_execute_command, &args, "",
				 RETURN_MASK_ALL);

      if (args.action == EXECUTE_COMMAND_SUPRESS_PROMPT)
	{
	  /* The command is executing synchronously.  Bail out early
	     suppressing the finished prompt. */
	  mi_parse_free (command);
	  return;
	}
      if (args.action == EXECUTE_COMMAND_DISPLAY_ERROR || result < 0)
	{
	  char *msg = error_last_message ();
	  struct cleanup *cleanup = make_cleanup (xfree, msg);
	  /* The command execution failed and error() was called
	     somewhere */
	  fputs_unfiltered (command->token, raw_stdout);
	  fputs_unfiltered ("^error,msg=\"", raw_stdout);
	  fputstr_unfiltered (msg, '"', raw_stdout);
	  fputs_unfiltered ("\"\n", raw_stdout);
	}
      mi_parse_free (command);
    }

  fputs_unfiltered ("(gdb) \n", raw_stdout);
  gdb_flush (raw_stdout);
  /* print any buffered hook code */
  /* ..... */
}
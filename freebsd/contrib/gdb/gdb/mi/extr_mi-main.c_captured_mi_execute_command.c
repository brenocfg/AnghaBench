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
struct mi_parse {int op; char* token; int /*<<< orphan*/  command; int /*<<< orphan*/  args; } ;
struct captured_mi_execute_command_args {int /*<<< orphan*/  rc; void* action; struct mi_parse* command; } ;

/* Variables and functions */
#define  CLI_COMMAND 129 
 void* EXECUTE_COMMAND_DISPLAY_ERROR ; 
 void* EXECUTE_COMMAND_DISPLAY_PROMPT ; 
 void* EXECUTE_COMMAND_SUPRESS_PROMPT ; 
 int /*<<< orphan*/  INTERP_MI ; 
 int /*<<< orphan*/  INTERP_MI1 ; 
 int /*<<< orphan*/  INTERP_MI2 ; 
 int /*<<< orphan*/  INTERP_MI3 ; 
 int /*<<< orphan*/  MI_CMD_CAUGHT_ERROR ; 
 int /*<<< orphan*/  MI_CMD_DONE ; 
 int /*<<< orphan*/  MI_CMD_ERROR ; 
#define  MI_COMMAND 128 
 int /*<<< orphan*/  current_interp_named_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  fputs_unfiltered (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputstr_unfiltered (int /*<<< orphan*/ ,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stdlog ; 
 int /*<<< orphan*/  mi_cmd_execute (struct mi_parse*) ; 
 int /*<<< orphan*/  mi_debug_p ; 
 int /*<<< orphan*/  mi_error_message ; 
 int /*<<< orphan*/  mi_execute_cli_command (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mi_out_put (struct ui_out*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mi_out_rewind (struct ui_out*) ; 
 int /*<<< orphan*/  raw_stdout ; 
 int /*<<< orphan*/  sync_execution ; 
 int /*<<< orphan*/  target_can_async_p () ; 
 int /*<<< orphan*/  target_executing ; 
 int /*<<< orphan*/  xfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
captured_mi_execute_command (struct ui_out *uiout, void *data)
{
  struct captured_mi_execute_command_args *args =
    (struct captured_mi_execute_command_args *) data;
  struct mi_parse *context = args->command;

  switch (context->op)
    {

    case MI_COMMAND:
      /* A MI command was read from the input stream */
      if (mi_debug_p)
	/* FIXME: gdb_???? */
	fprintf_unfiltered (raw_stdout, " token=`%s' command=`%s' args=`%s'\n",
			    context->token, context->command, context->args);
      /* FIXME: cagney/1999-09-25: Rather than this convoluted
         condition expression, each function should return an
         indication of what action is required and then switch on
         that. */
      args->action = EXECUTE_COMMAND_DISPLAY_PROMPT;
      args->rc = mi_cmd_execute (context);

      if (!target_can_async_p () || !target_executing)
	{
	  /* print the result if there were no errors

	     Remember that on the way out of executing a command, you have
	     to directly use the mi_interp's uiout, since the command could 
	     have reset the interpreter, in which case the current uiout 
	     will most likely crash in the mi_out_* routines.  */
	  if (args->rc == MI_CMD_DONE)
	    {
	      fputs_unfiltered (context->token, raw_stdout);
	      fputs_unfiltered ("^done", raw_stdout);
	      mi_out_put (uiout, raw_stdout);
	      mi_out_rewind (uiout);
	      fputs_unfiltered ("\n", raw_stdout);
	    }
	  else if (args->rc == MI_CMD_ERROR)
	    {
	      if (mi_error_message)
		{
		  fputs_unfiltered (context->token, raw_stdout);
		  fputs_unfiltered ("^error,msg=\"", raw_stdout);
		  fputstr_unfiltered (mi_error_message, '"', raw_stdout);
		  xfree (mi_error_message);
		  fputs_unfiltered ("\"\n", raw_stdout);
		}
	      mi_out_rewind (uiout);
	    }
	  else if (args->rc == MI_CMD_CAUGHT_ERROR)
	    {
	      mi_out_rewind (uiout);
	      args->action = EXECUTE_COMMAND_DISPLAY_ERROR;
	      return 1;
	    }
	  else
	    mi_out_rewind (uiout);
	}
      else if (sync_execution)
	{
	  /* Don't print the prompt. We are executing the target in
	     synchronous mode. */
	  args->action = EXECUTE_COMMAND_SUPRESS_PROMPT;
	  return 1;
	}
      break;

    case CLI_COMMAND:
      /* A CLI command was read from the input stream */
      /* This will be removed as soon as we have a complete set of
         mi commands */
      /* echo the command on the console. */
      fprintf_unfiltered (gdb_stdlog, "%s\n", context->command);
      mi_execute_cli_command (context->command, 0, NULL);

      /* If we changed interpreters, DON'T print out anything. */
      if (current_interp_named_p (INTERP_MI)
	  || current_interp_named_p (INTERP_MI1)
	  || current_interp_named_p (INTERP_MI2)
	  || current_interp_named_p (INTERP_MI3))
	{
	  /* print the result */
	  /* FIXME: Check for errors here. */
	  fputs_unfiltered (context->token, raw_stdout);
	  fputs_unfiltered ("^done", raw_stdout);
	  mi_out_put (uiout, raw_stdout);
	  mi_out_rewind (uiout);
	  fputs_unfiltered ("\n", raw_stdout);
	  args->action = EXECUTE_COMMAND_DISPLAY_PROMPT;
	  args->rc = MI_CMD_DONE;
	}
      break;

    }

  return 1;
}
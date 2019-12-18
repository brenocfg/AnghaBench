#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mi_parse {char* token; int /*<<< orphan*/  command; int /*<<< orphan*/  args; TYPE_2__* cmd; int /*<<< orphan*/  argc; int /*<<< orphan*/  argv; } ;
typedef  enum mi_cmd_result { ____Placeholder_mi_cmd_result } mi_cmd_result ;
struct TYPE_3__ {scalar_t__ cmd; int /*<<< orphan*/  args_p; } ;
struct TYPE_4__ {int (* argv_func ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int (* args_func ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;TYPE_1__ cli; } ;

/* Variables and functions */
 int MI_CMD_DONE ; 
 int MI_CMD_ERROR ; 
 int /*<<< orphan*/  fputs_unfiltered (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputstr_unfiltered (int /*<<< orphan*/ ,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_current_contents ; 
 char* last_async_command ; 
 int /*<<< orphan*/  make_exec_cleanup (int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  mi_execute_cli_command (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* previous_async_command ; 
 int /*<<< orphan*/  raw_stdout ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ target_executing ; 
 void* xstrdup (char*) ; 

__attribute__((used)) static enum mi_cmd_result
mi_cmd_execute (struct mi_parse *parse)
{
  if (parse->cmd->argv_func != NULL
      || parse->cmd->args_func != NULL)
    {
      /* FIXME: We need to save the token because the command executed
         may be asynchronous and need to print the token again.
         In the future we can pass the token down to the func
         and get rid of the last_async_command */
      /* The problem here is to keep the token around when we launch
         the target, and we want to interrupt it later on.  The
         interrupt command will have its own token, but when the
         target stops, we must display the token corresponding to the
         last execution command given. So we have another string where
         we copy the token (previous_async_command), if this was
         indeed the token of an execution command, and when we stop we
         print that one. This is possible because the interrupt
         command, when over, will copy that token back into the
         default token string (last_async_command). */

      if (target_executing)
	{
	  if (!previous_async_command)
	    previous_async_command = xstrdup (last_async_command);
	  if (strcmp (parse->command, "exec-interrupt"))
	    {
	      fputs_unfiltered (parse->token, raw_stdout);
	      fputs_unfiltered ("^error,msg=\"", raw_stdout);
	      fputs_unfiltered ("Cannot execute command ", raw_stdout);
	      fputstr_unfiltered (parse->command, '"', raw_stdout);
	      fputs_unfiltered (" while target running", raw_stdout);
	      fputs_unfiltered ("\"\n", raw_stdout);
	      return MI_CMD_ERROR;
	    }
	}
      last_async_command = xstrdup (parse->token);
      make_exec_cleanup (free_current_contents, &last_async_command);
      /* FIXME: DELETE THIS! */
      if (parse->cmd->args_func != NULL)
	return parse->cmd->args_func (parse->args, 0 /*from_tty */ );
      return parse->cmd->argv_func (parse->command, parse->argv, parse->argc);
    }
  else if (parse->cmd->cli.cmd != 0)
    {
      /* FIXME: DELETE THIS. */
      /* The operation is still implemented by a cli command */
      /* Must be a synchronous one */
      mi_execute_cli_command (parse->cmd->cli.cmd, parse->cmd->cli.args_p,
			      parse->args);
      return MI_CMD_DONE;
    }
  else
    {
      /* FIXME: DELETE THIS. */
      fputs_unfiltered (parse->token, raw_stdout);
      fputs_unfiltered ("^error,msg=\"", raw_stdout);
      fputs_unfiltered ("Undefined mi command: ", raw_stdout);
      fputstr_unfiltered (parse->command, '"', raw_stdout);
      fputs_unfiltered (" (missing implementation)", raw_stdout);
      fputs_unfiltered ("\"\n", raw_stdout);
      return MI_CMD_ERROR;
    }
}
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
typedef  enum mi_cmd_result { ____Placeholder_mi_cmd_result } mi_cmd_result ;

/* Variables and functions */
 int MI_CMD_ERROR ; 
 int MI_CMD_QUIET ; 
 int /*<<< orphan*/  fputs_unfiltered (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  interrupt_target_command (char*,int) ; 
 char* last_async_command ; 
 int /*<<< orphan*/  mi_error_message ; 
 int /*<<< orphan*/  mi_out_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mi_out_rewind (int /*<<< orphan*/ ) ; 
 char* previous_async_command ; 
 int /*<<< orphan*/  raw_stdout ; 
 int /*<<< orphan*/  target_executing ; 
 int /*<<< orphan*/  uiout ; 
 int /*<<< orphan*/  xasprintf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  xfree (char*) ; 
 char* xstrdup (char*) ; 

enum mi_cmd_result
mi_cmd_exec_interrupt (char *args, int from_tty)
{
  if (!target_executing)
    {
      xasprintf (&mi_error_message,
		 "mi_cmd_exec_interrupt: Inferior not executing.");
      return MI_CMD_ERROR;
    }
  interrupt_target_command (args, from_tty);
  if (last_async_command)
    fputs_unfiltered (last_async_command, raw_stdout);
  fputs_unfiltered ("^done", raw_stdout);
  xfree (last_async_command);
  if (previous_async_command)
    last_async_command = xstrdup (previous_async_command);
  xfree (previous_async_command);
  previous_async_command = NULL;
  mi_out_put (uiout, raw_stdout);
  mi_out_rewind (uiout);
  fputs_unfiltered ("\n", raw_stdout);
  return MI_CMD_QUIET;
}
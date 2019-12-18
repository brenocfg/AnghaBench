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
 int MI_CMD_ERROR ; 
 int NUM_REGS ; 
 char* REGISTER_NAME (int) ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int get_register (int,int) ; 
 struct cleanup* make_cleanup_ui_out_list_begin_end (int /*<<< orphan*/ ,char*) ; 
 struct cleanup* make_cleanup_ui_out_tuple_begin_end (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mi_error_message ; 
 int /*<<< orphan*/  target_has_registers ; 
 int /*<<< orphan*/  ui_out_field_int (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  uiout ; 
 int /*<<< orphan*/  xasprintf (int /*<<< orphan*/ *,char*) ; 

enum mi_cmd_result
mi_cmd_data_list_register_values (char *command, char **argv, int argc)
{
  int regnum, numregs, format, result;
  int i;
  struct cleanup *list_cleanup, *tuple_cleanup;

  /* Note that the test for a valid register must include checking the
     REGISTER_NAME because NUM_REGS may be allocated for the union of
     the register sets within a family of related processors.  In this
     case, some entries of REGISTER_NAME will change depending upon
     the particular processor being debugged.  */

  numregs = NUM_REGS;

  if (argc == 0)
    {
      xasprintf (&mi_error_message,
		 "mi_cmd_data_list_register_values: Usage: -data-list-register-values <format> [<regnum1>...<regnumN>]");
      return MI_CMD_ERROR;
    }

  format = (int) argv[0][0];

  if (!target_has_registers)
    {
      xasprintf (&mi_error_message,
		 "mi_cmd_data_list_register_values: No registers.");
      return MI_CMD_ERROR;
    }

  list_cleanup = make_cleanup_ui_out_list_begin_end (uiout, "register-values");

  if (argc == 1)		/* No args, beside the format: do all the regs */
    {
      for (regnum = 0;
	   regnum < numregs;
	   regnum++)
	{
	  if (REGISTER_NAME (regnum) == NULL
	      || *(REGISTER_NAME (regnum)) == '\0')
	    continue;
	  tuple_cleanup = make_cleanup_ui_out_tuple_begin_end (uiout, NULL);
	  ui_out_field_int (uiout, "number", regnum);
	  result = get_register (regnum, format);
	  if (result == -1)
	    {
	      do_cleanups (list_cleanup);
	      return MI_CMD_ERROR;
	    }
	  do_cleanups (tuple_cleanup);
	}
    }

  /* Else, list of register #s, just do listed regs */
  for (i = 1; i < argc; i++)
    {
      regnum = atoi (argv[i]);

      if (regnum >= 0
	  && regnum < numregs
	  && REGISTER_NAME (regnum) != NULL
	  && *REGISTER_NAME (regnum) != '\000')
	{
	  tuple_cleanup = make_cleanup_ui_out_tuple_begin_end (uiout, NULL);
	  ui_out_field_int (uiout, "number", regnum);
	  result = get_register (regnum, format);
	  if (result == -1)
	    {
	      do_cleanups (list_cleanup);
	      return MI_CMD_ERROR;
	    }
	  do_cleanups (tuple_cleanup);
	}
      else
	{
	  do_cleanups (list_cleanup);
	  xasprintf (&mi_error_message, "bad register number");
	  return MI_CMD_ERROR;
	}
    }
  do_cleanups (list_cleanup);
  return MI_CMD_DONE;
}
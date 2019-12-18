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
 int NUM_PSEUDO_REGS ; 
 int NUM_REGS ; 
 char* REGISTER_NAME (int) ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 struct cleanup* make_cleanup_ui_out_list_begin_end (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mi_error_message ; 
 int /*<<< orphan*/  ui_out_field_string (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  uiout ; 
 int /*<<< orphan*/  xasprintf (int /*<<< orphan*/ *,char*) ; 

enum mi_cmd_result
mi_cmd_data_list_register_names (char *command, char **argv, int argc)
{
  int regnum, numregs;
  int i;
  struct cleanup *cleanup;

  /* Note that the test for a valid register must include checking the
     REGISTER_NAME because NUM_REGS may be allocated for the union of
     the register sets within a family of related processors.  In this
     case, some entries of REGISTER_NAME will change depending upon
     the particular processor being debugged.  */

  numregs = NUM_REGS + NUM_PSEUDO_REGS;

  cleanup = make_cleanup_ui_out_list_begin_end (uiout, "register-names");

  if (argc == 0)		/* No args, just do all the regs */
    {
      for (regnum = 0;
	   regnum < numregs;
	   regnum++)
	{
	  if (REGISTER_NAME (regnum) == NULL
	      || *(REGISTER_NAME (regnum)) == '\0')
	    ui_out_field_string (uiout, NULL, "");
	  else
	    ui_out_field_string (uiout, NULL, REGISTER_NAME (regnum));
	}
    }

  /* Else, list of register #s, just do listed regs */
  for (i = 0; i < argc; i++)
    {
      regnum = atoi (argv[i]);
      if (regnum < 0 || regnum >= numregs)
	{
	  do_cleanups (cleanup);
	  xasprintf (&mi_error_message, "bad register number");
	  return MI_CMD_ERROR;
	}
      if (REGISTER_NAME (regnum) == NULL
	  || *(REGISTER_NAME (regnum)) == '\0')
	ui_out_field_string (uiout, NULL, "");
      else
	ui_out_field_string (uiout, NULL, REGISTER_NAME (regnum));
    }
  do_cleanups (cleanup);
  return MI_CMD_DONE;
}
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
typedef  int /*<<< orphan*/  LONGEST ;

/* Variables and functions */
 int /*<<< orphan*/  DEPRECATED_REGISTER_BYTE (int) ; 
 int /*<<< orphan*/  DEPRECATED_REGISTER_RAW_SIZE (int) ; 
 int /*<<< orphan*/  DEPRECATED_REGISTER_SIZE ; 
 int MI_CMD_DONE ; 
 int MI_CMD_ERROR ; 
 int NUM_REGS ; 
 char* REGISTER_NAME (int) ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  deprecated_write_register_bytes (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  mi_error_message ; 
 int /*<<< orphan*/  parse_and_eval_address (char*) ; 
 int /*<<< orphan*/  store_signed_integer (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  target_has_registers ; 
 int /*<<< orphan*/  xasprintf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  xfree ; 
 void* xmalloc (int /*<<< orphan*/ ) ; 

enum mi_cmd_result
mi_cmd_data_write_register_values (char *command, char **argv, int argc)
{
  int regnum;
  int i;
  int numregs;
  LONGEST value;
  char format;

  /* Note that the test for a valid register must include checking the
     REGISTER_NAME because NUM_REGS may be allocated for the union of
     the register sets within a family of related processors.  In this
     case, some entries of REGISTER_NAME will change depending upon
     the particular processor being debugged.  */

  numregs = NUM_REGS;

  if (argc == 0)
    {
      xasprintf (&mi_error_message,
		 "mi_cmd_data_write_register_values: Usage: -data-write-register-values <format> [<regnum1> <value1>...<regnumN> <valueN>]");
      return MI_CMD_ERROR;
    }

  format = (int) argv[0][0];

  if (!target_has_registers)
    {
      xasprintf (&mi_error_message,
		 "mi_cmd_data_write_register_values: No registers.");
      return MI_CMD_ERROR;
    }

  if (!(argc - 1))
    {
      xasprintf (&mi_error_message,
		 "mi_cmd_data_write_register_values: No regs and values specified.");
      return MI_CMD_ERROR;
    }

  if ((argc - 1) % 2)
    {
      xasprintf (&mi_error_message,
		 "mi_cmd_data_write_register_values: Regs and vals are not in pairs.");
      return MI_CMD_ERROR;
    }

  for (i = 1; i < argc; i = i + 2)
    {
      regnum = atoi (argv[i]);

      if (regnum >= 0
	  && regnum < numregs
	  && REGISTER_NAME (regnum) != NULL
	  && *REGISTER_NAME (regnum) != '\000')
	{
	  void *buffer;
	  struct cleanup *old_chain;

	  /* Get the value as a number */
	  value = parse_and_eval_address (argv[i + 1]);
	  /* Get the value into an array */
	  buffer = xmalloc (DEPRECATED_REGISTER_SIZE);
	  old_chain = make_cleanup (xfree, buffer);
	  store_signed_integer (buffer, DEPRECATED_REGISTER_SIZE, value);
	  /* Write it down */
	  deprecated_write_register_bytes (DEPRECATED_REGISTER_BYTE (regnum), buffer, DEPRECATED_REGISTER_RAW_SIZE (regnum));
	  /* Free the buffer.  */
	  do_cleanups (old_chain);
	}
      else
	{
	  xasprintf (&mi_error_message, "bad register number");
	  return MI_CMD_ERROR;
	}
    }
  return MI_CMD_DONE;
}
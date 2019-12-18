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
struct value {int dummy; } ;
struct qt_args {char* args; int from_tty; } ;

/* Variables and functions */
 int /*<<< orphan*/  RETURN_MASK_ALL ; 
 int /*<<< orphan*/  catch_errors (int /*<<< orphan*/ ,struct qt_args*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 struct value* parse_and_eval (char*) ; 
 int /*<<< orphan*/  quit_target ; 
 scalar_t__ value_as_long (struct value*) ; 

void
quit_force (char *args, int from_tty)
{
  int exit_code = 0;
  struct qt_args qt;

  /* An optional expression may be used to cause gdb to terminate with the 
     value of that expression. */
  if (args)
    {
      struct value *val = parse_and_eval (args);

      exit_code = (int) value_as_long (val);
    }

  qt.args = args;
  qt.from_tty = from_tty;

  /* We want to handle any quit errors and exit regardless.  */
  catch_errors (quit_target, &qt,
	        "Quitting: ", RETURN_MASK_ALL);

  exit (exit_code);
}
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

/* Variables and functions */
 int /*<<< orphan*/  Val_pretty_default ; 
 struct value* access_value_history (int) ; 
 int /*<<< orphan*/  gdb_stdout ; 
 int parse_and_eval_long (char*) ; 
 int /*<<< orphan*/  printf_filtered (char*,...) ; 
 int value_history_count ; 
 int /*<<< orphan*/  value_print (struct value*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
show_values (char *num_exp, int from_tty)
{
  int i;
  struct value *val;
  static int num = 1;

  if (num_exp)
    {
      /* "info history +" should print from the stored position.
         "info history <exp>" should print around value number <exp>.  */
      if (num_exp[0] != '+' || num_exp[1] != '\0')
	num = parse_and_eval_long (num_exp) - 5;
    }
  else
    {
      /* "info history" means print the last 10 values.  */
      num = value_history_count - 9;
    }

  if (num <= 0)
    num = 1;

  for (i = num; i < num + 10 && i <= value_history_count; i++)
    {
      val = access_value_history (i);
      printf_filtered ("$%d = ", i);
      value_print (val, gdb_stdout, 0, Val_pretty_default);
      printf_filtered ("\n");
    }

  /* The next "info history +" should start after what we just printed.  */
  num += 10;

  /* Hitting just return after this command should do the same thing as
     "info history +".  If num_exp is null, this is unnecessary, since
     "info history +" is not useful after "info history".  */
  if (from_tty && num_exp)
    {
      num_exp[0] = '+';
      num_exp[1] = '\0';
    }
}
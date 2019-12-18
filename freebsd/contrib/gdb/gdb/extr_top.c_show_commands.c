#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  line; } ;

/* Variables and functions */
 int Hist_print ; 
 int history_base ; 
 TYPE_1__* history_get (int) ; 
 int history_size ; 
 int parse_and_eval_long (char*) ; 
 int /*<<< orphan*/  printf_filtered (char*,int,int /*<<< orphan*/ ) ; 

void
show_commands (char *args, int from_tty)
{
  /* Index for history commands.  Relative to history_base.  */
  int offset;

  /* Number of the history entry which we are planning to display next.
     Relative to history_base.  */
  static int num = 0;

  /* The first command in the history which doesn't exist (i.e. one more
     than the number of the last command).  Relative to history_base.  */
  int hist_len;

  /* Print out some of the commands from the command history.  */
  /* First determine the length of the history list.  */
  hist_len = history_size;
  for (offset = 0; offset < history_size; offset++)
    {
      if (!history_get (history_base + offset))
	{
	  hist_len = offset;
	  break;
	}
    }

  if (args)
    {
      if (args[0] == '+' && args[1] == '\0')
	/* "info editing +" should print from the stored position.  */
	;
      else
	/* "info editing <exp>" should print around command number <exp>.  */
	num = (parse_and_eval_long (args) - history_base) - Hist_print / 2;
    }
  /* "show commands" means print the last Hist_print commands.  */
  else
    {
      num = hist_len - Hist_print;
    }

  if (num < 0)
    num = 0;

  /* If there are at least Hist_print commands, we want to display the last
     Hist_print rather than, say, the last 6.  */
  if (hist_len - num < Hist_print)
    {
      num = hist_len - Hist_print;
      if (num < 0)
	num = 0;
    }

  for (offset = num; offset < num + Hist_print && offset < hist_len; offset++)
    {
      printf_filtered ("%5d  %s\n", history_base + offset,
		       (history_get (history_base + offset))->line);
    }

  /* The next command we want to display is the next one that we haven't
     displayed yet.  */
  num += Hist_print;

  /* If the user repeats this command with return, it should do what
     "show commands +" does.  This is unnecessary if arg is null,
     because "show commands +" is not useful after "show commands".  */
  if (from_tty && args)
    {
      args[0] = '+';
      args[1] = '\0';
    }
}
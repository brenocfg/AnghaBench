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
struct tracepoint {int number; scalar_t__ step_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_actions (struct tracepoint*) ; 
 struct tracepoint* get_tracepoint_by_number (char**,int /*<<< orphan*/ ,int) ; 
 scalar_t__ input_from_terminal_p () ; 
 int /*<<< orphan*/  printf_filtered (char*,char*,char*) ; 
 int /*<<< orphan*/  read_actions (struct tracepoint*) ; 
 int /*<<< orphan*/  readline_begin_hook (char*,char*,char*) ; 
 int /*<<< orphan*/  readline_end_hook () ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  stub1 (char*,char*,char*) ; 
 int /*<<< orphan*/  stub2 () ; 

__attribute__((used)) static void
trace_actions_command (char *args, int from_tty)
{
  struct tracepoint *t;
  char tmpbuf[128];
  char *end_msg = "End with a line saying just \"end\".";

  t = get_tracepoint_by_number (&args, 0, 1);
  if (t)
    {
      sprintf (tmpbuf, "Enter actions for tracepoint %d, one per line.",
	       t->number);

      if (from_tty)
	{
	  if (readline_begin_hook)
	    (*readline_begin_hook) ("%s  %s\n", tmpbuf, end_msg);
	  else if (input_from_terminal_p ())
	    printf_filtered ("%s\n%s\n", tmpbuf, end_msg);
	}

      free_actions (t);
      t->step_count = 0;	/* read_actions may set this */
      read_actions (t);

      if (readline_end_hook)
	(*readline_end_hook) ();
      /* tracepoints_changed () */
    }
  /* else just return */
}
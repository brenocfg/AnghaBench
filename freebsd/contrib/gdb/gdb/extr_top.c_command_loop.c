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

/* Variables and functions */
 int ISATTY (scalar_t__) ; 
 int /*<<< orphan*/  bpstat_do_actions (int /*<<< orphan*/ *) ; 
 char* command_line_input (char*,int,char*) ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  execute_command (char*,int) ; 
 int /*<<< orphan*/  feof (scalar_t__) ; 
 char* get_prompt () ; 
 long get_run_time () ; 
 scalar_t__ instream ; 
 char* lim_at_start ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  null_cleanup ; 
 int /*<<< orphan*/  printf_unfiltered (char*,long,char,...) ; 
 scalar_t__ quit_flag ; 
 int /*<<< orphan*/  reinitialize_more_filter () ; 
 scalar_t__ sbrk (int /*<<< orphan*/ ) ; 
 scalar_t__ stdin ; 
 int /*<<< orphan*/  stop_bpstat ; 
 int /*<<< orphan*/  stub1 (scalar_t__,char*) ; 
 int /*<<< orphan*/  window_hook (scalar_t__,char*) ; 

void
command_loop (void)
{
  struct cleanup *old_chain;
  char *command;
  int stdin_is_tty = ISATTY (stdin);
  long time_at_cmd_start;
#ifdef HAVE_SBRK
  long space_at_cmd_start = 0;
#endif
  extern int display_time;
  extern int display_space;

  while (instream && !feof (instream))
    {
      if (window_hook && instream == stdin)
	(*window_hook) (instream, get_prompt ());

      quit_flag = 0;
      if (instream == stdin && stdin_is_tty)
	reinitialize_more_filter ();
      old_chain = make_cleanup (null_cleanup, 0);

      /* Get a command-line. This calls the readline package. */
      command = command_line_input (instream == stdin ?
				    get_prompt () : (char *) NULL,
				    instream == stdin, "prompt");
      if (command == 0)
	return;

      time_at_cmd_start = get_run_time ();

      if (display_space)
	{
#ifdef HAVE_SBRK
	  char *lim = (char *) sbrk (0);
	  space_at_cmd_start = lim - lim_at_start;
#endif
	}

      execute_command (command, instream == stdin);
      /* Do any commands attached to breakpoint we stopped at.  */
      bpstat_do_actions (&stop_bpstat);
      do_cleanups (old_chain);

      if (display_time)
	{
	  long cmd_time = get_run_time () - time_at_cmd_start;

	  printf_unfiltered ("Command execution time: %ld.%06ld\n",
			     cmd_time / 1000000, cmd_time % 1000000);
	}

      if (display_space)
	{
#ifdef HAVE_SBRK
	  char *lim = (char *) sbrk (0);
	  long space_now = lim - lim_at_start;
	  long space_diff = space_now - space_at_cmd_start;

	  printf_unfiltered ("Space used: %ld (%c%ld for this command)\n",
			     space_now,
			     (space_diff >= 0 ? '+' : '-'),
			     space_diff);
#endif
	}
    }
}
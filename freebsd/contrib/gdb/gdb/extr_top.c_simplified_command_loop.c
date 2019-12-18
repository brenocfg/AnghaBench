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
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  feof (scalar_t__) ; 
 char* get_prompt () ; 
 scalar_t__ instream ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  null_cleanup ; 
 scalar_t__ quit_flag ; 
 int /*<<< orphan*/  reinitialize_more_filter () ; 
 scalar_t__ stdin ; 
 int /*<<< orphan*/  stop_bpstat ; 
 char* stub1 (char*) ; 
 void stub2 (char*,int) ; 

void
simplified_command_loop (char *(*read_input_func) (char *),
			 void (*execute_command_func) (char *, int))
{
  struct cleanup *old_chain;
  char *command;
  int stdin_is_tty = ISATTY (stdin);

  while (instream && !feof (instream))
    {
      quit_flag = 0;
      if (instream == stdin && stdin_is_tty)
	reinitialize_more_filter ();
      old_chain = make_cleanup (null_cleanup, 0);

      /* Get a command-line. */
      command = (*read_input_func) (instream == stdin ?
				    get_prompt () : (char *) NULL);

      if (command == 0)
	return;

      (*execute_command_func) (command, instream == stdin);

      /* Do any commands attached to breakpoint we stopped at.  */
      bpstat_do_actions (&stop_bpstat);

      do_cleanups (old_chain);
    }
}
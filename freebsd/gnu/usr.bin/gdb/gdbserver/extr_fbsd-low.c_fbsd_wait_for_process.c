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
struct thread_info {int dummy; } ;
struct process_info {int lwpid; int stopped; int tid; scalar_t__ pending_is_breakpoint; } ;
struct TYPE_2__ {int /*<<< orphan*/ * get_pc; } ;

/* Variables and functions */
 scalar_t__ ECHILD ; 
 scalar_t__ WIFSTOPPED (int) ; 
 int /*<<< orphan*/  WNOHANG ; 
 int WSTOPSIG (int) ; 
 int /*<<< orphan*/  all_processes ; 
 int /*<<< orphan*/  all_threads ; 
 struct thread_info* current_inferior ; 
 scalar_t__ debug_threads ; 
 scalar_t__ errno ; 
 scalar_t__ find_inferior_id (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  get_stop_pc () ; 
 int /*<<< orphan*/  perror_with_name (char*) ; 
 int /*<<< orphan*/  stderr ; 
 TYPE_1__ the_low_target ; 
 int /*<<< orphan*/  usleep (int) ; 
 int waitpid (int,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fbsd_wait_for_process (struct process_info **childp, int *wstatp)
{
  int ret;
  int to_wait_for = -1;

  if (*childp != NULL)
    to_wait_for = (*childp)->lwpid;

  while (1)
    {
      ret = waitpid (to_wait_for, wstatp, WNOHANG);

      if (ret == -1)
	{
	  if (errno != ECHILD)
	    perror_with_name ("waitpid");
	}
      else if (ret > 0)
	break;

      usleep (1000);
    }

  if (debug_threads
      && (!WIFSTOPPED (*wstatp)
	  || (WSTOPSIG (*wstatp) != 32
	      && WSTOPSIG (*wstatp) != 33)))
    fprintf (stderr, "Got an event from %d (%x)\n", ret, *wstatp);

  if (to_wait_for == -1)
    *childp = (struct process_info *) find_inferior_id (&all_processes, ret);

  (*childp)->stopped = 1;
  (*childp)->pending_is_breakpoint = 0;

  if (debug_threads
      && WIFSTOPPED (*wstatp))
    {
      current_inferior = (struct thread_info *)
	find_inferior_id (&all_threads, (*childp)->tid);
      /* For testing only; i386_stop_pc prints out a diagnostic.  */
      if (the_low_target.get_pc != NULL)
	get_stop_pc ();
    }
}
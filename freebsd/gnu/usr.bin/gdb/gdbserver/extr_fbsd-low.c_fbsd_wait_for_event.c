#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct thread_info {int dummy; } ;
struct TYPE_7__ {int id; } ;
struct process_info {int lwpid; int status_pending; int tid; int stepping; scalar_t__ bp_reinsert; int pending_is_breakpoint; void* pending_stop_pc; TYPE_2__ head; scalar_t__ stop_expected; scalar_t__ status_pending_p; } ;
struct TYPE_8__ {scalar_t__ head; scalar_t__ tail; } ;
struct TYPE_6__ {scalar_t__ (* breakpoint_at ) (void*) ;int /*<<< orphan*/  (* breakpoint_reinsert_addr ) () ;int /*<<< orphan*/ * get_pc; } ;
typedef  void* CORE_ADDR ;

/* Variables and functions */
 scalar_t__ SIGSTOP ; 
 scalar_t__ SIGTRAP ; 
 scalar_t__ WIFSTOPPED (int) ; 
 scalar_t__ WSTOPSIG (int) ; 
 int /*<<< orphan*/  all_processes ; 
 TYPE_3__ all_threads ; 
 scalar_t__ check_breakpoints (void*) ; 
 scalar_t__ check_removed_breakpoint (struct process_info*) ; 
 struct thread_info* current_inferior ; 
 int /*<<< orphan*/  dead_thread_notify (int) ; 
 scalar_t__ debug_threads ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  fbsd_resume_one_process (TYPE_2__*,int,scalar_t__) ; 
 int /*<<< orphan*/  fbsd_wait_for_process (struct process_info**,int*) ; 
 scalar_t__ find_inferior (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ find_inferior_id (TYPE_3__*,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (struct process_info*) ; 
 struct thread_info* get_process_thread (struct process_info*) ; 
 void* get_stop_pc () ; 
 struct process_info* get_thread_process (struct thread_info*) ; 
 int /*<<< orphan*/  reinsert_breakpoint (scalar_t__) ; 
 int /*<<< orphan*/  reinsert_breakpoint_by_bp (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_inferior (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  remove_thread (struct thread_info*) ; 
 int /*<<< orphan*/  status_pending_p ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stub1 () ; 
 scalar_t__ stub2 (void*) ; 
 TYPE_1__ the_low_target ; 
 int /*<<< orphan*/  uninsert_breakpoint (void*) ; 
 scalar_t__ using_threads ; 

__attribute__((used)) static int
fbsd_wait_for_event (struct thread_info *child)
{
  CORE_ADDR stop_pc;
  struct process_info *event_child;
  int wstat;

  /* Check for a process with a pending status.  */
  /* It is possible that the user changed the pending task's registers since
     it stopped.  We correctly handle the change of PC if we hit a breakpoint
     (in check_removed_breakpoint); signals should be reported anyway.  */
  if (child == NULL)
    {
      event_child = (struct process_info *)
	find_inferior (&all_processes, status_pending_p, NULL);
      if (debug_threads && event_child)
	fprintf (stderr, "Got a pending child %d\n", event_child->lwpid);
    }
  else
    {
      event_child = get_thread_process (child);
      if (event_child->status_pending_p
	  && check_removed_breakpoint (event_child))
	event_child = NULL;
    }

  if (event_child != NULL)
    {
      if (event_child->status_pending_p)
	{
	  if (debug_threads)
	    fprintf (stderr, "Got an event from pending child %d (%04x)\n",
		     event_child->lwpid, event_child->status_pending);
	  wstat = event_child->status_pending;
	  event_child->status_pending_p = 0;
	  event_child->status_pending = 0;
	  current_inferior = get_process_thread (event_child);
	  return wstat;
	}
    }

  /* We only enter this loop if no process has a pending wait status.  Thus
     any action taken in response to a wait status inside this loop is
     responding as soon as we detect the status, not after any pending
     events.  */
  while (1)
    {
      if (child == NULL)
	event_child = NULL;
      else
	event_child = get_thread_process (child);

      fbsd_wait_for_process (&event_child, &wstat);

      if (event_child == NULL)
	error ("event from unknown child");

      current_inferior = (struct thread_info *)
	find_inferior_id (&all_threads, event_child->tid);

      if (using_threads)
	{
	  /* Check for thread exit.  */
	  if (! WIFSTOPPED (wstat))
	    {
	      if (debug_threads)
		fprintf (stderr, "Thread %d (LWP %d) exiting\n",
			 event_child->tid, event_child->head.id);

	      /* If the last thread is exiting, just return.  */
	      if (all_threads.head == all_threads.tail)
		return wstat;

	      dead_thread_notify (event_child->tid);

	      remove_inferior (&all_processes, &event_child->head);
	      free (event_child);
	      remove_thread (current_inferior);
	      current_inferior = (struct thread_info *) all_threads.head;

	      /* If we were waiting for this particular child to do something...
		 well, it did something.  */
	      if (child != NULL)
		return wstat;

	      /* Wait for a more interesting event.  */
	      continue;
	    }

	  if (WIFSTOPPED (wstat)
	      && WSTOPSIG (wstat) == SIGSTOP
	      && event_child->stop_expected)
	    {
	      if (debug_threads)
		fprintf (stderr, "Expected stop.\n");
	      event_child->stop_expected = 0;
	      fbsd_resume_one_process (&event_child->head,
					event_child->stepping, 0);
	      continue;
	    }

	  /* FIXME drow/2002-06-09: Get signal numbers from the inferior's
	     thread library?  */
	  if (WIFSTOPPED (wstat))
	    {
	      if (debug_threads)
		fprintf (stderr, "Ignored signal %d for %d (LWP %d).\n",
			 WSTOPSIG (wstat), event_child->tid,
			 event_child->head.id);
	      fbsd_resume_one_process (&event_child->head,
					event_child->stepping,
					WSTOPSIG (wstat));
	      continue;
	    }
	}

      /* If this event was not handled above, and is not a SIGTRAP, report
	 it.  */
      if (!WIFSTOPPED (wstat) || WSTOPSIG (wstat) != SIGTRAP)
	return wstat;

      /* If this target does not support breakpoints, we simply report the
	 SIGTRAP; it's of no concern to us.  */
      if (the_low_target.get_pc == NULL)
	return wstat;

      stop_pc = get_stop_pc ();

      /* bp_reinsert will only be set if we were single-stepping.
	 Notice that we will resume the process after hitting
	 a gdbserver breakpoint; single-stepping to/over one
	 is not supported (yet).  */
      if (event_child->bp_reinsert != 0)
	{
	  if (debug_threads)
	    fprintf (stderr, "Reinserted breakpoint.\n");
	  reinsert_breakpoint (event_child->bp_reinsert);
	  event_child->bp_reinsert = 0;

	  /* Clear the single-stepping flag and SIGTRAP as we resume.  */
	  fbsd_resume_one_process (&event_child->head, 0, 0);
	  continue;
	}

      if (debug_threads)
	fprintf (stderr, "Hit a (non-reinsert) breakpoint.\n");

      if (check_breakpoints (stop_pc) != 0)
	{
	  /* We hit one of our own breakpoints.  We mark it as a pending
	     breakpoint, so that check_removed_breakpoint () will do the PC
	     adjustment for us at the appropriate time.  */
	  event_child->pending_is_breakpoint = 1;
	  event_child->pending_stop_pc = stop_pc;

	  /* Now we need to put the breakpoint back.  We continue in the event
	     loop instead of simply replacing the breakpoint right away,
	     in order to not lose signals sent to the thread that hit the
	     breakpoint.  Unfortunately this increases the window where another
	     thread could sneak past the removed breakpoint.  For the current
	     use of server-side breakpoints (thread creation) this is
	     acceptable; but it needs to be considered before this breakpoint
	     mechanism can be used in more general ways.  For some breakpoints
	     it may be necessary to stop all other threads, but that should
	     be avoided where possible.

	     If breakpoint_reinsert_addr is NULL, that means that we can
	     use PT_STEP on this platform.  Uninsert the breakpoint,
	     mark it for reinsertion, and single-step.

	     Otherwise, call the target function to figure out where we need
	     our temporary breakpoint, create it, and continue executing this
	     process.  */
	  if (the_low_target.breakpoint_reinsert_addr == NULL)
	    {
	      event_child->bp_reinsert = stop_pc;
	      uninsert_breakpoint (stop_pc);
	      fbsd_resume_one_process (&event_child->head, 1, 0);
	    }
	  else
	    {
	      reinsert_breakpoint_by_bp
		(stop_pc, (*the_low_target.breakpoint_reinsert_addr) ());
	      fbsd_resume_one_process (&event_child->head, 0, 0);
	    }

	  continue;
	}

      /* If we were single-stepping, we definitely want to report the
	 SIGTRAP.  The single-step operation has completed, so also
         clear the stepping flag; in general this does not matter,
	 because the SIGTRAP will be reported to the client, which
	 will give us a new action for this thread, but clear it for
	 consistency anyway.  It's safe to clear the stepping flag
         because the only consumer of get_stop_pc () after this point
	 is check_removed_breakpoint, and pending_is_breakpoint is not
	 set.  It might be wiser to use a step_completed flag instead.  */
      if (event_child->stepping)
	{
	  event_child->stepping = 0;
	  return wstat;
	}

      /* A SIGTRAP that we can't explain.  It may have been a breakpoint.
	 Check if it is a breakpoint, and if so mark the process information
	 accordingly.  This will handle both the necessary fiddling with the
	 PC on decr_pc_after_break targets and suppressing extra threads
	 hitting a breakpoint if two hit it at once and then GDB removes it
	 after the first is reported.  Arguably it would be better to report
	 multiple threads hitting breakpoints simultaneously, but the current
	 remote protocol does not allow this.  */
      if ((*the_low_target.breakpoint_at) (stop_pc))
	{
	  event_child->pending_is_breakpoint = 1;
	  event_child->pending_stop_pc = stop_pc;
	}

      return wstat;
    }

  /* NOTREACHED */
  return 0;
}
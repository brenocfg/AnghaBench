#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct thread_resume {int thread; scalar_t__ leave_stopped; scalar_t__ sig; scalar_t__ step; } ;
struct thread_info {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/ * tail; int /*<<< orphan*/  head; } ;
struct TYPE_4__ {scalar_t__ head; scalar_t__ tail; } ;

/* Variables and functions */
 int WEXITSTATUS (int) ; 
 scalar_t__ WIFEXITED (int) ; 
 int /*<<< orphan*/  WIFSTOPPED (int) ; 
 scalar_t__ WSTOPSIG (int) ; 
 int WTERMSIG (int) ; 
 TYPE_3__ all_processes ; 
 TYPE_1__ all_threads ; 
 int /*<<< orphan*/  clear_inferiors () ; 
 scalar_t__ cont_thread ; 
 int /*<<< orphan*/  disable_async_io () ; 
 int /*<<< orphan*/  enable_async_io () ; 
 int /*<<< orphan*/  fbsd_resume (struct thread_resume*) ; 
 int fbsd_wait_for_event (struct thread_info*) ; 
 scalar_t__ find_inferior_id (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stop_all_processes () ; 
 int /*<<< orphan*/  unblock_async_io () ; 

__attribute__((used)) static unsigned char
fbsd_wait (char *status)
{
  int w;
  struct thread_info *child = NULL;

retry:
  /* If we were only supposed to resume one thread, only wait for
     that thread - if it's still alive.  If it died, however - which
     can happen if we're coming from the thread death case below -
     then we need to make sure we restart the other threads.  We could
     pick a thread at random or restart all; restarting all is less
     arbitrary.  */
  if (cont_thread > 0)
    {
      child = (struct thread_info *) find_inferior_id (&all_threads,
						       cont_thread);

      /* No stepping, no signal - unless one is pending already, of course.  */
      if (child == NULL)
	{
	  struct thread_resume resume_info;
	  resume_info.thread = -1;
	  resume_info.step = resume_info.sig = resume_info.leave_stopped = 0;
	  fbsd_resume (&resume_info);
	}
    }

  enable_async_io ();
  unblock_async_io ();
  w = fbsd_wait_for_event (child);
  stop_all_processes ();
  disable_async_io ();

  /* If we are waiting for a particular child, and it exited,
     fbsd_wait_for_event will return its exit status.  Similarly if
     the last child exited.  If this is not the last child, however,
     do not report it as exited until there is a 'thread exited' response
     available in the remote protocol.  Instead, just wait for another event.
     This should be safe, because if the thread crashed we will already
     have reported the termination signal to GDB; that should stop any
     in-progress stepping operations, etc.

     Report the exit status of the last thread to exit.  This matches
     LinuxThreads' behavior.  */

  if (all_threads.head == all_threads.tail)
    {
      if (WIFEXITED (w))
	{
	  fprintf (stderr, "\nChild exited with retcode = %x \n", WEXITSTATUS (w));
	  *status = 'W';
	  clear_inferiors ();
	  free (all_processes.head);
	  all_processes.head = all_processes.tail = NULL;
	  return ((unsigned char) WEXITSTATUS (w));
	}
      else if (!WIFSTOPPED (w))
	{
	  fprintf (stderr, "\nChild terminated with signal = %x \n", WTERMSIG (w));
	  *status = 'X';
	  clear_inferiors ();
	  free (all_processes.head);
	  all_processes.head = all_processes.tail = NULL;
	  return ((unsigned char) WTERMSIG (w));
	}
    }
  else
    {
      if (!WIFSTOPPED (w))
	goto retry;
    }

  *status = 'T';
  return ((unsigned char) WSTOPSIG (w));
}
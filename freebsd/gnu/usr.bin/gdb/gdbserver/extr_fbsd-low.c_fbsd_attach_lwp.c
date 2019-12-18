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
struct process_info {int stop_expected; } ;

/* Variables and functions */
 int /*<<< orphan*/  PT_ATTACH ; 
 int /*<<< orphan*/  _exit (int) ; 
 scalar_t__ add_process (int) ; 
 int /*<<< orphan*/  add_thread (int,struct process_info*) ; 
 int errno ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,char*,int) ; 
 scalar_t__ ptrace (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stopping_threads ; 
 char* strerror (int) ; 
 int /*<<< orphan*/  using_threads ; 

void
fbsd_attach_lwp (int pid, int tid)
{
  struct process_info *new_process;

  if (ptrace (PT_ATTACH, pid, 0, 0) != 0)
    {
      fprintf (stderr, "Cannot attach to process %d: %s (%d)\n", pid,
	       strerror (errno), errno);
      fflush (stderr);

      /* If we fail to attach to an LWP, just return.  */
      if (!using_threads)
	_exit (0177);
      return;
    }

  new_process = (struct process_info *) add_process (pid);
  add_thread (tid, new_process);

  /* The next time we wait for this LWP we'll see a SIGSTOP as PTRACE_ATTACH
     brings it to a halt.  We should ignore that SIGSTOP and resume the process
     (unless this is the first process, in which case the flag will be cleared
     in fbsd_attach).

     On the other hand, if we are currently trying to stop all threads, we
     should treat the new thread as if we had sent it a SIGSTOP.  This works
     because we are guaranteed that add_process added us to the end of the
     list, and so the new thread has not yet reached wait_for_sigstop (but
     will).  */
  if (! stopping_threads)
    new_process->stop_expected = 1;
}
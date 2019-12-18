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
struct thread_resume {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  all_processes ; 
 int /*<<< orphan*/  all_threads ; 
 int /*<<< orphan*/  block_async_io () ; 
 scalar_t__ debug_threads ; 
 int /*<<< orphan*/  enable_async_io () ; 
 int /*<<< orphan*/  fbsd_continue_one_thread ; 
 int /*<<< orphan*/  fbsd_queue_one_thread ; 
 int /*<<< orphan*/  fbsd_set_resume_request ; 
 int /*<<< orphan*/  find_inferior (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  for_each_inferior (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 struct thread_resume* resume_ptr ; 
 int /*<<< orphan*/  resume_status_pending_p ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
fbsd_resume (struct thread_resume *resume_info)
{
  int pending_flag;

  /* Yes, the use of a global here is rather ugly.  */
  resume_ptr = resume_info;

  for_each_inferior (&all_threads, fbsd_set_resume_request);

  /* If there is a thread which would otherwise be resumed, which
     has a pending status, then don't resume any threads - we can just
     report the pending status.  Make sure to queue any signals
     that would otherwise be sent.  */
  pending_flag = 0;
  find_inferior (&all_processes, resume_status_pending_p, &pending_flag);

  if (debug_threads)
    {
      if (pending_flag)
	fprintf (stderr, "Not resuming, pending status\n");
      else
	fprintf (stderr, "Resuming, no pending status\n");
    }

  if (pending_flag)
    for_each_inferior (&all_threads, fbsd_queue_one_thread);
  else
    {
      block_async_io ();
      enable_async_io ();
      for_each_inferior (&all_threads, fbsd_continue_one_thread);
    }
}
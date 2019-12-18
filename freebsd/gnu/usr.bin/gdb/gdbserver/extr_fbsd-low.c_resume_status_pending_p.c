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
struct process_info {scalar_t__ status_pending_p; TYPE_1__* resume; } ;
struct inferior_list_entry {int dummy; } ;
struct TYPE_2__ {scalar_t__ leave_stopped; } ;

/* Variables and functions */
 int /*<<< orphan*/  check_removed_breakpoint (struct process_info*) ; 

__attribute__((used)) static int
resume_status_pending_p (struct inferior_list_entry *entry, void *flag_p)
{
  struct process_info *process = (struct process_info *) entry;

  /* Processes which will not be resumed are not interesting, because
     we might not wait for them next time through fbsd_wait.  */
  if (process->resume->leave_stopped)
    return 0;

  /* If this thread has a removed breakpoint, we won't have any
     events to report later, so check now.  check_removed_breakpoint
     may clear status_pending_p.  We avoid calling check_removed_breakpoint
     for any thread that we are not otherwise going to resume - this
     lets us preserve stopped status when two threads hit a breakpoint.
     GDB removes the breakpoint to single-step a particular thread
     past it, then re-inserts it and resumes all threads.  We want
     to report the second thread without resuming it in the interim.  */
  if (process->status_pending_p)
    check_removed_breakpoint (process);

  if (process->status_pending_p)
    * (int *) flag_p = 1;

  return 0;
}
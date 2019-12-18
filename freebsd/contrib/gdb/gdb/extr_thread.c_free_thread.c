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
struct thread_info {struct thread_info* private; scalar_t__ step_resume_breakpoint; } ;

/* Variables and functions */
 int /*<<< orphan*/  delete_breakpoint (scalar_t__) ; 
 int /*<<< orphan*/  xfree (struct thread_info*) ; 

__attribute__((used)) static void
free_thread (struct thread_info *tp)
{
  /* NOTE: this will take care of any left-over step_resume breakpoints,
     but not any user-specified thread-specific breakpoints. */
  if (tp->step_resume_breakpoint)
    delete_breakpoint (tp->step_resume_breakpoint);

  /* FIXME: do I ever need to call the back-end to give it a
     chance at this private data before deleting the thread?  */
  if (tp->private)
    xfree (tp->private);

  xfree (tp);
}
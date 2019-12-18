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
struct thread_info {struct breakpoint* step_resume_breakpoint; struct thread_info* next; } ;
struct breakpoint {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  delete_breakpoint (struct breakpoint*) ; 
 struct thread_info* thread_list ; 

void
delete_step_resume_breakpoint (void *arg)
{
  struct breakpoint **breakpointp = (struct breakpoint **) arg;
  struct thread_info *tp;

  if (*breakpointp != NULL)
    {
      delete_breakpoint (*breakpointp);
      for (tp = thread_list; tp; tp = tp->next)
	if (tp->step_resume_breakpoint == *breakpointp)
	  tp->step_resume_breakpoint = NULL;

      *breakpointp = NULL;
    }
}
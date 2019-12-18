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
struct thread_resume {int thread; int step; int sig; int leave_stopped; } ;
struct inferior_list_entry {int id; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* resume ) (struct thread_resume*) ;} ;

/* Variables and functions */
 scalar_t__ cont_thread ; 
 scalar_t__ current_inferior ; 
 int /*<<< orphan*/  stub1 (struct thread_resume*) ; 
 TYPE_1__* the_target ; 

void
myresume (int step, int sig)
{
  struct thread_resume resume_info[2];
  int n = 0;

  if (step || sig || cont_thread > 0)
    {
      resume_info[0].thread
	= ((struct inferior_list_entry *) current_inferior)->id;
      resume_info[0].step = step;
      resume_info[0].sig = sig;
      resume_info[0].leave_stopped = 0;
      n++;
    }
  resume_info[n].thread = -1;
  resume_info[n].step = 0;
  resume_info[n].sig = 0;
  resume_info[n].leave_stopped = (cont_thread > 0);

  (*the_target->resume) (resume_info);
}
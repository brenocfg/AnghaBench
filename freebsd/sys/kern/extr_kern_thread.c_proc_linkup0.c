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
struct thread {int dummy; } ;
struct proc {int /*<<< orphan*/  p_threads; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  proc_linkup (struct proc*,struct thread*) ; 

void
proc_linkup0(struct proc *p, struct thread *td)
{
	TAILQ_INIT(&p->p_threads);	     /* all threads in proc */
	proc_linkup(p, td);
}
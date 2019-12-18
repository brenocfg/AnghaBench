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
struct thread {scalar_t__ td_sticks; scalar_t__ td_iticks; scalar_t__ td_uticks; scalar_t__ td_incruntime; int /*<<< orphan*/  td_rux; } ;
struct proc {int /*<<< orphan*/  p_rux; } ;

/* Variables and functions */
 int /*<<< orphan*/  ruxagg_locked (int /*<<< orphan*/ *,struct thread*) ; 
 int /*<<< orphan*/  thread_lock (struct thread*) ; 
 int /*<<< orphan*/  thread_unlock (struct thread*) ; 

void
ruxagg(struct proc *p, struct thread *td)
{

	thread_lock(td);
	ruxagg_locked(&p->p_rux, td);
	ruxagg_locked(&td->td_rux, td);
	td->td_incruntime = 0;
	td->td_uticks = 0;
	td->td_iticks = 0;
	td->td_sticks = 0;
	thread_unlock(td);
}
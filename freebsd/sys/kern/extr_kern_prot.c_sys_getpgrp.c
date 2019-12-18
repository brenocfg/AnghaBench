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
struct thread {int /*<<< orphan*/ * td_retval; struct proc* td_proc; } ;
struct proc {TYPE_1__* p_pgrp; } ;
struct getpgrp_args {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pg_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 

int
sys_getpgrp(struct thread *td, struct getpgrp_args *uap)
{
	struct proc *p = td->td_proc;

	PROC_LOCK(p);
	td->td_retval[0] = p->p_pgrp->pg_id;
	PROC_UNLOCK(p);
	return (0);
}
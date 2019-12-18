#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct thread {struct proc* td_proc; } ;
struct proc {TYPE_1__* p_session; } ;
struct TYPE_4__ {int sc_dev_opened; scalar_t__ sc_dev_sid; } ;
struct TYPE_3__ {scalar_t__ s_sid; } ;

/* Variables and functions */
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 TYPE_2__* autofs_softc ; 

bool
autofs_ignore_thread(const struct thread *td)
{
	struct proc *p;

	p = td->td_proc;

	if (autofs_softc->sc_dev_opened == false)
		return (false);

	PROC_LOCK(p);
	if (p->p_session->s_sid == autofs_softc->sc_dev_sid) {
		PROC_UNLOCK(p);
		return (true);
	}
	PROC_UNLOCK(p);

	return (false);
}
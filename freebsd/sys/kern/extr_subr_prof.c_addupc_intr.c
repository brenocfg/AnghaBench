#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uintfptr_t ;
typedef  scalar_t__ u_int ;
struct uprof {scalar_t__ pr_off; scalar_t__ pr_size; } ;
struct thread {int /*<<< orphan*/  td_flags; int /*<<< orphan*/  td_pflags; scalar_t__ td_profil_ticks; scalar_t__ td_profil_addr; TYPE_2__* td_proc; } ;
struct TYPE_5__ {TYPE_1__* p_stats; } ;
struct TYPE_4__ {struct uprof p_prof; } ;

/* Variables and functions */
 scalar_t__ PC_TO_INDEX (scalar_t__,struct uprof*) ; 
 int /*<<< orphan*/  PROC_PROFLOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  PROC_PROFUNLOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  TDF_ASTPENDING ; 
 int /*<<< orphan*/  TDP_OWEUPC ; 
 int /*<<< orphan*/  thread_lock (struct thread*) ; 
 int /*<<< orphan*/  thread_unlock (struct thread*) ; 

void
addupc_intr(struct thread *td, uintfptr_t pc, u_int ticks)
{
	struct uprof *prof;

	if (ticks == 0)
		return;
	prof = &td->td_proc->p_stats->p_prof;
	PROC_PROFLOCK(td->td_proc);
	if (pc < prof->pr_off || PC_TO_INDEX(pc, prof) >= prof->pr_size) {
		PROC_PROFUNLOCK(td->td_proc);
		return;			/* out of range; ignore */
	}

	PROC_PROFUNLOCK(td->td_proc);
	td->td_profil_addr = pc;
	td->td_profil_ticks = ticks;
	td->td_pflags |= TDP_OWEUPC;
	thread_lock(td);
	td->td_flags |= TDF_ASTPENDING;
	thread_unlock(td);
}
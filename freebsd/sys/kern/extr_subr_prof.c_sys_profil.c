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
struct uprof {int pr_scale; int /*<<< orphan*/  pr_size; int /*<<< orphan*/  pr_base; int /*<<< orphan*/  pr_off; } ;
struct thread {struct proc* td_proc; } ;
struct profil_args {int scale; int /*<<< orphan*/  size; int /*<<< orphan*/  samples; int /*<<< orphan*/  offset; } ;
struct proc {TYPE_1__* p_stats; } ;
struct TYPE_2__ {struct uprof p_prof; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_PROFLOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_PROFUNLOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int /*<<< orphan*/  startprofclock (struct proc*) ; 
 int /*<<< orphan*/  stopprofclock (struct proc*) ; 

int
sys_profil(struct thread *td, struct profil_args *uap)
{
	struct uprof *upp;
	struct proc *p;

	if (uap->scale > (1 << 16))
		return (EINVAL);

	p = td->td_proc;
	if (uap->scale == 0) {
		PROC_LOCK(p);
		stopprofclock(p);
		PROC_UNLOCK(p);
		return (0);
	}
	PROC_LOCK(p);
	upp = &td->td_proc->p_stats->p_prof;
	PROC_PROFLOCK(p);
	upp->pr_off = uap->offset;
	upp->pr_scale = uap->scale;
	upp->pr_base = uap->samples;
	upp->pr_size = uap->size;
	PROC_PROFUNLOCK(p);
	startprofclock(p);
	PROC_UNLOCK(p);

	return (0);
}
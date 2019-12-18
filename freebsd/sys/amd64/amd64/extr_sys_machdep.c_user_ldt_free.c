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
struct thread {struct proc* td_proc; } ;
struct proc_ldt {int dummy; } ;
struct mdproc {int /*<<< orphan*/  md_ldt_sd; struct proc_ldt* md_ldt; } ;
struct proc {struct mdproc p_md; } ;

/* Variables and functions */
 int /*<<< orphan*/  GNULL_SEL ; 
 int /*<<< orphan*/  GSEL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEL_KPL ; 
 int /*<<< orphan*/  atomic_thread_fence_rel () ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  critical_enter () ; 
 int /*<<< orphan*/  critical_exit () ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  dt_lock ; 
 int /*<<< orphan*/  lldt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  user_ldt_deref (struct proc_ldt*) ; 

void
user_ldt_free(struct thread *td)
{
	struct proc *p = td->td_proc;
	struct mdproc *mdp = &p->p_md;
	struct proc_ldt *pldt;

	mtx_lock(&dt_lock);
	if ((pldt = mdp->md_ldt) == NULL) {
		mtx_unlock(&dt_lock);
		return;
	}

	critical_enter();
	mdp->md_ldt = NULL;
	atomic_thread_fence_rel();
	bzero(&mdp->md_ldt_sd, sizeof(mdp->md_ldt_sd));
	if (td == curthread)
		lldt(GSEL(GNULL_SEL, SEL_KPL));
	critical_exit();
	user_ldt_deref(pldt);
}
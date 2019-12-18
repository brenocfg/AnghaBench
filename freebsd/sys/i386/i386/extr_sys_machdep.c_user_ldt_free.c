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
struct thread {TYPE_1__* td_proc; } ;
struct proc_ldt {int dummy; } ;
struct mdproc {struct proc_ldt* md_ldt; } ;
struct TYPE_2__ {struct mdproc p_md; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  PCPU_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _default_ldt ; 
 int /*<<< orphan*/  currentldt ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  dt_lock ; 
 int /*<<< orphan*/  lldt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  user_ldt_deref (struct proc_ldt*) ; 

void
user_ldt_free(struct thread *td)
{
	struct mdproc *mdp;
	struct proc_ldt *pldt;

	mtx_assert(&dt_lock, MA_OWNED);
	mdp = &td->td_proc->p_md;
	if ((pldt = mdp->md_ldt) == NULL) {
		mtx_unlock_spin(&dt_lock);
		return;
	}

	if (td == curthread) {
		lldt(_default_ldt);
		PCPU_SET(currentldt, _default_ldt);
	}

	mdp->md_ldt = NULL;
	user_ldt_deref(pldt);
}
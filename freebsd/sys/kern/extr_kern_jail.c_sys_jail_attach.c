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
struct thread {TYPE_1__* td_ucred; } ;
struct prison {scalar_t__ pr_uref; int /*<<< orphan*/  pr_mtx; } ;
struct jail_attach_args {int /*<<< orphan*/  jid; } ;
struct TYPE_2__ {int /*<<< orphan*/  cr_prison; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PRIV_JAIL_ATTACH ; 
 int /*<<< orphan*/  allprison_lock ; 
 int do_jail_attach (struct thread*,struct prison*) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 struct prison* prison_find_child (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int priv_check (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_downgrade (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_sunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 

int
sys_jail_attach(struct thread *td, struct jail_attach_args *uap)
{
	struct prison *pr;
	int error;

	error = priv_check(td, PRIV_JAIL_ATTACH);
	if (error)
		return (error);

	/*
	 * Start with exclusive hold on allprison_lock to ensure that a possible
	 * PR_METHOD_REMOVE call isn't concurrent with jail_set or jail_remove.
	 * But then immediately downgrade it since we don't need to stop
	 * readers.
	 */
	sx_xlock(&allprison_lock);
	sx_downgrade(&allprison_lock);
	pr = prison_find_child(td->td_ucred->cr_prison, uap->jid);
	if (pr == NULL) {
		sx_sunlock(&allprison_lock);
		return (EINVAL);
	}

	/*
	 * Do not allow a process to attach to a prison that is not
	 * considered to be "alive".
	 */
	if (pr->pr_uref == 0) {
		mtx_unlock(&pr->pr_mtx);
		sx_sunlock(&allprison_lock);
		return (EINVAL);
	}

	return (do_jail_attach(td, pr));
}
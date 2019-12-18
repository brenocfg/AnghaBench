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
struct ucred {int dummy; } ;
struct thread {TYPE_2__* td_proc; } ;
struct TYPE_5__ {TYPE_1__* p_vmspace; int /*<<< orphan*/  p_ucred; } ;
struct TYPE_4__ {int /*<<< orphan*/  vm_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  PROC_LOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  crfree (struct ucred*) ; 
 struct ucred* crhold (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mac_proc_vm_revoke_recurse (struct thread*,struct ucred*,int /*<<< orphan*/ *) ; 

void
mac_proc_vm_revoke(struct thread *td)
{
	struct ucred *cred;

	PROC_LOCK(td->td_proc);
	cred = crhold(td->td_proc->p_ucred);
	PROC_UNLOCK(td->td_proc);

	/* XXX freeze all other threads */
	mac_proc_vm_revoke_recurse(td, cred,
	    &td->td_proc->p_vmspace->vm_map);
	/* XXX allow other threads to continue */

	crfree(cred);
}
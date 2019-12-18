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
struct proc {TYPE_2__* p_ucred; int /*<<< orphan*/  p_comm; int /*<<< orphan*/  p_pid; } ;
struct TYPE_4__ {int /*<<< orphan*/  cr_uid; TYPE_1__* cr_prison; } ;
struct TYPE_3__ {int /*<<< orphan*/  pr_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTR3 (int /*<<< orphan*/ ,char*,struct proc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KTR_PROC ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  PROC_LOCK_ASSERT (struct proc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  kern_psignal (struct proc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  proc_wkilled (struct proc*) ; 

void
killproc(struct proc *p, char *why)
{

	PROC_LOCK_ASSERT(p, MA_OWNED);
	CTR3(KTR_PROC, "killproc: proc %p (pid %d, %s)", p, p->p_pid,
	    p->p_comm);
	log(LOG_ERR, "pid %d (%s), jid %d, uid %d, was killed: %s\n",
	    p->p_pid, p->p_comm, p->p_ucred->cr_prison->pr_id,
	    p->p_ucred->cr_uid, why);
	proc_wkilled(p);
	kern_psignal(p, SIGKILL);
}
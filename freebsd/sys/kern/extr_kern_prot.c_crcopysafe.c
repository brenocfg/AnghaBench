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
struct ucred {int cr_agroups; } ;
struct proc {struct ucred* p_ucred; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_LOCK_ASSERT (struct proc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int /*<<< orphan*/  crcopy (struct ucred*,struct ucred*) ; 
 int /*<<< orphan*/  crextend (struct ucred*,int) ; 

struct ucred *
crcopysafe(struct proc *p, struct ucred *cr)
{
	struct ucred *oldcred;
	int groups;

	PROC_LOCK_ASSERT(p, MA_OWNED);

	oldcred = p->p_ucred;
	while (cr->cr_agroups < oldcred->cr_agroups) {
		groups = oldcred->cr_agroups;
		PROC_UNLOCK(p);
		crextend(cr, groups);
		PROC_LOCK(p);
		oldcred = p->p_ucred;
	}
	crcopy(cr, oldcred);

	return (oldcred);
}
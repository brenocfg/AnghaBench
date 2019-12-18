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
struct vnode {int dummy; } ;
struct session {struct vnode* s_ttyvp; int /*<<< orphan*/ * pg_session; int /*<<< orphan*/ * p_pgrp; } ;
struct proc {struct vnode* s_ttyvp; int /*<<< orphan*/ * pg_session; int /*<<< orphan*/ * p_pgrp; } ;
struct pgrp {struct vnode* s_ttyvp; int /*<<< orphan*/ * pg_session; int /*<<< orphan*/ * p_pgrp; } ;
struct kinfo_proc {int /*<<< orphan*/  ki_pid; int /*<<< orphan*/ * ki_paddr; } ;
typedef  int /*<<< orphan*/  sess ;
typedef  int /*<<< orphan*/  proc ;
typedef  int /*<<< orphan*/  pgrp ;
typedef  int /*<<< orphan*/  kvm_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (struct kinfo_proc*) ; 
 int kvm_read_all (int /*<<< orphan*/ *,unsigned long,struct session*,int) ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct vnode *
getctty(kvm_t *kd, struct kinfo_proc *kp)
{
	struct pgrp pgrp;
	struct proc proc;
	struct session sess;
	int error;
                        
	assert(kp);
	error = kvm_read_all(kd, (unsigned long)kp->ki_paddr, &proc,
	    sizeof(proc));
	if (error == 0) {
		warnx("can't read proc struct at %p for pid %d",
		    kp->ki_paddr, kp->ki_pid);
		return (NULL);
	}
	if (proc.p_pgrp == NULL)
		return (NULL);
	error = kvm_read_all(kd, (unsigned long)proc.p_pgrp, &pgrp,
	    sizeof(pgrp));
	if (error == 0) {
		warnx("can't read pgrp struct at %p for pid %d",
		    proc.p_pgrp, kp->ki_pid);
		return (NULL);
	}
	error = kvm_read_all(kd, (unsigned long)pgrp.pg_session, &sess,
	    sizeof(sess));
	if (error == 0) {
		warnx("can't read session struct at %p for pid %d",
		    pgrp.pg_session, kp->ki_pid);
		return (NULL);
	}
	return (sess.s_ttyvp);
}
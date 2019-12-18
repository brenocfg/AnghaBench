#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct thread {int /*<<< orphan*/  td_ucred; } ;
struct nameidata {TYPE_2__* ni_vp; } ;
struct acct_args {int /*<<< orphan*/ * path; } ;
struct TYPE_10__ {TYPE_1__* pl_rlimit; } ;
struct TYPE_9__ {scalar_t__ v_type; } ;
struct TYPE_8__ {int /*<<< orphan*/  rlim_max; int /*<<< orphan*/  rlim_cur; } ;

/* Variables and functions */
 int ACCT_EXITREQ ; 
 int ACCT_RUNNING ; 
 int AUDITVNODE1 ; 
 int EACCES ; 
 int FWRITE ; 
 int /*<<< orphan*/  LOG_NOTICE ; 
 int /*<<< orphan*/  LOOKUP ; 
 int /*<<< orphan*/  NDFREE (struct nameidata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NDF_ONLY_PNBUF ; 
 int /*<<< orphan*/  NDINIT (struct nameidata*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct thread*) ; 
 int NOFOLLOW ; 
 int O_APPEND ; 
 int /*<<< orphan*/  PRIV_ACCT ; 
 int /*<<< orphan*/  RLIM_INFINITY ; 
 int RLIM_NLIMITS ; 
 int /*<<< orphan*/  UIO_USERSPACE ; 
 int /*<<< orphan*/  VOP_UNLOCK (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ VREG ; 
 int acct_configured ; 
 int /*<<< orphan*/  acct_cred ; 
 int acct_disable (struct thread*,int) ; 
 int acct_flags ; 
 TYPE_4__* acct_limit ; 
 int acct_state ; 
 scalar_t__ acct_suspended ; 
 int /*<<< orphan*/  acct_sx ; 
 int /*<<< orphan*/  acct_thread ; 
 TYPE_2__* acct_vp ; 
 int /*<<< orphan*/  crhold (int /*<<< orphan*/ ) ; 
 int kproc_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 TYPE_4__* lim_alloc () ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*) ; 
 int mac_system_check_acct (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int priv_check (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vn_close (TYPE_2__*,int,int /*<<< orphan*/ ,struct thread*) ; 
 int vn_open (struct nameidata*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup (int*) ; 

int
sys_acct(struct thread *td, struct acct_args *uap)
{
	struct nameidata nd;
	int error, flags, i, replacing;

	error = priv_check(td, PRIV_ACCT);
	if (error)
		return (error);

	/*
	 * If accounting is to be started to a file, open that file for
	 * appending and make sure it's a 'normal'.
	 */
	if (uap->path != NULL) {
		NDINIT(&nd, LOOKUP, NOFOLLOW | AUDITVNODE1,
		    UIO_USERSPACE, uap->path, td);
		flags = FWRITE | O_APPEND;
		error = vn_open(&nd, &flags, 0, NULL);
		if (error)
			return (error);
		NDFREE(&nd, NDF_ONLY_PNBUF);
#ifdef MAC
		error = mac_system_check_acct(td->td_ucred, nd.ni_vp);
		if (error) {
			VOP_UNLOCK(nd.ni_vp, 0);
			vn_close(nd.ni_vp, flags, td->td_ucred, td);
			return (error);
		}
#endif
		VOP_UNLOCK(nd.ni_vp, 0);
		if (nd.ni_vp->v_type != VREG) {
			vn_close(nd.ni_vp, flags, td->td_ucred, td);
			return (EACCES);
		}
#ifdef MAC
	} else {
		error = mac_system_check_acct(td->td_ucred, NULL);
		if (error)
			return (error);
#endif
	}

	/*
	 * Disallow concurrent access to the accounting vnode while we swap
	 * it out, in order to prevent access after close.
	 */
	sx_xlock(&acct_sx);

	/*
	 * Don't log spurious disable/enable messages if we are
	 * switching from one accounting file to another due to log
	 * rotation.
	 */
	replacing = (acct_vp != NULL && uap->path != NULL);

	/*
	 * If accounting was previously enabled, kill the old space-watcher,
	 * close the file, and (if no new file was specified, leave).  Reset
	 * the suspended state regardless of whether accounting remains
	 * enabled.
	 */
	acct_suspended = 0;
	if (acct_vp != NULL)
		error = acct_disable(td, !replacing);
	if (uap->path == NULL) {
		if (acct_state & ACCT_RUNNING) {
			acct_state |= ACCT_EXITREQ;
			wakeup(&acct_state);
		}
		sx_xunlock(&acct_sx);
		return (error);
	}

	/*
	 * Create our own plimit object without limits. It will be assigned
	 * to exiting processes.
	 */
	acct_limit = lim_alloc();
	for (i = 0; i < RLIM_NLIMITS; i++)
		acct_limit->pl_rlimit[i].rlim_cur =
		    acct_limit->pl_rlimit[i].rlim_max = RLIM_INFINITY;

	/*
	 * Save the new accounting file vnode, and schedule the new
	 * free space watcher.
	 */
	acct_vp = nd.ni_vp;
	acct_cred = crhold(td->td_ucred);
	acct_flags = flags;
	if (acct_state & ACCT_RUNNING)
		acct_state &= ~ACCT_EXITREQ;
	else {
		/*
		 * Try to start up an accounting kthread.  We may start more
		 * than one, but if so the extras will commit suicide as
		 * soon as they start up.
		 */
		error = kproc_create(acct_thread, NULL, NULL, 0, 0,
		    "accounting");
		if (error) {
			(void) acct_disable(td, 0);
			sx_xunlock(&acct_sx);
			log(LOG_NOTICE, "Unable to start accounting thread\n");
			return (error);
		}
	}
	acct_configured = 1;
	sx_xunlock(&acct_sx);
	if (!replacing)
		log(LOG_NOTICE, "Accounting enabled\n");
	return (error);
}
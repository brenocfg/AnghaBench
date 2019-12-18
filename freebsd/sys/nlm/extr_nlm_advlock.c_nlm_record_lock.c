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
struct vop_advlockasync_args {int a_op; int a_flags; int /*<<< orphan*/ * a_cookiep; int /*<<< orphan*/ * a_task; struct flock* a_fl; int /*<<< orphan*/ * a_id; struct vnode* a_vp; } ;
struct vnode {int /*<<< orphan*/  v_lockf; } ;
struct proc {int dummy; } ;
struct flock {int l_pid; int l_sysid; int /*<<< orphan*/  l_whence; int /*<<< orphan*/  l_type; int /*<<< orphan*/  l_len; int /*<<< orphan*/  l_start; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int EDEADLK ; 
 int EINTR ; 
 int ENOENT ; 
 int F_NOINTR ; 
 int F_REMOTE ; 
 int F_WAIT ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int NLM_SYSID_CLIENT ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int /*<<< orphan*/  SIGDEFERSTOP_OFF ; 
 struct proc* curproc ; 
 int lf_advlockasync (struct vop_advlockasync_args*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pause (char*,int) ; 
 int /*<<< orphan*/  sigallowstop (int) ; 
 int sigdeferstop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_suspend_check (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nlm_record_lock(struct vnode *vp, int op, struct flock *fl,
    int svid, int sysid, off_t size)
{
	struct vop_advlockasync_args a;
	struct flock newfl;
	struct proc *p;
	int error, stops_deferred;

	a.a_vp = vp;
	a.a_id = NULL;
	a.a_op = op;
	a.a_fl = &newfl;
	a.a_flags = F_REMOTE|F_WAIT|F_NOINTR;
	a.a_task = NULL;
	a.a_cookiep = NULL;
	newfl.l_start = fl->l_start;
	newfl.l_len = fl->l_len;
	newfl.l_type = fl->l_type;
	newfl.l_whence = fl->l_whence;
	newfl.l_pid = svid;
	newfl.l_sysid = NLM_SYSID_CLIENT | sysid;

	for (;;) {
		error = lf_advlockasync(&a, &vp->v_lockf, size);
		if (error == EDEADLK) {
			/*
			 * Locks are associated with the processes and
			 * not with threads.  Suppose we have two
			 * threads A1 A2 in one process, A1 locked
			 * file f1, A2 is locking file f2, and A1 is
			 * unlocking f1. Then remote server may
			 * already unlocked f1, while local still not
			 * yet scheduled A1 to make the call to local
			 * advlock manager. The process B owns lock on
			 * f2 and issued the lock on f1.  Remote would
			 * grant B the request on f1, but local would
			 * return EDEADLK.
			*/
			pause("nlmdlk", 1);
			p = curproc;
			stops_deferred = sigdeferstop(SIGDEFERSTOP_OFF);
			PROC_LOCK(p);
			thread_suspend_check(0);
			PROC_UNLOCK(p);
			sigallowstop(stops_deferred);
		} else if (error == EINTR) {
			/*
			 * lf_purgelocks() might wake up the lock
			 * waiter and removed our lock graph edges.
			 * There is no sense in re-trying recording
			 * the lock to the local manager after
			 * reclaim.
			 */
			error = 0;
			break;
		} else
			break;
	}
	KASSERT(error == 0 || error == ENOENT,
	    ("Failed to register NFS lock locally - error=%d", error));
}
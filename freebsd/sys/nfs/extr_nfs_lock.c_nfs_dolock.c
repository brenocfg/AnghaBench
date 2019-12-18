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
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct vop_advlock_args {int a_flags; scalar_t__ a_op; struct flock* a_fl; struct vnode* a_vp; } ;
struct vnode {int /*<<< orphan*/  v_mount; } ;
struct timeval {int dummy; } ;
struct thread {int /*<<< orphan*/  td_ucred; struct proc* td_proc; } ;
struct proc {TYPE_4__* p_nlminfo; TYPE_1__* p_stats; int /*<<< orphan*/  p_pid; } ;
struct nlminfo {int dummy; } ;
struct nfsmount {int /*<<< orphan*/  (* nm_getinfo ) (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
struct flock {scalar_t__ l_whence; scalar_t__ l_start; int l_len; scalar_t__ l_type; int /*<<< orphan*/  l_pid; scalar_t__ l_sysid; } ;
struct TYPE_10__ {int retcode; int /*<<< orphan*/  getlk_pid; scalar_t__ set_getlk_pid; scalar_t__ msg_seq; int /*<<< orphan*/  pid_start; } ;
struct TYPE_8__ {scalar_t__ msg_seq; int /*<<< orphan*/  pid_start; int /*<<< orphan*/  pid; } ;
struct TYPE_9__ {int lm_wait; int lm_getlk; int /*<<< orphan*/  lm_cred; struct flock lm_fl; TYPE_2__ lm_msg_ident; int /*<<< orphan*/  lm_version; int /*<<< orphan*/  lm_nfsv3; int /*<<< orphan*/  lm_addr; int /*<<< orphan*/  lm_fh_len; int /*<<< orphan*/  lm_fh; } ;
struct TYPE_7__ {int /*<<< orphan*/  p_start; } ;
typedef  TYPE_3__ LOCKD_MSG ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_VOP_LOCKED (struct vnode*,char*) ; 
 int EINVAL ; 
 int EOVERFLOW ; 
 int EWOULDBLOCK ; 
 scalar_t__ F_GETLK ; 
 scalar_t__ F_UNLCK ; 
 int F_WAIT ; 
 int /*<<< orphan*/  Giant ; 
 int /*<<< orphan*/  LOCKD_MSG_VERSION ; 
 int /*<<< orphan*/  M_NLMINFO ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int OFF_MAX ; 
 int /*<<< orphan*/  PUSER ; 
 scalar_t__ SEEK_CUR ; 
 scalar_t__ SEEK_END ; 
 scalar_t__ SEEK_SET ; 
 struct nfsmount* VFSTONFS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cru2x (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  getboottime (struct timeval*) ; 
 int hz ; 
 TYPE_4__* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int nfslock_send (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timevaladd (int /*<<< orphan*/ *,struct timeval*) ; 
 int tsleep (TYPE_4__*,int /*<<< orphan*/ ,char*,int) ; 

int
nfs_dolock(struct vop_advlock_args *ap)
{
	LOCKD_MSG msg;
	struct thread *td;
	struct vnode *vp;
	int error;
	struct flock *fl;
	struct proc *p;
	struct nfsmount *nmp;
	struct timeval boottime;

	td = curthread;
	p = td->td_proc;

	vp = ap->a_vp;
	fl = ap->a_fl;
	nmp = VFSTONFS(vp->v_mount);

	ASSERT_VOP_LOCKED(vp, "nfs_dolock");

	nmp->nm_getinfo(vp, msg.lm_fh, &msg.lm_fh_len, &msg.lm_addr,
	    &msg.lm_nfsv3, NULL, NULL);
	VOP_UNLOCK(vp, 0);

	/*
	 * the NLM protocol doesn't allow the server to return an error
	 * on ranges, so we do it.
	 */
	if (fl->l_whence != SEEK_END) {
		if ((fl->l_whence != SEEK_CUR && fl->l_whence != SEEK_SET) ||
		    fl->l_start < 0 ||
		    (fl->l_len < 0 &&
		     (fl->l_start == 0 || fl->l_start + fl->l_len < 0)))
			return (EINVAL);
		if (fl->l_len > 0 &&
			 (fl->l_len - 1 > OFF_MAX - fl->l_start))
			return (EOVERFLOW);
	}

	/*
	 * Fill in the information structure.
	 */
	msg.lm_version = LOCKD_MSG_VERSION;
	msg.lm_msg_ident.pid = p->p_pid;

	mtx_lock(&Giant);
	/*
	 * if there is no nfsowner table yet, allocate one.
	 */
	if (p->p_nlminfo == NULL) {
		p->p_nlminfo = malloc(sizeof(struct nlminfo),
		    M_NLMINFO, M_WAITOK | M_ZERO);
		p->p_nlminfo->pid_start = p->p_stats->p_start;
		getboottime(&boottime);
		timevaladd(&p->p_nlminfo->pid_start, &boottime);
	}
	msg.lm_msg_ident.pid_start = p->p_nlminfo->pid_start;
	msg.lm_msg_ident.msg_seq = ++(p->p_nlminfo->msg_seq);

	msg.lm_fl = *fl;
	msg.lm_wait = ap->a_flags & F_WAIT;
	msg.lm_getlk = ap->a_op == F_GETLK;
	cru2x(td->td_ucred, &msg.lm_cred);

	for (;;) {
		error = nfslock_send(&msg);
		if (error)
			goto out;

		/* Unlocks succeed immediately.  */
		if (fl->l_type == F_UNLCK)
			goto out;

		/*
		 * Retry after 20 seconds if we haven't gotten a response yet.
		 * This number was picked out of thin air... but is longer
		 * then even a reasonably loaded system should take (at least
		 * on a local network).  XXX Probably should use a back-off
		 * scheme.
		 *
		 * XXX: No PCATCH here since we currently have no useful
		 * way to signal to the userland rpc.lockd that the request
		 * has been aborted.  Once the rpc.lockd implementation
		 * can handle aborts, and we report them properly,
		 * PCATCH can be put back.  In the mean time, if we did
		 * permit aborting, the lock attempt would "get lost"
		 * and the lock would get stuck in the locked state.
		 */
		error = tsleep(p->p_nlminfo, PUSER, "lockd", 20*hz);
		if (error != 0) {
			if (error == EWOULDBLOCK) {
				/*
				 * We timed out, so we rewrite the request
				 * to the fifo.
				 */
				continue;
			}

			break;
		}

		if (msg.lm_getlk && p->p_nlminfo->retcode == 0) {
			if (p->p_nlminfo->set_getlk_pid) {
				fl->l_sysid = 0; /* XXX */
				fl->l_pid = p->p_nlminfo->getlk_pid;
			} else {
				fl->l_type = F_UNLCK;
			}
		}
		error = p->p_nlminfo->retcode;
		break;
	}
 out:
	mtx_unlock(&Giant);
	return (error);
}
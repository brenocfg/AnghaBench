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
struct vnode {scalar_t__ v_type; int v_vflag; } ;
struct vattr {int va_nlink; scalar_t__ va_uid; int /*<<< orphan*/  va_flags; scalar_t__ va_size; } ;
struct ucred {scalar_t__ cr_uid; } ;
struct thread {struct ucred* td_ucred; struct proc* td_proc; } ;
struct sbuf {int dummy; } ;
struct proc {int p_flag; int p_flag2; int /*<<< orphan*/  p_textvp; TYPE_1__* p_sysent; int /*<<< orphan*/  p_acflag; int /*<<< orphan*/  p_sig; int /*<<< orphan*/  p_pid; int /*<<< orphan*/  p_comm; struct thread* p_singlethread; } ;
struct flock {int /*<<< orphan*/  l_type; scalar_t__ l_len; scalar_t__ l_start; int /*<<< orphan*/  l_whence; } ;
typedef  scalar_t__ off_t ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_2__ {int (* sv_coredump ) (struct thread*,struct vnode*,scalar_t__,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ACORE ; 
 int EFAULT ; 
 int EFBIG ; 
 int ENOSYS ; 
 int /*<<< orphan*/  FWRITE ; 
 int /*<<< orphan*/  F_FLOCK ; 
 int /*<<< orphan*/  F_SETLK ; 
 int /*<<< orphan*/  F_UNLCK ; 
 int /*<<< orphan*/  F_WRLCK ; 
 int LK_EXCLUSIVE ; 
 int LK_RETRY ; 
 int /*<<< orphan*/  MAXPATHLEN ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  OFF_MAX ; 
 int P2_NOTRACE ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_LOCK_ASSERT (struct proc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int P_HADTHREADS ; 
 int P_SUGID ; 
 int /*<<< orphan*/  RACCT_CORE ; 
 int /*<<< orphan*/  RLIMIT_CORE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  S_CORE ; 
 int /*<<< orphan*/  UF_NODUMP ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int /*<<< orphan*/  VATTR_NULL (struct vattr*) ; 
 scalar_t__ VOP_ADVLOCK (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct flock*,int /*<<< orphan*/ ) ; 
 scalar_t__ VOP_GETATTR (struct vnode*,struct vattr*,struct ucred*) ; 
 int /*<<< orphan*/  VOP_SETATTR (struct vnode*,struct vattr*,struct ucred*) ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 scalar_t__ VREG ; 
 int VV_SYSTEM ; 
 int /*<<< orphan*/  _STOPEVENT (struct proc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  audit_proc_coredump (struct thread*,char*,int) ; 
 int /*<<< orphan*/  compress_user_cores ; 
 scalar_t__ coredump_devctl ; 
 int corefile_open (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vnode**,char**) ; 
 int /*<<< orphan*/  devctl_notify (char*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devctl_safe_quote_sb (struct sbuf*,char*) ; 
 int /*<<< orphan*/  do_coredump ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ kern___getcwd (struct thread*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ lim_cur (struct thread*,int /*<<< orphan*/ ) ; 
 char* malloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ racct_get_available (struct proc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbuf_data (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_delete (struct sbuf*) ; 
 scalar_t__ sbuf_finish (struct sbuf*) ; 
 struct sbuf* sbuf_new_auto () ; 
 int /*<<< orphan*/  sbuf_printf (struct sbuf*,char*) ; 
 int /*<<< orphan*/  sbuf_putc (struct sbuf*,char) ; 
 scalar_t__ set_core_nodump_flag ; 
 int stub1 (struct thread*,struct vnode*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sugid_coredump ; 
 int vn_close (struct vnode*,int /*<<< orphan*/ ,struct ucred*,struct thread*) ; 
 scalar_t__ vn_fullpath_global (struct thread*,int /*<<< orphan*/ ,char**,char**) ; 
 int /*<<< orphan*/  vn_lock (struct vnode*,int) ; 
 int /*<<< orphan*/  vn_rangelock_unlock (struct vnode*,void*) ; 
 void* vn_rangelock_wlock (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
coredump(struct thread *td)
{
	struct proc *p = td->td_proc;
	struct ucred *cred = td->td_ucred;
	struct vnode *vp;
	struct flock lf;
	struct vattr vattr;
	int error, error1, locked;
	char *name;			/* name of corefile */
	void *rl_cookie;
	off_t limit;
	char *fullpath, *freepath = NULL;
	struct sbuf *sb;

	PROC_LOCK_ASSERT(p, MA_OWNED);
	MPASS((p->p_flag & P_HADTHREADS) == 0 || p->p_singlethread == td);
	_STOPEVENT(p, S_CORE, 0);

	if (!do_coredump || (!sugid_coredump && (p->p_flag & P_SUGID) != 0) ||
	    (p->p_flag2 & P2_NOTRACE) != 0) {
		PROC_UNLOCK(p);
		return (EFAULT);
	}

	/*
	 * Note that the bulk of limit checking is done after
	 * the corefile is created.  The exception is if the limit
	 * for corefiles is 0, in which case we don't bother
	 * creating the corefile at all.  This layout means that
	 * a corefile is truncated instead of not being created,
	 * if it is larger than the limit.
	 */
	limit = (off_t)lim_cur(td, RLIMIT_CORE);
	if (limit == 0 || racct_get_available(p, RACCT_CORE) == 0) {
		PROC_UNLOCK(p);
		return (EFBIG);
	}
	PROC_UNLOCK(p);

	error = corefile_open(p->p_comm, cred->cr_uid, p->p_pid, td,
	    compress_user_cores, p->p_sig, &vp, &name);
	if (error != 0)
		return (error);

	/*
	 * Don't dump to non-regular files or files with links.
	 * Do not dump into system files. Effective user must own the corefile.
	 */
	if (vp->v_type != VREG || VOP_GETATTR(vp, &vattr, cred) != 0 ||
	    vattr.va_nlink != 1 || (vp->v_vflag & VV_SYSTEM) != 0 ||
	    vattr.va_uid != cred->cr_uid) {
		VOP_UNLOCK(vp, 0);
		error = EFAULT;
		goto out;
	}

	VOP_UNLOCK(vp, 0);

	/* Postpone other writers, including core dumps of other processes. */
	rl_cookie = vn_rangelock_wlock(vp, 0, OFF_MAX);

	lf.l_whence = SEEK_SET;
	lf.l_start = 0;
	lf.l_len = 0;
	lf.l_type = F_WRLCK;
	locked = (VOP_ADVLOCK(vp, (caddr_t)p, F_SETLK, &lf, F_FLOCK) == 0);

	VATTR_NULL(&vattr);
	vattr.va_size = 0;
	if (set_core_nodump_flag)
		vattr.va_flags = UF_NODUMP;
	vn_lock(vp, LK_EXCLUSIVE | LK_RETRY);
	VOP_SETATTR(vp, &vattr, cred);
	VOP_UNLOCK(vp, 0);
	PROC_LOCK(p);
	p->p_acflag |= ACORE;
	PROC_UNLOCK(p);

	if (p->p_sysent->sv_coredump != NULL) {
		error = p->p_sysent->sv_coredump(td, vp, limit, 0);
	} else {
		error = ENOSYS;
	}

	if (locked) {
		lf.l_type = F_UNLCK;
		VOP_ADVLOCK(vp, (caddr_t)p, F_UNLCK, &lf, F_FLOCK);
	}
	vn_rangelock_unlock(vp, rl_cookie);

	/*
	 * Notify the userland helper that a process triggered a core dump.
	 * This allows the helper to run an automated debugging session.
	 */
	if (error != 0 || coredump_devctl == 0)
		goto out;
	sb = sbuf_new_auto();
	if (vn_fullpath_global(td, p->p_textvp, &fullpath, &freepath) != 0)
		goto out2;
	sbuf_printf(sb, "comm=\"");
	devctl_safe_quote_sb(sb, fullpath);
	free(freepath, M_TEMP);
	sbuf_printf(sb, "\" core=\"");

	/*
	 * We can't lookup core file vp directly. When we're replacing a core, and
	 * other random times, we flush the name cache, so it will fail. Instead,
	 * if the path of the core is relative, add the current dir in front if it.
	 */
	if (name[0] != '/') {
		fullpath = malloc(MAXPATHLEN, M_TEMP, M_WAITOK);
		if (kern___getcwd(td, fullpath, UIO_SYSSPACE, MAXPATHLEN, MAXPATHLEN) != 0) {
			free(fullpath, M_TEMP);
			goto out2;
		}
		devctl_safe_quote_sb(sb, fullpath);
		free(fullpath, M_TEMP);
		sbuf_putc(sb, '/');
	}
	devctl_safe_quote_sb(sb, name);
	sbuf_printf(sb, "\"");
	if (sbuf_finish(sb) == 0)
		devctl_notify("kernel", "signal", "coredump", sbuf_data(sb));
out2:
	sbuf_delete(sb);
out:
	error1 = vn_close(vp, FWRITE, cred, td);
	if (error == 0)
		error = error1;
#ifdef AUDIT
	audit_proc_coredump(td, name, error);
#endif
	free(name, M_TEMP);
	return (error);
}
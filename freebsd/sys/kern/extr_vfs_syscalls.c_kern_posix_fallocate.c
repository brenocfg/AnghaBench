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
struct vnode {scalar_t__ v_type; } ;
struct thread {int /*<<< orphan*/  td_ucred; int /*<<< orphan*/  td_proc; } ;
struct mount {int dummy; } ;
struct file {int f_flag; scalar_t__ f_type; int /*<<< orphan*/  f_cred; struct vnode* f_vnode; TYPE_1__* f_ops; } ;
typedef  scalar_t__ off_t ;
struct TYPE_2__ {int fo_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_ARG_FD (int) ; 
 int /*<<< orphan*/  AUDIT_ARG_FILE (int /*<<< orphan*/ ,struct file*) ; 
 int /*<<< orphan*/  AUDIT_ARG_VNODE1 (struct vnode*) ; 
 int DFLAG_SEEKABLE ; 
 scalar_t__ DTYPE_VNODE ; 
 int EBADF ; 
 int EFBIG ; 
 int EINVAL ; 
 int ENODEV ; 
 int ESPIPE ; 
 int FWRITE ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  LK_EXCLUSIVE ; 
 scalar_t__ OFF_MAX ; 
 int PCATCH ; 
 int VOP_ALLOCATE (struct vnode*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 scalar_t__ VREG ; 
 int V_WAIT ; 
 int /*<<< orphan*/  bwillwrite () ; 
 int /*<<< orphan*/  cap_pwrite_rights ; 
 int /*<<< orphan*/  fdrop (struct file*,struct thread*) ; 
 int fget (struct thread*,int,int /*<<< orphan*/ *,struct file**) ; 
 int mac_vnode_check_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vnode*) ; 
 int /*<<< orphan*/  maybe_yield () ; 
 int /*<<< orphan*/  panic (char*,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  vn_finished_write (struct mount*) ; 
 int vn_lock (struct vnode*,int /*<<< orphan*/ ) ; 
 int vn_start_write (struct vnode*,struct mount**,int) ; 

int
kern_posix_fallocate(struct thread *td, int fd, off_t offset, off_t len)
{
	struct file *fp;
	struct mount *mp;
	struct vnode *vp;
	off_t olen, ooffset;
	int error;
#ifdef AUDIT
	int audited_vnode1 = 0;
#endif

	AUDIT_ARG_FD(fd);
	if (offset < 0 || len <= 0)
		return (EINVAL);
	/* Check for wrap. */
	if (offset > OFF_MAX - len)
		return (EFBIG);
	AUDIT_ARG_FD(fd);
	error = fget(td, fd, &cap_pwrite_rights, &fp);
	if (error != 0)
		return (error);
	AUDIT_ARG_FILE(td->td_proc, fp);
	if ((fp->f_ops->fo_flags & DFLAG_SEEKABLE) == 0) {
		error = ESPIPE;
		goto out;
	}
	if ((fp->f_flag & FWRITE) == 0) {
		error = EBADF;
		goto out;
	}
	if (fp->f_type != DTYPE_VNODE) {
		error = ENODEV;
		goto out;
	}
	vp = fp->f_vnode;
	if (vp->v_type != VREG) {
		error = ENODEV;
		goto out;
	}

	/* Allocating blocks may take a long time, so iterate. */
	for (;;) {
		olen = len;
		ooffset = offset;

		bwillwrite();
		mp = NULL;
		error = vn_start_write(vp, &mp, V_WAIT | PCATCH);
		if (error != 0)
			break;
		error = vn_lock(vp, LK_EXCLUSIVE);
		if (error != 0) {
			vn_finished_write(mp);
			break;
		}
#ifdef AUDIT
		if (!audited_vnode1) {
			AUDIT_ARG_VNODE1(vp);
			audited_vnode1 = 1;
		}
#endif
#ifdef MAC
		error = mac_vnode_check_write(td->td_ucred, fp->f_cred, vp);
		if (error == 0)
#endif
			error = VOP_ALLOCATE(vp, &offset, &len);
		VOP_UNLOCK(vp, 0);
		vn_finished_write(mp);

		if (olen + ooffset != offset + len) {
			panic("offset + len changed from %jx/%jx to %jx/%jx",
			    ooffset, olen, offset, len);
		}
		if (error != 0 || len == 0)
			break;
		KASSERT(olen > len, ("Iteration did not make progress?"));
		maybe_yield();
	}
 out:
	fdrop(fp, td);
	return (error);
}
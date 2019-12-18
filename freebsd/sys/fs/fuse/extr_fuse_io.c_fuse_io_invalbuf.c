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
struct TYPE_4__ {int /*<<< orphan*/ * bo_object; } ;
struct vnode {int v_iflag; TYPE_2__ v_bufobj; TYPE_1__* v_mount; } ;
struct thread {int /*<<< orphan*/  td_siglist; struct proc* td_proc; } ;
struct proc {int /*<<< orphan*/  p_siglist; } ;
struct fuse_vnode_data {int flag; } ;
struct TYPE_3__ {int mnt_kern_flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_VOP_ELOCKED (struct vnode*,char*) ; 
 int EINTR ; 
 int EIO ; 
 int ERESTART ; 
 int FN_FLUSHINPROG ; 
 int FN_FLUSHWANT ; 
 int MNTK_UNMOUNTF ; 
 int /*<<< orphan*/  OBJPC_SYNC ; 
 int /*<<< orphan*/  PCATCH ; 
 scalar_t__ PRIBIO ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 scalar_t__ SIGNOTEMPTY (int /*<<< orphan*/ ) ; 
 int VI_DOOMED ; 
 int /*<<< orphan*/  VM_OBJECT_WLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VM_OBJECT_WUNLOCK (int /*<<< orphan*/ *) ; 
 struct fuse_vnode_data* VTOFUD (struct vnode*) ; 
 int /*<<< orphan*/  V_SAVE ; 
 int hz ; 
 int /*<<< orphan*/  tsleep (int*,scalar_t__,char*,int) ; 
 int vinvalbuf (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_object_page_clean (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup (int*) ; 

int
fuse_io_invalbuf(struct vnode *vp, struct thread *td)
{
	struct fuse_vnode_data *fvdat = VTOFUD(vp);
	int error = 0;

	if (vp->v_iflag & VI_DOOMED)
		return 0;

	ASSERT_VOP_ELOCKED(vp, "fuse_io_invalbuf");

	while (fvdat->flag & FN_FLUSHINPROG) {
		struct proc *p = td->td_proc;

		if (vp->v_mount->mnt_kern_flag & MNTK_UNMOUNTF)
			return EIO;
		fvdat->flag |= FN_FLUSHWANT;
		tsleep(&fvdat->flag, PRIBIO + 2, "fusevinv", 2 * hz);
		error = 0;
		if (p != NULL) {
			PROC_LOCK(p);
			if (SIGNOTEMPTY(p->p_siglist) ||
			    SIGNOTEMPTY(td->td_siglist))
				error = EINTR;
			PROC_UNLOCK(p);
		}
		if (error == EINTR)
			return EINTR;
	}
	fvdat->flag |= FN_FLUSHINPROG;

	if (vp->v_bufobj.bo_object != NULL) {
		VM_OBJECT_WLOCK(vp->v_bufobj.bo_object);
		vm_object_page_clean(vp->v_bufobj.bo_object, 0, 0, OBJPC_SYNC);
		VM_OBJECT_WUNLOCK(vp->v_bufobj.bo_object);
	}
	error = vinvalbuf(vp, V_SAVE, PCATCH, 0);
	while (error) {
		if (error == ERESTART || error == EINTR) {
			fvdat->flag &= ~FN_FLUSHINPROG;
			if (fvdat->flag & FN_FLUSHWANT) {
				fvdat->flag &= ~FN_FLUSHWANT;
				wakeup(&fvdat->flag);
			}
			return EINTR;
		}
		error = vinvalbuf(vp, V_SAVE, PCATCH, 0);
	}
	fvdat->flag &= ~FN_FLUSHINPROG;
	if (fvdat->flag & FN_FLUSHWANT) {
		fvdat->flag &= ~FN_FLUSHWANT;
		wakeup(&fvdat->flag);
	}
	return (error);
}
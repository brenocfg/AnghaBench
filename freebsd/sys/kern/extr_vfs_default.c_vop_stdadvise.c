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
struct vop_advise_args {int a_advice; int /*<<< orphan*/  a_end; int /*<<< orphan*/  a_start; struct vnode* a_vp; } ;
struct bufobj {int bo_bsize; int /*<<< orphan*/  bo_dirty; int /*<<< orphan*/  bo_clean; } ;
struct vnode {int v_iflag; struct bufobj v_bufobj; int /*<<< orphan*/ * v_object; } ;
typedef  int off_t ;
typedef  int daddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BO_RLOCK (struct bufobj*) ; 
 int /*<<< orphan*/  BO_RUNLOCK (struct bufobj*) ; 
 int EINVAL ; 
 int LK_EXCLUSIVE ; 
 int LK_RETRY ; 
 int /*<<< orphan*/  OFF_TO_IDX (int) ; 
#define  POSIX_FADV_DONTNEED 129 
#define  POSIX_FADV_WILLNEED 128 
 int VI_DOOMED ; 
 int /*<<< orphan*/  VM_OBJECT_RLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VM_OBJECT_RUNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 int bnoreuselist (int /*<<< orphan*/ *,struct bufobj*,int,int) ; 
 int round_page (int) ; 
 int rounddown (int /*<<< orphan*/ ,int) ; 
 int roundup (int /*<<< orphan*/ ,int) ; 
 int trunc_page (int) ; 
 int /*<<< orphan*/  vm_object_page_noreuse (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vn_lock (struct vnode*,int) ; 

int
vop_stdadvise(struct vop_advise_args *ap)
{
	struct vnode *vp;
	struct bufobj *bo;
	daddr_t startn, endn;
	off_t bstart, bend, start, end;
	int bsize, error;

	vp = ap->a_vp;
	switch (ap->a_advice) {
	case POSIX_FADV_WILLNEED:
		/*
		 * Do nothing for now.  Filesystems should provide a
		 * custom method which starts an asynchronous read of
		 * the requested region.
		 */
		error = 0;
		break;
	case POSIX_FADV_DONTNEED:
		error = 0;
		vn_lock(vp, LK_EXCLUSIVE | LK_RETRY);
		if (vp->v_iflag & VI_DOOMED) {
			VOP_UNLOCK(vp, 0);
			break;
		}

		/*
		 * Round to block boundaries (and later possibly further to
		 * page boundaries).  Applications cannot reasonably be aware  
		 * of the boundaries, and the rounding must be to expand at
		 * both extremities to cover enough.  It still doesn't cover
		 * read-ahead.  For partial blocks, this gives unnecessary
		 * discarding of buffers but is efficient enough since the
		 * pages usually remain in VMIO for some time.
		 */
		bsize = vp->v_bufobj.bo_bsize;
		bstart = rounddown(ap->a_start, bsize);
		bend = roundup(ap->a_end, bsize);

		/*
		 * Deactivate pages in the specified range from the backing VM
		 * object.  Pages that are resident in the buffer cache will
		 * remain wired until their corresponding buffers are released
		 * below.
		 */
		if (vp->v_object != NULL) {
			start = trunc_page(bstart);
			end = round_page(bend);
			VM_OBJECT_RLOCK(vp->v_object);
			vm_object_page_noreuse(vp->v_object, OFF_TO_IDX(start),
			    OFF_TO_IDX(end));
			VM_OBJECT_RUNLOCK(vp->v_object);
		}

		bo = &vp->v_bufobj;
		BO_RLOCK(bo);
		startn = bstart / bsize;
		endn = bend / bsize;
		error = bnoreuselist(&bo->bo_clean, bo, startn, endn);
		if (error == 0)
			error = bnoreuselist(&bo->bo_dirty, bo, startn, endn);
		BO_RUNLOCK(bo);
		VOP_UNLOCK(vp, 0);
		break;
	default:
		error = EINVAL;
		break;
	}
	return (error);
}
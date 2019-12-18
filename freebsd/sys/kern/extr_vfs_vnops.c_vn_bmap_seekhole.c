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
typedef  int uint64_t ;
typedef  scalar_t__ u_long ;
struct vnode {scalar_t__ v_type; TYPE_2__* v_mount; } ;
struct vattr {int va_size; } ;
struct ucred {int dummy; } ;
typedef  int off_t ;
typedef  int daddr_t ;
struct TYPE_3__ {int f_iosize; } ;
struct TYPE_4__ {TYPE_1__ mnt_stat; } ;

/* Variables and functions */
 int EBADF ; 
 int ENOTTY ; 
 int ENXIO ; 
 int EOPNOTSUPP ; 
 scalar_t__ FIOSEEKDATA ; 
 scalar_t__ FIOSEEKHOLE ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  LK_SHARED ; 
 int VOP_BMAP (struct vnode*,int,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int VOP_GETATTR (struct vnode*,struct vattr*,struct ucred*) ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 scalar_t__ VREG ; 
 scalar_t__ vn_lock (struct vnode*,int /*<<< orphan*/ ) ; 

int
vn_bmap_seekhole(struct vnode *vp, u_long cmd, off_t *off, struct ucred *cred)
{
	struct vattr va;
	daddr_t bn, bnp;
	uint64_t bsize;
	off_t noff;
	int error;

	KASSERT(cmd == FIOSEEKHOLE || cmd == FIOSEEKDATA,
	    ("Wrong command %lu", cmd));

	if (vn_lock(vp, LK_SHARED) != 0)
		return (EBADF);
	if (vp->v_type != VREG) {
		error = ENOTTY;
		goto unlock;
	}
	error = VOP_GETATTR(vp, &va, cred);
	if (error != 0)
		goto unlock;
	noff = *off;
	if (noff >= va.va_size) {
		error = ENXIO;
		goto unlock;
	}
	bsize = vp->v_mount->mnt_stat.f_iosize;
	for (bn = noff / bsize; noff < va.va_size; bn++, noff += bsize -
	    noff % bsize) {
		error = VOP_BMAP(vp, bn, NULL, &bnp, NULL, NULL);
		if (error == EOPNOTSUPP) {
			error = ENOTTY;
			goto unlock;
		}
		if ((bnp == -1 && cmd == FIOSEEKHOLE) ||
		    (bnp != -1 && cmd == FIOSEEKDATA)) {
			noff = bn * bsize;
			if (noff < *off)
				noff = *off;
			goto unlock;
		}
	}
	if (noff > va.va_size)
		noff = va.va_size;
	/* noff == va.va_size. There is an implicit hole at the end of file. */
	if (cmd == FIOSEEKDATA)
		error = ENXIO;
unlock:
	VOP_UNLOCK(vp, 0);
	if (error == 0)
		*off = noff;
	return (error);
}
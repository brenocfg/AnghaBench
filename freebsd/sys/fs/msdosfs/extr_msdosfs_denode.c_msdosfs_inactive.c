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
typedef  int /*<<< orphan*/  u_long ;
struct vop_inactive_args {struct vnode* a_vp; } ;
struct vnode {TYPE_1__* v_mount; } ;
struct denode {int* de_Name; scalar_t__ de_refcnt; int /*<<< orphan*/  de_flag; } ;
struct TYPE_2__ {int mnt_flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  DE_UPDATE ; 
 int MNT_RDONLY ; 
 int /*<<< orphan*/  NOCRED ; 
 scalar_t__ SLOT_DELETED ; 
 scalar_t__ SLOT_EMPTY ; 
 struct denode* VTODE (struct vnode*) ; 
 int detrunc (struct denode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  deupdat (struct denode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  vrecycle (struct vnode*) ; 
 int vrefcnt (struct vnode*) ; 

int
msdosfs_inactive(struct vop_inactive_args *ap)
{
	struct vnode *vp = ap->a_vp;
	struct denode *dep = VTODE(vp);
	int error = 0;

#ifdef MSDOSFS_DEBUG
	printf("msdosfs_inactive(): dep %p, de_Name[0] %x\n", dep, dep->de_Name[0]);
#endif

	/*
	 * Ignore denodes related to stale file handles.
	 */
	if (dep->de_Name[0] == SLOT_DELETED || dep->de_Name[0] == SLOT_EMPTY)
		goto out;

	/*
	 * If the file has been deleted and it is on a read/write
	 * filesystem, then truncate the file, and mark the directory slot
	 * as empty.  (This may not be necessary for the dos filesystem.)
	 */
#ifdef MSDOSFS_DEBUG
	printf("msdosfs_inactive(): dep %p, refcnt %ld, mntflag %llx, MNT_RDONLY %llx\n",
	    dep, dep->de_refcnt, (unsigned long long)vp->v_mount->mnt_flag,
	    (unsigned long long)MNT_RDONLY);
#endif
	if (dep->de_refcnt <= 0 && (vp->v_mount->mnt_flag & MNT_RDONLY) == 0) {
		error = detrunc(dep, (u_long) 0, 0, NOCRED);
		dep->de_flag |= DE_UPDATE;
		dep->de_Name[0] = SLOT_DELETED;
	}
	deupdat(dep, 0);

out:
	/*
	 * If we are done with the denode, reclaim it
	 * so that it can be reused immediately.
	 */
#ifdef MSDOSFS_DEBUG
	printf("msdosfs_inactive(): v_usecount %d, de_Name[0] %x\n",
	       vrefcnt(vp), dep->de_Name[0]);
#endif
	if (dep->de_Name[0] == SLOT_DELETED || dep->de_Name[0] == SLOT_EMPTY)
		vrecycle(vp);
	return (error);
}
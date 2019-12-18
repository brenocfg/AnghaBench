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
struct vnode {int dummy; } ;
struct faultstate {struct vnode* vp; TYPE_1__* object; } ;
struct TYPE_2__ {scalar_t__ type; struct vnode* handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_VOP_LOCKED (struct vnode*,char*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int KERN_RESOURCE_SHORTAGE ; 
 int KERN_SUCCESS ; 
 int LK_CANRECURSE ; 
 int LK_EXCLUSIVE ; 
 int LK_NOWAIT ; 
 int LK_RETRY ; 
 int LK_SHARED ; 
 scalar_t__ OBJT_VNODE ; 
 int VOP_ISLOCKED (struct vnode*) ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  release_page (struct faultstate*) ; 
 int /*<<< orphan*/  unlock_and_deallocate (struct faultstate*) ; 
 int /*<<< orphan*/  unlock_vp (struct faultstate*) ; 
 int /*<<< orphan*/  vdrop (struct vnode*) ; 
 int vget (struct vnode*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vhold (struct vnode*) ; 

__attribute__((used)) static int
vm_fault_lock_vnode(struct faultstate *fs)
{
	struct vnode *vp;
	int error, locked;

	if (fs->object->type != OBJT_VNODE)
		return (KERN_SUCCESS);
	vp = fs->object->handle;
	if (vp == fs->vp) {
		ASSERT_VOP_LOCKED(vp, "saved vnode is not locked");
		return (KERN_SUCCESS);
	}

	/*
	 * Perform an unlock in case the desired vnode changed while
	 * the map was unlocked during a retry.
	 */
	unlock_vp(fs);

	locked = VOP_ISLOCKED(vp);
	if (locked != LK_EXCLUSIVE)
		locked = LK_SHARED;

	/*
	 * We must not sleep acquiring the vnode lock while we have
	 * the page exclusive busied or the object's
	 * paging-in-progress count incremented.  Otherwise, we could
	 * deadlock.
	 */
	error = vget(vp, locked | LK_CANRECURSE | LK_NOWAIT, curthread);
	if (error == 0) {
		fs->vp = vp;
		return (KERN_SUCCESS);
	}

	vhold(vp);
	release_page(fs);
	unlock_and_deallocate(fs);
	error = vget(vp, locked | LK_RETRY | LK_CANRECURSE, curthread);
	vdrop(vp);
	fs->vp = vp;
	KASSERT(error == 0, ("vm_fault: vget failed %d", error));
	return (KERN_RESOURCE_SHORTAGE);
}
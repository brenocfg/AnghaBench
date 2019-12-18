#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_offset_t ;
typedef  TYPE_3__* vm_object_t ;
struct vnode {int dummy; } ;
struct mount {int dummy; } ;
struct TYPE_8__ {scalar_t__ writemappings; } ;
struct TYPE_9__ {TYPE_1__ vnp; } ;
struct TYPE_10__ {scalar_t__ type; struct vnode* handle; TYPE_2__ un_pager; } ;

/* Variables and functions */
 int LK_RETRY ; 
 int LK_SHARED ; 
 scalar_t__ OBJT_VNODE ; 
 int /*<<< orphan*/  VM_OBJECT_WLOCK (TYPE_3__*) ; 
 int /*<<< orphan*/  VM_OBJECT_WUNLOCK (TYPE_3__*) ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V_WAIT ; 
 int /*<<< orphan*/  vdrop (struct vnode*) ; 
 int /*<<< orphan*/  vhold (struct vnode*) ; 
 int /*<<< orphan*/  vn_finished_write (struct mount*) ; 
 int /*<<< orphan*/  vn_lock (struct vnode*,int) ; 
 int /*<<< orphan*/  vn_start_write (struct vnode*,struct mount**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnode_pager_update_writecount (TYPE_3__*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
vnode_pager_release_writecount(vm_object_t object, vm_offset_t start,
    vm_offset_t end)
{
	struct vnode *vp;
	struct mount *mp;
	vm_offset_t inc;

	VM_OBJECT_WLOCK(object);

	/*
	 * First, recheck the object type to account for the race when
	 * the vnode is reclaimed.
	 */
	if (object->type != OBJT_VNODE) {
		VM_OBJECT_WUNLOCK(object);
		return;
	}

	/*
	 * Optimize for the case when writemappings is not going to
	 * zero.
	 */
	inc = end - start;
	if (object->un_pager.vnp.writemappings != inc) {
		object->un_pager.vnp.writemappings -= inc;
		VM_OBJECT_WUNLOCK(object);
		return;
	}

	vp = object->handle;
	vhold(vp);
	VM_OBJECT_WUNLOCK(object);
	mp = NULL;
	vn_start_write(vp, &mp, V_WAIT);
	vn_lock(vp, LK_SHARED | LK_RETRY);

	/*
	 * Decrement the object's writemappings, by swapping the start
	 * and end arguments for vnode_pager_update_writecount().  If
	 * there was not a race with vnode reclaimation, then the
	 * vnode's v_writecount is decremented.
	 */
	vnode_pager_update_writecount(object, end, start);
	VOP_UNLOCK(vp, 0);
	vdrop(vp);
	if (mp != NULL)
		vn_finished_write(mp);
}